#ifndef HUMAN_PLAYER
#define HUMAN_PLAYER

#include "Player.h"

class HumanPlayer: public Player{
public:
    HumanPlayer(int startingbankroll);
    void selectAction();
    bool playFinished();
    void formatScreen();
};

#endif // HUMAN_PLAYER
