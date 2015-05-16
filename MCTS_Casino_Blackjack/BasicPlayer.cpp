#include "BasicPlayer.h"

BasicPlayer::BasicPlayer(int bankroll): Player(bankroll){
    playerName = "Basic";
}


void BasicPlayer::selectAction(Player& dealer, Deck& deck){
    selected_action = STAY; //default action

    //dealer's faceup card value
    char upcard = dealer.hand[0]->card[0]->faceValue;

    if(currentHand->canSplit()){
        //logic for hand split table
        if(currentHand->card[0]->faceValue == 'A' ||
           currentHand->card[0]->faceValue == '8'){
               //always split on 8's and Aces
               selected_action = SPLIT;
        }else if(currentHand->card[0]->faceValue == '9'){
            switch(upcard){
            case '2' : case '3' : case '4' : case '5' : case '6':
            case '8' : case '9' :
                selected_action = SPLIT;
                break;
            }
        }else if(currentHand->card[0]->faceValue == '7'){
            switch(upcard){
            case '2' : case '3' : case '4' : case '5' : case '6':
            case '7' :
                selected_action = SPLIT;
                break;
            case '8' : case '9' : case 'Z' : case 'J' : case 'Q':
            case 'K' : case 'A' :
                selected_action = HIT;
                break;
            }
        }else if(currentHand->card[0]->faceValue == '6'){
            switch(upcard){
            case '2' : case '3' : case '4' : case '5' : case '6':
                selected_action = SPLIT;
                break;
            case '7' : case '8' : case '9' : case 'Z' : case 'J' :
            case 'Q' : case 'K' : case 'A' :
                selected_action = HIT;
                break;
            }
        }else if(currentHand->card[0]->faceValue == '5'){
            switch(upcard){
            case '2' : case '3' : case '4' : case '5' : case '6':
            case '7' : case '8' : case '9' :
                selected_action = DOUBLE;
                break;
            case 'Z' : case 'J' :
            case 'Q' : case 'K' : case 'A' :
                selected_action = HIT;
                break;
            }
        }else if(currentHand->card[0]->faceValue == '4'){
            switch(upcard){
            case '5' : case '6':
                selected_action = SPLIT;
                break;
            case '2' : case '3' : case '4' : case 'Z' : case 'J' :
            case 'Q' : case 'K' : case 'A' : case '7' : case '8' : case '9' :
                selected_action = HIT;
                break;
            }
        }else if(currentHand->card[0]->faceValue == '3' ||
                 currentHand->card[0]->faceValue == '2'){
            switch(upcard){
            case '2' : case '3' : case '4' : case '5' : case '6': case '7' :
                selected_action = SPLIT;
                break;
            case 'Z' : case 'J' :
            case 'Q' : case 'K' : case 'A' : case '8' : case '9' :
                selected_action = HIT;
                break;
            }
        }
    }
    else{
        //can't split
        currentHand->calculateHandValue();
        int value = currentHand->handValue;

        if(value >= 5 && value <= 8){
            selected_action = HIT;
        }else if(value >= 13 && value <= 16){
            switch(upcard){
            case 'Z' : case 'J' : case '7' :
            case 'Q' : case 'K' : case 'A' : case '8' : case '9' :
                selected_action = HIT;
                break;
            }
        }else if(value == 12){
            switch(upcard){
            case '2' : case '3' : case 'Z' : case 'J' : case '7' :
            case 'Q' : case 'K' : case 'A' : case '8' : case '9' :
                selected_action = HIT;
                break;
            }
        }else if(value == 11){
            switch(upcard){
            case '2' : case '3' : case '4' : case '5' : case '6': case '7' :
            case '8' : case '9' : case 'Z' : case 'J' : case 'Q' : case 'K' :
                selected_action = DOUBLE;
                break;
            case 'A' :
                selected_action = HIT;
                break;
            }
        }else if(value == 10){
            switch(upcard){
            case '2' : case '3' : case '4' : case '5' : case '6': case '7' :
            case '8' : case '9' :
                selected_action = DOUBLE;
                break;
            case 'Z' : case 'J' : case 'Q' : case 'K' : case 'A' :
                selected_action = HIT;
                break;
            }
        }else if(value == 9){
            switch(upcard){
            case '3' : case '4' : case '5' : case '6':
                selected_action = DOUBLE;
                break;
            case '2' : case '7' : case '8' : case '9' :
            case 'Z' : case 'J' : case 'Q' : case 'K' : case 'A' :
                selected_action = HIT;
                break;
            }
        }

    }
}

Player* BasicPlayer::cloneMe() const {
    Player* temp = new BasicPlayer(*this);
        return temp;
}

Player* BasicPlayer::clone() const{
    Player* temp = cloneMe();
    temp->hand.clear();

    for(int i = 0; i < this->hand.size(); i++){
        Hand* tempHand =  new Hand(*this->hand[i]);
        temp->hand.push_back(tempHand);
    }

    temp->currentHand = temp->hand[0];
    return temp;
}
