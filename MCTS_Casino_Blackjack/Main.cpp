#include "Card.h"
#include "Deck.h"
#include <time.h>
#include <cstdlib>
#include "Hand.h"

int main(){
    srand(time(NULL));

    Deck tempDeck(1);
    Deck deck(tempDeck);

    deck.shuffle();

    Card* tempCard = new Card(deck.deal());

    Hand tempHand(10);
    tempHand.addCard(*tempCard);
    for(int i = 0; i < 10; i++){
        tempCard = new Card(deck.deal());
        tempHand.addCard(*tempCard);
    }

    tempHand.calculateHandValue();

    tempHand.printHand();
}
