#include "HumanPlayer.h"
#include <iostream>
#include <limits>

HumanPlayer::HumanPlayer(int bankroll): Player(bankroll){
    playerName = "Human";
}

void HumanPlayer::selectAction(Player& dealer, Deck& deck){
    std::cout << "What would you like to do? (Type a number and then press enter)" << std::endl << std::endl;
    bool validInput;
    for(int i = 0; i < this->available_actions.size(); i++){
        std::cout << i << ") ";

        switch(i){
        case 0:
            std::cout << "HIT";
            break;
        case 1:
            std::cout << "STAY";
            break;
        case 2:
            std::cout << "DOUBLE";
            break;
        case 3:
            std::cout << "SPLIT";
            break;
        case 4:
            std::cout << "NO ACTION";
            break;
        }

        std::cout << std::endl;
    }

    int selector = 5;

    std::cout << std::endl << "I want to : ";
    std::cin >> selector;

    if(!std::cin){
        validInput = false;
    }else if(selector > available_actions.size() - 1){
        validInput = false;
    }else{
        validInput = true;
    }

    while(validInput == false){
        validInput = true;
        if(!std::cin){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << std::endl << "Invalid selection" << std::endl << std::endl;
            std::cout << "What would you like to do? (Type a number and then press enter)" << std::endl << std::endl;

        for(int i = 0; i < this->available_actions.size(); i++){
            std::cout << i << ") ";

            switch(i){
            case 0:
                std::cout << "HIT";
                break;
            case 1:
                std::cout << "STAY";
                break;
            case 2:
                std::cout << "DOUBLE";
                break;
            case 3:
                std::cout << "SPLIT";
                break;
            case 4:
                std::cout << "NO ACTION";
                break;
            }

            std::cout << std::endl;
        }
        std::cin >> selector;
        }else if (selector > available_actions.size() - 1){
            std::cout << std::endl << "Invalid selection" << std::endl << std::endl;
            std::cout << "What would you like to do? (Type a number and then press enter)" << std::endl << std::endl;

        for(int i = 0; i < this->available_actions.size(); i++){
            std::cout << i << ") ";

            switch(i){
            case 0:
                std::cout << "HIT";
                break;
            case 1:
                std::cout << "STAY";
                break;
            case 2:
                std::cout << "DOUBLE";
                break;
            case 3:
                std::cout << "SPLIT";
                break;
            case 4:
                std::cout << "NO ACTION";
                break;
            }

            std::cout << std::endl;
        }
        std::cin >> selector;
        }

        if(!std::cin){
            validInput = false;
        }else if(selector > available_actions.size() - 1){
            validInput = false;
        }else{
            validInput = true;
        }

    }


    switch(selector){
        case 0:
            selected_action = HIT;
            break;
        case 1:
            selected_action = STAY;
            break;
        case 2:
            selected_action = DOUBLE_DOWN;
            break;
        case 3:
            selected_action = SPLIT;
            break;
        case 4:
            selected_action = NO_ACTION;
            break;
        }

}

void HumanPlayer::formatScreen(){
    std::cout << std::endl << std::endl << std::endl << std::endl << std::endl <<
                   std::endl << std::endl << std::endl;
}


void HumanPlayer::playAction(Deck& deck){
    std::cout << std::endl;
    if(selected_action == HIT){
        std::cout << "Hitting" << std::endl << std::endl;
        this->hit(deck.deal());
    }else if(selected_action == STAY){
        std::cout << "Staying" << std::endl << std::endl;
        this->stay();
    }else if(selected_action == DOUBLE_DOWN){
        std::cout << "Double Up" << std::endl << std::endl;
        this->doubleUp(deck.deal());
    }else if(selected_action == SPLIT){
        std::cout << "Splitting" << std::endl << std::endl;
        this->splitHand();
    }

    checkIfFinished();
}

Player* HumanPlayer::cloneMe() const {
    Player* temp = new HumanPlayer(*this);
        return temp;
}

Player* HumanPlayer::clone() const{
    Player* temp = cloneMe();
    temp->hand.clear();

    for(int i = 0; i < this->hand.size(); i++){
        Hand* tempHand =  new Hand(*this->hand[i]);
        temp->hand.push_back(tempHand);
    }

    temp->currentHand = temp->hand[0];
    return temp;
}
