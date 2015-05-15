#ifndef HUMAN_PLAYER
#define HUMAN_PLAYER

#include "Player.h"

class HumanPlayer: public Player{
public:
    HumanPlayer(int startingbankroll);
    void selectAction(Player& dealer, Deck& deck);
    void formatScreen();
    void playAction(Deck&);
    Player* clone() const;
};

#endif // HUMAN_PLAYER
