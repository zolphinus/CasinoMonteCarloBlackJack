#ifndef MONTE_CARLO_PLAYER
#define MONTE_CARLO_PLAYER

#include "Player.h"
#define NUM_MC_SIMS 2000


struct ACTION_NODE{
    ACTION action;
    double timesPlayed = 0;
    double timesWon = 0;
    double winRate = 0;
    int tickets = 0;
};

class MCPlayer : public Player{
public:
    MCPlayer(int startingbankroll);

    void selectAction(Player& dealer, Deck& deck);

    ACTION monteCarlo(Player& player, Player& dealer, Deck& deck);

    void assignTickets(std::vector<ACTION_NODE*>& playedActions, int);
    Player* clone() const;
private:
    Player* cloneMe() const;

};


#endif // MONTE_CARLO_PLAYER
