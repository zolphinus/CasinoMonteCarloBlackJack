#include "MCPlayer.h"
#include <cstdlib>
#include <iostream>

MCPlayer::MCPlayer(int bankroll): Player(bankroll){
    playerName = "Monte Carlo";
}


void MCPlayer::selectAction(Player& dealer, Deck& deck){

    selected_action = monteCarlo(*this, dealer, deck);
}


ACTION MCPlayer::monteCarlo(Player& player, Player& dealer, Deck& deck){
    ACTION chosen_action = STAY;
    //create containers for nodes for each action
    std::vector<ACTION_NODE*> unplayedActions;
    std::vector<ACTION_NODE*> playedActions;

    //create nodes for each action
    for(int i = 0; i < player.available_actions.size(); i++){
        ACTION_NODE* newAction = new ACTION_NODE();
        newAction->action = player.available_actions[i];
        unplayedActions.push_back(newAction);
    }

    Player* playerCopy;
    Player* dealerCopy;
    Deck* deckCopy;


    //run simulations
    ACTION_NODE* action_to_play;
    int selector = 0;
    if(unplayedActions.size() > 0){
        //then create a copy of myHand, dealerHand, and the deck
        //these will serve as the copies to run the monte carlo sims
        while(unplayedActions.size() > 0){

            playerCopy = player.clone();
            dealerCopy = dealer.clone();
            deckCopy = new Deck(deck);

            //randomize the deck positions since the dealer's second card and all subsequent cards are unknown
            deckCopy->shuffle();
            //some actions haven't been tried yet
            //these do not count towards the available simulations
            selector = rand() % unplayedActions.size();
            //swap the action to the back of vector if it's not already last
            if(selector != unplayedActions.size() - 1){
                ACTION_NODE* temp_action;
                temp_action = unplayedActions[selector];
                unplayedActions[selector] = unplayedActions[unplayedActions.size() - 1];
                unplayedActions[unplayedActions.size() - 1] = temp_action;
            }

            //grab the action so that we can mark it as played
            action_to_play = unplayedActions.back();
            unplayedActions.pop_back();


            //then play the action
            if(action_to_play->action == HIT){
                playerCopy->hit(deckCopy->deal());

                Hand* handCopy = playerCopy->currentHand;
                ACTION tempAction = action_to_play->action;
                while(tempAction != STAY && playerCopy->currentHand != handCopy){
                    //busting on a  hit will advance current hand to the next hand, or to null

                    playerCopy->getActions();

                    tempAction = monteCarlo(*playerCopy, *dealerCopy, deck);
                    if(tempAction == HIT){
                        playerCopy->hit(deckCopy->deal());
                    }else{
                        //once you hit, you can't double/split, so stay is the only other option
                        tempAction = STAY;
                    }
                }

                //dealer plays hand out
                bool handOver = false;
                while(handOver == false){
                    //dealer plays

                    //dealers facedown card is now finalized
                    dealerCopy->addCardToNewHand(deckCopy->deal());
                    dealerCopy->getActions();
                    dealerCopy->selectAction(dealer, deck);
                    dealerCopy->playAction(deck);
                    handOver = dealerCopy->isFinished;
                }


                playerCopy->compareHands(dealerCopy->hand[0]);
                action_to_play->timesPlayed += 1.00;
                action_to_play->timesWon += playerCopy->roundsWon;
                action_to_play->winRate = (action_to_play->timesWon / action_to_play->timesPlayed);
            }else if(action_to_play->action == STAY){
                dealerCopy->addCardToNewHand(deckCopy->deal());

                playerCopy->compareHands(dealerCopy->hand[0]);
                action_to_play->timesPlayed += 1.00;
                action_to_play->timesWon += playerCopy->roundsWon;
                action_to_play->winRate = (action_to_play->timesWon / action_to_play->timesPlayed);
            }else if(action_to_play->action == DOUBLE){
                playerCopy->doubleUp(deckCopy->deal());
                dealerCopy->addCardToNewHand(deckCopy->deal());

                playerCopy->compareHands(dealerCopy->hand[0]);
                action_to_play->timesPlayed += 1.00;
                action_to_play->timesWon += playerCopy->roundsWon;
                action_to_play->winRate = (action_to_play->timesWon / action_to_play->timesPlayed);

            }else if(action_to_play->action == SPLIT){
                playerCopy->splitHand();

                //hand 1
                playerCopy->getActions();

                //hand 2
                playerCopy->getActions();

                dealerCopy->addCardToNewHand(deckCopy->deal());

                playerCopy->compareHands(dealerCopy->hand[0]);
                action_to_play->timesPlayed += 1.00;
                action_to_play->timesWon += playerCopy->roundsWon;
                action_to_play->winRate = (action_to_play->timesWon / action_to_play->timesPlayed);

            }

            playedActions.push_back(action_to_play);
            delete playerCopy;
            delete dealerCopy;
            delete deckCopy;


        }
    }
    //all actions have been tried at least once
    //so we use the UTC algorithm to decide
    int totalTickets = (playedActions.size() - 1) * 2;

    for(int i = 0; i < NUM_MC_SIMS; i++){
        //then create a copy of myHand, dealerHand, and the deck
        //these will serve as the copies to run the monte carlo sims

        playerCopy = player.clone();
        dealerCopy = dealer.clone();
        deckCopy = new Deck(deck);


        //first we assign available tickets, weighting the action with the best win %
        assignTickets(playedActions, totalTickets);

        //then we draw a ticket from 0 to N - 1
        int ticketDrawn = rand() % totalTickets;

        //we use that ticket to figure out which action to select using UTC
        for(int i = 0; i < playedActions.size(); i++){
            ticketDrawn -= playedActions[i]->tickets;
            if(ticketDrawn < 0){
                action_to_play = playedActions[i];
            }
        }

        //dealer's unknown card is dealt first, but isn't used in the Monte Carlo logic
        dealerCopy->addCardToNewHand(deckCopy->deal());
        if(action_to_play->action == HIT){

        }else if(action_to_play->action == STAY){

        }else if(action_to_play->action == DOUBLE){

        }else if(action_to_play->action == SPLIT){

        }


        delete playerCopy;
        delete dealerCopy;
        delete deckCopy;

    }


    //decide best action and return it
    ACTION_NODE* best_action = playedActions[0];
    for(int i = 0; i < playedActions.size(); i++){
        if(playedActions[i]->winRate > best_action->winRate){
            best_action = playedActions[i];
        }else if(playedActions[i]->winRate == best_action->winRate){
            //decide randomly between the tied actions
            int tiebreaker = rand() % 20;
            if(tiebreaker > 9){
                best_action = playedActions[i];
            }
        }
    }

    chosen_action = best_action->action;
    best_action = NULL;

    //cleanup memory of nodes
    for(int i = 0; i < playedActions.size(); i++){
        delete playedActions[i];
    }
    playedActions.clear();


    return chosen_action;
}


