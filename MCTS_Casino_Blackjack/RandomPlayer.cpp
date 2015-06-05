#include "RandomPlayer.h"

RandomPlayer::RandomPlayer(int bankroll): Player(bankroll){
    playerName = "Random";
}


void RandomPlayer::selectAction(Player& dealer, Deck& deck){
    int selector = rand() % available_actions.size();

    switch(selector){
    case 0:
        selected_action = HIT;
        break;
    case 1:
        selected_action = STAY;
        break;
    case 2:
        selected_action = DOUBLE_DOWN;
        break;
    case 3:
        selected_action = SPLIT;
        break;
    default:
        selected_action = NO_ACTION;
    }

}

Player* RandomPlayer::cloneMe() const {
    Player* temp = new RandomPlayer(*this);
        return temp;
}

Player* RandomPlayer::clone() const{
    Player* temp = cloneMe();
    temp->hand.clear();

    for(int i = 0; i < this->hand.size(); i++){
        Hand* tempHand =  new Hand(*this->hand[i]);
        temp->hand.push_back(tempHand);
    }

    temp->currentHand = temp->hand[0];
    return temp;
}
