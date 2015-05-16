#ifndef BASIC_PLAYER
#define BASIC_PLAYER

#include "Player.h"

class BasicPlayer : public Player{
public:
    BasicPlayer(int startingbankroll);
    void selectAction(Player& dealer, Deck& deck);
    Player* clone() const;
private:
    Player* cloneMe() const;
};

#endif // BASIC_PLAYER
