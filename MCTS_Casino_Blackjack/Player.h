#ifndef PLAYER
#define PLAYER
#include <string>
#include <vector>
#include "Card.h"
#include "Hand.h"
#include "Deck.h"

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

    double roundsPlayed;
    double roundsWon;

    double highestBankroll;


    std::vector<ACTION> available_actions;
    ACTION selected_action;
    int starting_bankroll;
    int bankroll;
    int bid;
    bool isFinished;

    //player actions


    void getActions();
    void clearActions();
    void printActions();

    void compareHands(Hand* dealerHand);
    void compareSingleHand(Hand* dealerHand);

    //only the Basic Player and AI variants use the hand/deck when selecting an action
    //but declaring a pure virtual function makes sense for more generic bots
    virtual void selectAction(Player& dealer, Deck& deck) = 0;



    virtual void formatScreen(){};
    virtual void playAction(Deck&);
    virtual Player* clone() const = 0;


    inline void hit(Card);
    inline void stay();
    inline void doubleUp(Card);
    inline void splitHand();

    Hand* getNextHand();
    void initializeNewHand();
    void addCardToNewHand(Card newCard);
    void updateBankroll(int results);
    inline void emptyHand();
    void printHands();
    virtual void printCurrentHand();

    void saveWinRateData(std::string, double);
    void saveMoneyData(std::string, int);
    void saveTimeData(std::string, double);


    void checkIfFinished();
};

#endif // PLAYER
