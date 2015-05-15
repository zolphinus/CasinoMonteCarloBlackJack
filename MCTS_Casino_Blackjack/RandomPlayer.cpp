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
        selected_action = DOUBLE;
        break;
    case 3:
        selected_action = SPLIT;
        break;
    default:
        selected_action = NO_ACTION;
    }

}

Player* RandomPlayer::clone() const {
    Player* temp = new RandomPlayer(*this);
        return temp;
}
