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
        std::cout << "LL" << std::endl;
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

        std::cout << "Can split = " << currentHand->canSplit() << std::endl;

        if(currentHand->canSplit()){
            available_actions.push_back(SPLIT);
        }
    }else{
        available_actions.push_back(NO_ACTION);
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
    std::cout << std::endl;
    if(selected_action == HIT){
        std::cout << "Hitting" << std::endl << std::endl;
        this->hit(deck.deal());
    }else if(selected_action == STAY){
        std::cout << "Staying" << std::endl << std::endl;
        this->stay();
    }else if(selected_action == DOUBLE){
        std::cout << "Double Up" << std::endl << std::endl;
        this->doubleUp(deck.deal());
    }else if(selected_action == SPLIT){
        std::cout << "Splitting" << std::endl << std::endl;
        this->splitHand();
    }

    checkIfFinished();
}
