#include "Card.h"
#include "Deck.h"
#include <time.h>
#include <cstdlib>
#include "Hand.h"
#include "Player.h"

int main(){
    srand(time(NULL));

    Deck deck(1);
    Player testPlayer(10000);

    deck.shuffle();

    testPlayer.initializeNewHand();
    testPlayer.addCardToNewHand(deck.deal());
    testPlayer.addCardToNewHand(deck.deal());
    testPlayer.splitHand();

    //testPlayer.hit(deck.deal());

    testPlayer.printHands();



}
