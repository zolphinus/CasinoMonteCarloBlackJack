#ifndef HUMAN_PLAYER
#define HUMAN_PLAYER

#include "Player.h"

class HumanPlayer: public Player{
public:
    HumanPlayer(int startingbankroll);
    void selectAction(Hand& dealerHand, Deck& deck);
    void formatScreen();
    void playAction(Deck&);
};

#endif // HUMAN_PLAYER
