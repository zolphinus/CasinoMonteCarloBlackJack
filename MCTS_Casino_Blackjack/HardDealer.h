#ifndef HARD_DEALER
#define HARD_DEALER

#include "Player.h"

class HardDealer : public Player{
public:
    HardDealer(int startingbankroll);
    void selectAction(Player& dealer, Deck& deck);
    void printCurrentHand();
    Player* clone() const;
private:
    Player* cloneMe() const;
};

#endif // HARD_DEALER
