#ifndef RANDOM_PLAYER
#define RANDOM_PLAYER

#include <ctime>
#include <cstdlib>
#include "Player.h"

class RandomPlayer : public Player{
public:
    RandomPlayer(int startingbankroll);
    void selectAction(Hand& dealerHand, Deck& deck);
};


#endif // RANDOM_PLAYER
