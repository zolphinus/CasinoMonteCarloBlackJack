#ifndef HAND
#define HAND
#include <vector>
#include "Card.h"

class Hand{
public:
    Hand(int betValue);
    Hand(Card&, int betValue);
    ~Hand();

    std::vector<Card*> card;
    int betValue;
    int handValue;

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
