#ifndef HARD_DEALER
#define HARD_DEALER

#include "Player.h"

class HardDealer : public Player{
public:
    HardDealer(int startingbankroll);
    void selectAction();
    void printCurrentHand();
};

#endif // HARD_DEALER
