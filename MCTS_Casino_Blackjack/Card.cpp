#include "Card.h"
#include <iostream>

Card::Card(int faceValue, int suit){
    if(faceValue == 0){
        this->faceValue = 'A';
    }else if(faceValue == 1){
        this->faceValue = '2';
    }else if(faceValue == 2){
        this->faceValue = '3';
    }else if(faceValue == 3){
        this->faceValue = '4';
    }else if(faceValue == 4){
        this->faceValue = '5';
    }else if(faceValue == 5){
        this->faceValue = '6';
    }else if(faceValue == 6){
        this->faceValue = '7';
    }else if(faceValue == 7){
        this->faceValue = '8';
    }else if(faceValue == 8){
        this->faceValue = '9';
    }else if(faceValue == 9){
        //Z represents 10s
        this->faceValue = 'Z';
    }else if(faceValue == 10){
        this->faceValue = 'J';
    }else if(faceValue == 11){
        this->faceValue = 'Q';
    }else if(faceValue == 12){
        this->faceValue = 'K';
    }else{
        this->faceValue = 'E';
    }

    if(suit == 0){
        this->suit = HEARTS;
    }else if(suit == 1){
        this->suit = SPADES;
    }else if(suit == 2){
        this->suit = DIAMONDS;
    }else if(suit == 3){
        this->suit = CLUBS;
    }else{
        this->suit = ERROR;
    }

}

Card::Card(const Card &obj){
        this->faceValue = obj.faceValue;
        this->suit = obj.suit;

}

void Card::printCard(){
    std::cout << "The ";
    if(faceValue == 'K'){
        std::cout << "King of ";
    }else if(faceValue == 'Q'){
        std::cout << "Queen of ";
    }else if (faceValue == 'J'){
        std::cout << "Jack of ";
    }else if(faceValue == 'A'){
        std::cout << "Ace of ";
    }else if(faceValue == 'Z'){
        std::cout << "10 of ";
    }else if(faceValue >= '2' && faceValue <= '9'){
        std::cout << faceValue << " of ";
    }


    if(suit == HEARTS){
        std::cout << "Hearts" << std::endl;
    }else if(suit == SPADES){
        std::cout << "Spades" << std::endl;
    }else if(suit == DIAMONDS){
        std::cout << "Diamonds" << std::endl;
    }else if(suit == CLUBS){
        std::cout << "Clubs" << std::endl;
    }


    if(faceValue == 'E' || suit == ERROR){
        std::cout << "card is not valid!" << std::endl;
    }
}
