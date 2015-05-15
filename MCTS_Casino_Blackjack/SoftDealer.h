#ifndef SOFT_DEALER
#define SOFT_DEALER

#include "Player.h"

class SoftDealer : public Player{
public:
    SoftDealer(int startingbankroll);
    void selectAction(Player& dealer, Deck& deck);
    void printCurrentHand();
    Player* clone() const;
};

#endif // SOFT_DEALER
