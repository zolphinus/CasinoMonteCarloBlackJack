#include "Card.h"
#include "Deck.h"
#include <time.h>
#include <cstdlib>
#include "Hand.h"


#include "HumanPlayer.h"
#include "HardDealer.h"
#include "SoftDealer.h"
#include "ActionPlayer.h"
#include "RandomPlayer.h"

#include "BasicPlayer.h"
#include "MCPlayer.h"

#include <iostream>


#define NUM_DECKS 6
#define NUM_SIMS 5000
#define START_BANKROLL 50000

#define UNLIMITED_BANKROLL false


void testGame();
void testClone(const Player*);

//human versus dealers
void humanHard(int decks, int bankroll, int simulations);
void humanSoft(int decks, int bankroll, int simulations);

//hard dealer versus dealers
void botGame(int, int, int, Player*&, Player*&);



int main(){
    srand(time(NULL));
    Deck deck(1);
    deck.shuffle();
    //Test Hard Dealer

    Player* player = new HardDealer(START_BANKROLL);
    Player* dealer = new SoftDealer(START_BANKROLL);

    botGame(NUM_DECKS, START_BANKROLL, NUM_SIMS, player, dealer);


    delete player;
    delete dealer;

    player = new HardDealer(START_BANKROLL);
    dealer = new HardDealer(START_BANKROLL);

    botGame(NUM_DECKS, START_BANKROLL, NUM_SIMS, player, dealer);

    //Test Soft Dealer

    delete player;
    delete dealer;

    player = new SoftDealer(START_BANKROLL);
    dealer = new SoftDealer(START_BANKROLL);

    botGame(NUM_DECKS, START_BANKROLL, NUM_SIMS, player, dealer);

    delete player;
    delete dealer;

    player = new SoftDealer(START_BANKROLL);
    dealer = new HardDealer(START_BANKROLL);

    botGame(NUM_DECKS, START_BANKROLL, NUM_SIMS, player, dealer);


    //Test Action Dealer

    delete player;
    delete dealer;

    player = new ActionPlayer(START_BANKROLL, HIT);
    dealer = new SoftDealer(START_BANKROLL);

    botGame(NUM_DECKS, START_BANKROLL, NUM_SIMS, player, dealer);

    delete player;
    delete dealer;

    player = new ActionPlayer(START_BANKROLL, HIT);
    dealer = new HardDealer(START_BANKROLL);

    botGame(NUM_DECKS, START_BANKROLL, NUM_SIMS, player, dealer);


    //test Random Player
    player = new RandomPlayer(START_BANKROLL);
    dealer = new SoftDealer(START_BANKROLL);

    botGame(NUM_DECKS, START_BANKROLL, NUM_SIMS, player, dealer);

    delete player;
    delete dealer;

    player = new RandomPlayer(START_BANKROLL);
    dealer = new HardDealer(START_BANKROLL);

    botGame(NUM_DECKS, START_BANKROLL, NUM_SIMS, player, dealer);

    //test Basic Player
    player = new BasicPlayer(START_BANKROLL);
    dealer = new SoftDealer(START_BANKROLL);

    botGame(NUM_DECKS, START_BANKROLL, NUM_SIMS, player, dealer);


    delete player;
    delete dealer;

    player = new BasicPlayer(START_BANKROLL);
    dealer = new HardDealer(START_BANKROLL);

    botGame(NUM_DECKS, START_BANKROLL, NUM_SIMS, player, dealer);

    delete player;
    delete dealer;

    player = new MCPlayer(START_BANKROLL);
    dealer = new HardDealer(START_BANKROLL);

    botGame(NUM_DECKS, START_BANKROLL, NUM_SIMS, player, dealer);

    delete player;
    delete dealer;

    player = new MCPlayer(START_BANKROLL);
    dealer = new SoftDealer(START_BANKROLL);

    botGame(NUM_DECKS, START_BANKROLL, NUM_SIMS, player, dealer);

}


void testGame(){
    Deck deck(1);
    Player* testPlayer = new HumanPlayer(10000);
    Player* testDealer = new SoftDealer(10000);


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
            testPlayer->selectAction(*testDealer, deck);
            testPlayer->playAction(deck);
            handOver = testPlayer->isFinished;
        }
        handOver = false;
        while(handOver == false){
            //dealer plays
            testDealer->printCurrentHand();
            testDealer->getActions();
            testDealer->selectAction(*testDealer, deck);
            testDealer->playAction(deck);
            handOver = testDealer->isFinished;
        }


        testDealer->printCurrentHand();
        testPlayer->printHands();

        //hands are evaluated


        testPlayer->compareHands(testDealer->hand[0]);
    }
}



