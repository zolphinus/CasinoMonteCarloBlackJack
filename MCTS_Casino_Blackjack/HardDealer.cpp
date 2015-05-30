#include "HardDealer.h"
#include <iostream>
#include <limits>

HardDealer::HardDealer(int bankroll): Player(bankroll){
    playerName = "Hard";
}


void HardDealer::selectAction(Player& dealer, Deck& deck){
    currentHand->calculateHandValue();
    if(currentHand->handValue < 17){
        selected_action = HIT;
    }else{
        selected_action = STAY;
    }
}

void HardDealer::printCurrentHand(){
    if(currentHand != NULL && hand.size() > 0){
        std::cout << this->playerName << " -- ";
        std::cout << "current hand contains: " << std::endl << std::endl;
        currentHand->printHand();
    }

    std::cout << std::endl << std::endl;
}


Player* HardDealer::cloneMe() const {
    Player* temp = new HardDealer(*this);
        return temp;
}

Player* HardDealer::clone() const{
    Player* temp = cloneMe();
    temp->hand.clear();

    for(int i = 0; i < this->hand.size(); i++){
        Hand* tempHand =  new Hand(*this->hand[i]);
        temp->hand.push_back(tempHand);
    }

    temp->currentHand = temp->hand[0];
    return temp;
}
