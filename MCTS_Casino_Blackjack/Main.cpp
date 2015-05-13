#include "Card.h"
#include "Deck.h"
#include <time.h>
#include <cstdlib>
#include "Hand.h"
#include "HumanPlayer.h"
#include "HardDealer.h"

#include <iostream>

int main(){
    srand(time(NULL));

    Deck deck(1);
    Player* testPlayer = new HumanPlayer(10000);
    Player* testDealer = new HardDealer(10000);


    while(true){
        testPlayer->formatScreen();
        std::cout << "Rounds played : " << testPlayer->roundsPlayed << std::endl;
        std::cout << "Rounds won : " << testPlayer->roundsWon << std::endl;

        //restore the deck to a randomized original state
        deck.readyDeck();


        //deal Dealer's faceup card
        testDealer->initializeNewHand();
        testDealer->addCardToNewHand(deck.deal());

        //deal player's starting hand
        testPlayer->initializeNewHand();
        testPlayer->addCardToNewHand(deck.deal());
        testPlayer->addCardToNewHand(deck.deal());


        testDealer->printCurrentHand();
        bool handOver = false;
        while(handOver == false){
            //player plays

            testPlayer->printCurrentHand();
            testPlayer->getActions();
            testPlayer->selectAction();
            testPlayer->playAction(deck);
            handOver = testPlayer->isFinished;
        }
        handOver = false;
        while(handOver == false){
            //dealer plays
            testDealer->printCurrentHand();
            testDealer->getActions();
            testDealer->selectAction();
            testDealer->playAction(deck);
            handOver = testDealer->isFinished;
        }


        testDealer->printCurrentHand();
        testPlayer->printHands();

        //hands are evaluated


        testPlayer->compareHands(testDealer->hand[0]);
    }

}
