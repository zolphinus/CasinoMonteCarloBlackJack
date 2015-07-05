#ifndef HAND
#define HAND
#include <vector>
#include "Card.h"

#define MAX_BID 100

class Hand{
public:
    Hand(double betValue);
    Hand(Card&, double betValue);
    ~Hand();

    std::vector<Card*> card;
    double betValue;
    int handValue;
    double handRewardValue;

    bool won;
    bool busted;
    bool blackjackPossible;
    bool doubled;
    bool aceSplit;

    void addCard(Card);
    void sortAces();
    void calculateHandValue();
    Card split();
    bool canSplit();
    bool canDouble();

    void printHand();


};

#endif // HAND