void MCPlayer::assignTickets(std::vector<ACTION_NODE*>& playedActions, int totalTickets){
    //create tickets for the UTC algorithm
    int winnerTickets = totalTickets / 2;
    totalTickets = totalTickets - winnerTickets;

    ACTION_NODE* best_action = playedActions[0];
    for(int i = 0; i < playedActions.size(); i++){
        if(playedActions[i]->winRate > best_action->winRate){
            best_action = playedActions[i];
        }else if(playedActions[i]->winRate == best_action->winRate){
            //decide randomly between the tied actions
            int tiebreaker = rand() % 20;
            if(tiebreaker > 9){
                best_action = playedActions[i];
            }
        }
    }

    if(winnerTickets == 0){
        winnerTickets = 1;
    }

    best_action->tickets = winnerTickets;
    for(int i = 0; i < playedActions.size(); i++){
        if(playedActions[i] != best_action){
            playedActions[i]->tickets = 1;
            totalTickets--;
        }
    }

    if(totalTickets != 0){
        std::cout << "ERROR IN TICKET DISTRIBUTION" << std::endl;
    }

}

Player* MCPlayer::cloneMe() const {
    Player* temp = new MCPlayer(*this);
        return temp;
}

Player* MCPlayer::clone() const{
    Player* temp = cloneMe();
    temp->hand.clear();

    for(int i = 0; i < this->hand.size(); i++){
        Hand* tempHand =  new Hand(*this->hand[i]);
        temp->hand.push_back(tempHand);
    }

    temp->currentHand = temp->hand[0];
    return temp;
}
