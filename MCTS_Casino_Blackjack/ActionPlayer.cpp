#include "ActionPlayer.h"

ActionPlayer::ActionPlayer(int bankroll, ACTION newAction): Player(bankroll){

    if(newAction == HIT){
        playerName = "HitPlayer";
    }
    if(newAction == STAY){
        playerName = "StayPlayer";
    }
    preferred_action = newAction;
}


void ActionPlayer::selectAction(Player& dealer, Deck& deck){
    currentHand->calculateHandValue();

    if(currentHand->handValue < 21){
        selected_action = HIT;
    }else{
        selected_action = STAY;
    }
}


Player* ActionPlayer::cloneMe() const {
    Player* temp = new ActionPlayer(*this);
        return temp;
}

Player* ActionPlayer::clone() const{
    Player* temp = cloneMe();
    temp->hand.clear();

    for(int i = 0; i < this->hand.size(); i++){
        Hand* tempHand =  new Hand(*this->hand[i]);
        temp->hand.push_back(tempHand);
    }

    temp->currentHand = temp->hand[0];
    return temp;
}
