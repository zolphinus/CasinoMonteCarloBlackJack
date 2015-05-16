#include "Player.h"
#include <iostream>

Player::Player(int startingBankroll){
    currentHand = NULL;
    selected_action = NO_ACTION;
    this->starting_bankroll = startingBankroll;
    this->bankroll = starting_bankroll;
    isFinished = false;
    bid = MAX_BID;
    handSelector = 0;
    roundsPlayed = 0.00;
    roundsWon = 0.00;
    highestBankroll = 0;
}


Hand* Player::getNextHand(){
    Hand* tempHand;
    handSelector++;
    if(handSelector < hand.size()){
        tempHand = hand[handSelector];
    }else{
        tempHand = NULL;
    }

    return tempHand;
}

void Player::hit(Card hitCard){
    if(currentHand != NULL){
        currentHand->addCard(hitCard);
        currentHand->doubled = true; //can't double after hitting
        currentHand->calculateHandValue();
        if(currentHand->aceSplit || currentHand->busted){
            //can only hit once with ace split, and can't hit any more on a bust
            currentHand = getNextHand();
        }
    }
}

void Player::stay(){
    if(currentHand != NULL){
        currentHand->calculateHandValue();
        currentHand = getNextHand();
    }
}

void Player::doubleUp(Card hitCard){
    if(currentHand != NULL){
        currentHand->addCard(hitCard);
        currentHand->doubled; //variable possibly obsolete
        currentHand->betValue += bid;
        bankroll -= bid;
        currentHand->calculateHandValue();
        currentHand = getNextHand();
    }
}

void Player::splitHand(){
    if(currentHand != NULL){
        currentHand->blackjackPossible = false;
        Card* tempCard = new Card(currentHand->split());
        currentHand->handRewardValue = currentHand->handRewardValue / 2;
        Hand* newHand = new Hand(*tempCard, bid);
        newHand->handRewardValue = newHand->handRewardValue / 2;
        bankroll -= bid;
        currentHand->calculateHandValue();
        newHand->blackjackPossible = false;
        newHand->calculateHandValue();
        hand.push_back(newHand);
        //splits still require playing the current hand out
    }else{
        std::cout << "morph" << std::endl;
    }
}


void Player::initializeNewHand(){
    roundsPlayed += 1.00;
    handSelector = 0;
    emptyHand();
    Hand* tempHand = new Hand(bid);
    bankroll -= bid;
    currentHand = tempHand;
    hand.push_back(tempHand);
    isFinished = false;
}

void Player::emptyHand(){
    if(hand.size() > 0){
        std::vector<Hand*>::iterator it = hand.begin();
        int i = 0;
        for(it; it != hand.end(); it++, i++){
            Hand* tempHand = *it;
            delete tempHand;
        }
        hand.clear();
    }
}

void Player::addCardToNewHand(Card newCard){
    if(currentHand != NULL){
        currentHand->addCard(newCard);
        currentHand->calculateHandValue();
    }
}

void Player::updateBankroll(int results){
    bankroll += results;
}

void Player::printHands(){
    if(hand.size() > 0){
        std::cout << std::endl << "Current hands contain: " << std::endl << std::endl;
        std::vector<Hand*>::iterator it = hand.begin();
        int i = 0;
        for(it; it != hand.end(); it++, i++){
            Hand* tempHand = *it;
            tempHand->printHand();
            std::cout << std::endl;
        }


        std::cout << "BANKROLL IS : " << bankroll << std::endl << std::endl;
    }else{
        std::cout << "Player has no hand." << std::endl << std::endl;
    }
}

void Player::printCurrentHand(){
    if(currentHand != NULL && hand.size() > 0){
        std::cout << this->playerName << " -- ";
        std::cout << "current hand contains: " << std::endl << std::endl;
        currentHand->printHand();
        std::cout << "BANKROLL IS : " << bankroll << std::endl << std::endl;
    }
}

void Player::checkIfFinished(){
    if(currentHand == NULL){
        isFinished = true;
    }else{
        isFinished = false;
    }
}


