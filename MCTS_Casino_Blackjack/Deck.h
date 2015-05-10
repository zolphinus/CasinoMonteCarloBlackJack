#ifndef DECK
#define DECK
#include <Vector>
#include "Card.h"


class Deck{
public:
    Deck(int numberOfDecks);
    Deck(Deck& obj);
    ~Deck();

    std::vector<Card*> card;

    Card deal();
    void shuffle();
};

#endif // DECK
