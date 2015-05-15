#ifndef ACTION_PLAYER
#define ACTION_PLAYER

#include "Player.h"

class ActionPlayer : public Player{
public:
    ActionPlayer(int startingbankroll, ACTION);

    ACTION preferred_action;
    void selectAction(Player& dealer, Deck& deck);
    Player* clone() const;
};

#endif // HIT_PLAYER
