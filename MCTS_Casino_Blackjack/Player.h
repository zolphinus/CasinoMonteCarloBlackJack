#ifndef PLAYER
#define PLAYER
#include <string>
#include <vector>
#include "Card.h"
#include "Hand.h"

#define MAX_BID 100

enum ACTION{
    HIT,
    STAY,
    DOUBLE,
    SPLIT,
    NO_ACTION
};

class Player{
public:
    Player(int startingBankroll);

    //player data
    std::string playerName;
    std::vector<Hand*> hand;
    Hand* currentHand;
    int handSelector;

    std::vector<ACTION> available_actions;
    ACTION selected_action;
    int starting_bankroll;
    int bankroll;
    int bid;
    bool isFinished;

    //player actions

    /*
    virtual void getActions() = 0;
    virtual void selectAction() = 0;
    virtual void playAction() = 0;
    */


    void hit(Card);
    void stay();
    void doubleUp(Card);
    void splitHand();

    Hand* getNextHand();
    void initializeNewHand();
    void addCardToNewHand(Card newCard);
    void updateBankroll(int results);
    void emptyHand();
    void printHands();

    void checkIfFinished();
};

#endif // PLAYER
