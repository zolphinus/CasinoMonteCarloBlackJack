#include "Deck.h"
#include <cstdlib>

Deck::Deck(int numberOfDecks){

    for(int i = 0; i < 13; i++){
        for(int j = 0; j < 4; j++){
            for(int k = 0; k < numberOfDecks; k++){
                Card* tempCard = new Card(i, j);
                card.push_back(tempCard);
            }
        }
    }
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
    std::vector<Card*>::iterator it = card.begin();
    int i = 0;
    for(it; it != card.end(); it++, i++){
        Card* tempCard = *it;
        delete tempCard;
    }
}

Card Deck::deal(){
    Card tempCard('E', ERROR);
    if(card.size() > 0){
        tempCard = *card.back();
        card.pop_back();
        return tempCard;
    }


    return tempCard;
}


void Deck::shuffle(){

    for(int i = card.size() - 1; i >= 1; i--){
        int j = rand() % i;

        Card* temp = card[i];
        card[i] = card[j];
        card[j] = temp;
    }
}
