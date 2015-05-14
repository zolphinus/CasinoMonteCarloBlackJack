#include "HardDealer.h"
#include <iostream>
#include <limits>

HardDealer::HardDealer(int bankroll): Player(bankroll){
    playerName = "Dealer (Hard17)";
}


void HardDealer::selectAction(Hand& dealerHand, Deck& deck){
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
