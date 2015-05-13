#ifndef DECK
#define DECK
#include <Vector>
#include "Card.h"


class Deck{
public:
    Deck(int numberOfDecks);
    Deck(Deck& obj);
    ~Deck();

    int numberOfDecks;

    std::vector<Card*> card;

    Card deal();
    void shuffle();
    void readyDeck();
    void initializeDeck(int numberOfDecks);
    void destroy();
};

#endif // DECK
