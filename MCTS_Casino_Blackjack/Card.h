#ifndef CARD
#define CARD

enum Suit{
    HEARTS,
    SPADES,
    DIAMONDS,
    CLUBS,
    ERROR
};

//Character Z represents the number 10 on the face

class Card{
public:
    Card(int faceValue, int suit);
    Card(const Card&);

    char faceValue;
    Suit suit;

    void printCard();
};

#endif // CARD
