#include "Player.h"
#include <iostream>

Player::Player(int startingBankroll){
    currentHand = NULL;
    selected_action = NO_ACTION;
    this->starting_bankroll = startingBankroll;
    this->bankroll = starting_bankroll;
    playerFinished = false;
    handSelector = false;
    bid = MAX_BID;
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
    }
}

void Player::splitHand(){
    if(currentHand != NULL){
        currentHand->blackjackPossible = false;
        Card* tempCard = new Card(currentHand->split());
        Hand* newHand = new Hand(*tempCard, bid);
        bankroll -= bid;
        currentHand->calculateHandValue();
        newHand->blackjackPossible = false;
        newHand->calculateHandValue();
        hand.push_back(newHand);

        //splits still require playing the current hand out
    }
}


void Player::initializeNewHand(){
    emptyHand();
    Hand* tempHand = new Hand(bid);
    bankroll -= bid;
    currentHand = tempHand;
    hand.push_back(tempHand);
}

void Player::emptyHand(){
    if(hand.size() > 0){
        std::vector<Hand*>::iterator it = hand.begin();
        int i = 0;
        for(it; it != hand.end(); it++, i++){
            Hand* tempHand = *it;
            delete tempHand;
        }
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

void Player::checkIfFinished(){
    if(currentHand == NULL){
        isFinished = true;
    }
}
