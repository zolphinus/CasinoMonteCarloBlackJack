#include "SoftDealer.h"
#include <iostream>
#include <limits>

#include <cstdlib>

SoftDealer::SoftDealer(int bankroll): Player(bankroll){
    playerName = "Soft";
}


void SoftDealer::selectAction(Player& dealer, Deck& deck){
    currentHand->calculateHandValue();
    //stays on 17+ regardless of aces being 11s

    selected_action = STAY;
    if(currentHand->handValue < 17){
        selected_action = HIT;
    }
}

void SoftDealer::printCurrentHand(){
    if(currentHand != NULL && hand.size() > 0){
        std::cout << this->playerName << " -- ";
        std::cout << "current hand contains: " << std::endl << std::endl;
        currentHand->printHand();
    }

    std::cout << std::endl << std::endl;
}

Player* SoftDealer::cloneMe() const {
    Player* temp = new SoftDealer(*this);
        return temp;
}

Player* SoftDealer::clone() const{
    Player* temp = cloneMe();
    temp->hand.clear();

    for(int i = 0; i < this->hand.size(); i++){
        Hand* tempHand =  new Hand(*this->hand[i]);
        temp->hand.push_back(tempHand);
    }

    temp->currentHand = temp->hand[0];
    return temp;
}
