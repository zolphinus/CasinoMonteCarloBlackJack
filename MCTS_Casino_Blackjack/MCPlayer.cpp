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
    for(int i = 0; i < available_actions.size(); i++){
        ACTION_NODE* newAction = new ACTION_NODE();
        newAction->action = available_actions[i];
        unplayedActions.push_back(newAction);
    }

        Player* playerCopy = player.clone();
        Player* dealerCopy = dealer.clone();
        Deck deckCopy(deck);


    //run simulations
    ACTION_NODE* action_to_play;
    int selector = 0;
    if(unplayedActions.size() > 0){
        //then create a copy of myHand, dealerHand, and the deck
        //these will serve as the copies to run the monte carlo sims


        //randomize the deck positions since the dealer's second card and all subsequent cards are unknown
        deckCopy.shuffle();
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

        }else if(action_to_play->action == STAY){

        }else if(action_to_play->action == DOUBLE){

        }else if(action_to_play->action == SPLIT){

        }

        playedActions.push_back(action_to_play);

    }else{
        //all actions have been tried at least once
        //so we use the UTC algorithm to decide
        int totalTickets = (playedActions.size() - 1) * 2;

        for(int i = 0; i < NUM_MC_SIMS; i++){
            //then create a copy of myHand, dealerHand, and the deck
            //these will serve as the copies to run the monte carlo sims

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
        }

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

Player* MCPlayer::clone() const {
    Player* temp = new MCPlayer(*this);
        return temp;
}
