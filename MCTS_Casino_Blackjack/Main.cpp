#include "Card.h"
#include "Deck.h"
#include <time.h>
#include <cstdlib>
#include "Hand.h"
#include "HumanPlayer.h"

#include <iostream>

int main(){
    srand(time(NULL));

    Deck deck(1);
    Player* testPlayer = new HumanPlayer(10000);


    while(true){
        //restore the deck to a randomized original state
        deck.readyDeck();

        //deal Dealer's faceup card

        //deal player's starting hand
        testPlayer->initializeNewHand();
        testPlayer->addCardToNewHand(deck.deal());
        testPlayer->addCardToNewHand(deck.deal());

        bool handOver = false;
        while(handOver == false){
            //player plays
            testPlayer->printCurrentHand();
            testPlayer->getActions();
            testPlayer->selectAction();
            testPlayer->playAction(deck);
            handOver = testPlayer->isFinished;
        }

        testPlayer->printHands();

            //dealer plays


            //hands are evaluated


        testPlayer->formatScreen();
    }

}
