#include "ActionPlayer.h"

ActionPlayer::ActionPlayer(int bankroll, ACTION newAction): Player(bankroll){
    playerName = "ActionPlayer";
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


Player* ActionPlayer::clone() const {
    Player* temp = new ActionPlayer(*this);
        return temp;
}
