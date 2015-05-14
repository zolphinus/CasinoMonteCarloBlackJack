#ifndef ACTION_PLAYER
#define ACTION_PLAYER

#include "Player.h"

class ActionPlayer : public Player{
public:
    ActionPlayer(int startingbankroll, ACTION);

    ACTION preferred_action;
    void selectAction(Hand& dealerHand, Deck& deck);
};

#endif // HIT_PLAYER
