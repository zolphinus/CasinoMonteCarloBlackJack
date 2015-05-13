#ifndef SOFT_DEALER
#define SOFT_DEALER

#include "Player.h"

class SoftDealer : public Player{
public:
    SoftDealer(int startingbankroll);
    void selectAction();
    void printCurrentHand();
};

#endif // SOFT_DEALER
