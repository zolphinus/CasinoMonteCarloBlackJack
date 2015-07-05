#include "Hand.h"
#include <iostream>

Hand::Hand(double betValue){
    this->betValue = betValue;
    won = false;
    busted = false;
    doubled = false;
    blackjackPossible = true;
    aceSplit = false;
    handValue = 0;
    handRewardValue = 1.00;
}


Hand::Hand(Card& firstCard, double betValue ){
    Card* tempCard = new Card(firstCard);
    card.push_back(tempCard);
    this->betValue = betValue;

    if(betValue > MAX_BID){
        this->betValue = MAX_BID;
    }
    won = false;
    busted = false;
    doubled = false;
    blackjackPossible = false;
    if(tempCard->faceValue == 'A'){
        aceSplit = true;
    }

    calculateHandValue(); //needs to get card value
}

Hand::~Hand(){
    std::vector<Card*>::iterator it = card.begin();
    int i = 0;
    for(it; it != card.end(); it++, i++){
        Card* tempCard = *it;
        delete tempCard;
    }
    card.clear();
}

bool Hand::canDouble(){
    return !doubled;
}

bool Hand::canSplit(){
    if(card.size() > 2 || card.size() < 2){
        return false;
    }

    if(card[0]->faceValue == card[1]->faceValue){
        return true;
    }

    return false;
}

Card Hand::split(){
    Card tempCard('E', ERROR);
    if(card.size() > 0){
        tempCard =*card.back();
        card.pop_back();
    }
    blackjackPossible = false;
    return tempCard;
}

void Hand::addCard(Card newCard){
    Card* tempCard = new Card(newCard);
    card.push_back(tempCard);
}

void Hand::sortAces(){
    //places Aces at the end of a hand to add them easier
    int j = card.size() - 1;
    for(int i = card.size() - 1; i >= 1; i--){
        if(card[i]->faceValue == 'A'){
            //we found an ace, so swap it to the end of the vector
            Card* tempCard = card[i];
            card[i] = card[j];
            card[j] = tempCard;
            j--;
        }
    }
}

void Hand::calculateHandValue(){
    sortAces();
    handValue = 0;
    for(int i = 0; i < card.size(); i++){
        if(card[i]->faceValue == 'K' ||
           card[i]->faceValue == 'Q' ||
           card[i]->faceValue == 'J' ||
           card[i]->faceValue == 'Z'){

           handValue += 10;
           }else if(card[i]->faceValue == 'A'){
               if(handValue + 11 > 21){
                  handValue += 1;
               }else{
                   handValue += 11;
               }
           }else{
               //converts ASCII to int
               handValue += (card[i]->faceValue - 48);
           }
    }

    if(handValue > 21){
        busted = true;
    }
}


void Hand::printHand(){
    for(int i = 0; i < card.size(); i++){
        card[i]->printCard();
    }

    std::cout << std::endl << "Hand value is " << handValue << std::endl;
    if(busted){
        std::cout << "The hand is busted" << std::endl << std::endl;
    }
}
