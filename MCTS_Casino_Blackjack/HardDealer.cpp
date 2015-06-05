#include "HardDealer.h"
#include <iostream>
#include <limits>

HardDealer::HardDealer(int bankroll): Player(bankroll){
    playerName = "Hard";
}


void HardDealer::selectAction(Player& dealer, Deck& deck){

    //stays only on hard 17s, no Aces as 11
    currentHand->calculateHandValue();
    selected_action = STAY;
    if(currentHand->handValue < 17){
        selected_action = HIT;
    }else if(currentHand->handValue == 17){
        int tempSum = 0;
        for(int i = 0; i < currentHand->card.size(); i++){
            for(int i = 0; i < currentHand->card.size(); i++){
                if(currentHand->card[i]->faceValue == 'K' ||
                   currentHand->card[i]->faceValue == 'Q' ||
                   currentHand->card[i]->faceValue == 'J' ||
                   currentHand->card[i]->faceValue == 'Z'){

                   tempSum += 10;
                   }else if(currentHand->card[i]->faceValue == 'A'){
                       if(tempSum + 11 > 21){
                          tempSum += 1;
                       }else{
                           selected_action = HIT;
                           tempSum += 11;
                       }
                   }else{
                       //converts ASCII to int
                       tempSum += (currentHand->card[i]->faceValue - 48);
                   }
            }
        }
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