void humanHard(int decks, int bankroll, int simulations){
    Deck deck(decks);
    Player* humanPlayer = new HumanPlayer(bankroll);
    Player* hardDealer = new HardDealer(bankroll);

    for(int i = 0; i < simulations; i ++){
        humanPlayer->formatScreen();
        //restore the deck to a randomized original state
        deck.readyDeck();
        //deal Dealer's faceup card
        hardDealer->initializeNewHand();
        hardDealer->addCardToNewHand(deck.deal());
        //deal player's starting hand
        humanPlayer->initializeNewHand();
        humanPlayer->addCardToNewHand(deck.deal());
        humanPlayer->addCardToNewHand(deck.deal());
        hardDealer->printCurrentHand();
        bool handOver = false;
        while(handOver == false){
            //player plays
            humanPlayer->printCurrentHand();
            humanPlayer->getActions();
            humanPlayer->selectAction(*hardDealer, deck);
            humanPlayer->playAction(deck);
            handOver = humanPlayer->isFinished;
        }
        handOver = false;
        while(handOver == false){
            //dealer plays
            hardDealer->printCurrentHand();
            hardDealer->getActions();
            hardDealer->selectAction(*hardDealer, deck);
            hardDealer->playAction(deck);
            handOver = hardDealer->isFinished;
        }
        hardDealer->printCurrentHand();
        humanPlayer->printHands();

        //hands are evaluated
        humanPlayer->compareHands(hardDealer->hand[0]);
        std::cout << "Rounds played : " << humanPlayer->roundsPlayed << std::endl;
        std::cout << "Rounds won : " << humanPlayer->roundsWon << std::endl;
    }
}

void humanSoft(int decks, int bankroll, int simulations){
    Deck deck(decks);
    Player* humanPlayer = new HumanPlayer(bankroll);
    Player* softDealer = new SoftDealer(bankroll);

    for(int i = 0; i < simulations; i ++){
        humanPlayer->formatScreen();
        if(humanPlayer->bankroll < humanPlayer->bid){
            break;
        }
        //restore the deck to a randomized original state
        deck.readyDeck();
        //deal Dealer's faceup card
        softDealer->initializeNewHand();
        softDealer->addCardToNewHand(deck.deal());
        //deal player's starting hand
        humanPlayer->initializeNewHand();
        humanPlayer->addCardToNewHand(deck.deal());
        humanPlayer->addCardToNewHand(deck.deal());
        softDealer->printCurrentHand();
        bool handOver = false;
        while(handOver == false){
            //player plays
            humanPlayer->printCurrentHand();
            humanPlayer->getActions();
            humanPlayer->selectAction(*softDealer, deck);
            humanPlayer->playAction(deck);
            handOver = humanPlayer->isFinished;
        }
        handOver = false;
        while(handOver == false){
            //dealer plays
            softDealer->printCurrentHand();
            softDealer->getActions();
            softDealer->selectAction(*softDealer, deck);
            softDealer->playAction(deck);
            handOver = softDealer->isFinished;
        }
        softDealer->printCurrentHand();
        humanPlayer->printHands();

        //hands are evaluated
        humanPlayer->compareHands(softDealer->hand[0]);
    }


        std::cout << "Rounds played : " << humanPlayer->roundsPlayed << std::endl;
        std::cout << "Rounds won : " << humanPlayer->roundsWon << std::endl;

}


void botGame(int decks, int bankroll, int simulations, Player*& newPlayer,
               Player*& newDealer){
    Deck deck(decks);
    Player* player = newPlayer;
    Player* dealer = newDealer;

    if(UNLIMITED_BANKROLL){
        //create string here for separate file name
    }

    //open file based on the player/dealer name

    //and load any prior statistics



    double highest_bankroll = 0;

    for(int i = 0; i < simulations; i ++){
        //restore the deck to a randomized original state
        if(player->bankroll > highest_bankroll){
            highest_bankroll = (double) player->bankroll;
        }

        if(player->bankroll < player->bid){
            if(UNLIMITED_BANKROLL){
                player->bankroll = bankroll;
            }else{
                break;
            }
        }

        deck.readyDeck();
        //deal Dealer's faceup card
        dealer->initializeNewHand();
        dealer->addCardToNewHand(deck.deal());
        //deal player's starting hand
        player->initializeNewHand();
        player->addCardToNewHand(deck.deal());
        player->addCardToNewHand(deck.deal());
        bool handOver = false;
        while(handOver == false){
            //player plays
            player->getActions();
            player->selectAction(*dealer, deck);
            player->playAction(deck);
            handOver = player->isFinished;
        }
        handOver = false;
        while(handOver == false){
            //dealer plays

            //dealers facedown card is now finalized
            dealer->addCardToNewHand(deck.deal());
            dealer->getActions();
            dealer->selectAction(*dealer, deck);
            dealer->playAction(deck);
            handOver = dealer->isFinished;
        }
        //hands are evaluated
        player->compareHands(dealer->hand[0]);
    }


        std::cout << "Rounds played : " << player->roundsPlayed << std::endl;
        std::cout << "Rounds won : " << player->roundsWon << std::endl;
        std::cout << "Bankroll : " << player->bankroll << std::endl;
        std::cout << "Highest Bankroll : " << highest_bankroll << std::endl << std::endl;
        std::cout << "Win rate is " << (player->roundsWon / player->roundsPlayed) * 100 << "%" << std::endl;

        //output average/min/max statistics to file

        std::cout << std::endl << std::endl;
}

void testClone(const Player* original){
    Deck deck(1);
    deck.shuffle();

    Player* clone = (original->clone());
    Player* clone2 = (original->clone());

    //clone = original->clone();
    clone->addCardToNewHand(deck.deal());

    std::cout << "Clone 1 name is " << clone->playerName << std::endl << "CLONING" << std::endl << std::endl;

    clone2->playerName = "fazilla";

    clone->printCurrentHand();

    clone2->addCardToNewHand(deck.deal());


    std::cout << "Clone 2 name is " << clone2->playerName << std::endl << "CLONED" << std::endl << std::endl;
    clone2->printCurrentHand();

}
