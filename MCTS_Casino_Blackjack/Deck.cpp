#include "Deck.h"
#include <cstdlib>
#include <iostream>

Deck::Deck(int numberOfDecks){

    this->numberOfDecks = numberOfDecks;
    initializeDeck(numberOfDecks);
    shuffle();
}

Deck::Deck(Deck& copyDeck){
    std::vector<Card*>::iterator it = copyDeck.card.begin();
    int i = 0;
    for(it; it != copyDeck.card.end(); it++, i++){
        Card* tempCard = new Card(**it);
        this->card.push_back(tempCard);
    }
}

Deck::~Deck(){
    destroy();
}

Card Deck::deal(){
    Card tempCard('E', ERROR);
    if(card.size() > 0){
        int j = rand() % card.size();

        Card* temp = card[j];
        card[j] = card[card.size() - 1];
        card[card.size() - 1] = temp;

        tempCard = *card.back();
        card.pop_back();
        return tempCard;
    }


    return tempCard;
}


void Deck::shuffle(){
    //fisher yates shuffle
    for(int i = card.size() - 1; i >= 1; i--){
        int j = rand() % i;

        Card* temp = card[i];
        card[i] = card[j];
        card[j] = temp;
    }
}


void Deck::readyDeck(){
    destroy();
    initializeDeck(this->numberOfDecks);
    shuffle();
}


void Deck::initializeDeck(int numberOfDecks){
    for(int i = 0; i < 13; i++){
        for(int j = 0; j < 4; j++){
            for(int k = 0; k < numberOfDecks; k++){
                Card* tempCard = new Card(i, j);
                card.push_back(tempCard);
            }
        }
    }
}


void Deck::destroy(){
    std::vector<Card*>::iterator it = card.begin();
    int i = 0;
    for(it; it != card.end(); it++, i++){
        Card* tempCard = *it;
        delete tempCard;
    }
    card.clear();
}