void Player::getActions(){
    clearActions();
    if(currentHand != NULL){
        available_actions.push_back(HIT);
        available_actions.push_back(STAY);
        if(currentHand->canDouble()){
            available_actions.push_back(DOUBLE);
        }

        if(currentHand->canSplit()){
            available_actions.push_back(SPLIT);
        }
    }else{
        std::cout << "HAND IS NULL" << std::endl;
        //available_actions.push_back(NO_ACTION);
    }
}

void Player::clearActions(){
    if(available_actions.size() > 0){
        available_actions.clear();
    }
}

void Player::printActions(){
    for(int i = 0; i < available_actions.size(); i++){
        std::cout << available_actions[i] << std::endl;
    }
}


void Player::playAction(Deck& deck){
    if(selected_action == HIT){
        this->hit(deck.deal());
    }else if(selected_action == STAY){
        this->stay();
    }else if(selected_action == DOUBLE){
        this->doubleUp(deck.deal());
    }else if(selected_action == SPLIT){
        this->splitHand();
    }

    checkIfFinished();
}


void Player::compareHands(Hand* dealerHand){
    for(int i = 0; i < hand.size(); i++){
        if(hand[i]->handRewardValue > 1){
            hand[i]->handRewardValue = 1;
        }
        if(dealerHand->handValue == 21 && dealerHand->card.size() == 2){
            //dealer has natural blackjack
            if(hand[i]->handValue == 21 && hand[i]->card.size() == 2 && hand[i]->blackjackPossible){
                //player also has a natural blackjack, ties, and pushes
                //but splits cannot have a natural blackjack so they aren't counted
                this->bankroll += hand[i]->betValue;

                //rewards half the hand reward because it's a tie
                roundsWon += (hand[i]->handRewardValue / 2);
            }
        }else if(hand[i]->busted){
            //lose, so do nothing
        }else if(dealerHand->busted){
            //if the dealer busts but the player didn't, player wins
            this->bankroll += (2 * hand[i]->betValue);
            roundsWon += hand[i]->handRewardValue;
        }else if(hand[i]->handValue == 21 && hand[i]->card.size() == 2 && hand[i]->blackjackPossible){
            //dealer has no blackjack but player does
            this->bankroll += (3 * hand[i]->betValue);
            roundsWon += hand[i]->handRewardValue;
        }else{
            //we must compare hand values to determine winner

            if(hand[i]->handValue == dealerHand->handValue){
                //push
                this->bankroll += hand[i]->betValue;

                //rewards half the hand reward because it's a tie
                roundsWon += (hand[i]->handRewardValue / 2);
            }else if(hand[i]->handValue > dealerHand->handValue){
                //wins
                this->bankroll += (2 * hand[i]->betValue);
                roundsWon += hand[i]->handRewardValue;
            }else{
                //loses

            }
        }

    }

}


void Player::compareSingleHand(Hand* dealerHand){
    if(currentHand == NULL){
        return;
    }


    if(dealerHand->handValue == 21 && dealerHand->card.size() == 2){
        //dealer has natural blackjack
        if(currentHand->handValue == 21 && currentHand->card.size() == 2 && currentHand->blackjackPossible){
            //player also has a natural blackjack, ties, and pushes
            //but splits cannot have a natural blackjack so they aren't counted
            this->bankroll += currentHand->betValue;

            //rewards half the hand reward because it's a tie
            roundsWon += (currentHand->handRewardValue / 2);
        }
    }else if(currentHand->busted){
        //lose, so do nothing
    }else if(dealerHand->busted){
        //if the dealer busts but the player didn't, player wins
        this->bankroll += (2 * currentHand->betValue);
        roundsWon += currentHand->handRewardValue;
    }else if(currentHand->handValue == 21 && currentHand->card.size() == 2 && currentHand->blackjackPossible){
        //dealer has no blackjack but player does
        this->bankroll += (3 * currentHand->betValue);
        roundsWon += currentHand->handRewardValue;
    }else{
        //we must compare hand values to determine winner

        if(currentHand->handValue == dealerHand->handValue){
            //push
            this->bankroll += currentHand->betValue;

            //rewards half the hand reward because it's a tie
            roundsWon += (currentHand->handRewardValue / 2);
        }else if(currentHand->handValue > dealerHand->handValue){
            //wins
            this->bankroll += (2 * currentHand->betValue);
            roundsWon += currentHand->handRewardValue;
        }else{
            //loses

        }
    }

}
