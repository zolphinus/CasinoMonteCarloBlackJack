#ifndef BASIC_PLAYER
#define BASIC_PLAYER

#include "Player.h"

class BasicPlayer : public Player{
public:
    BasicPlayer(int startingbankroll);
    void selectAction(Hand& dealerHand, Deck& deck);
};

#endif // BASIC_PLAYER
