// Header file deck.h for the Deck object.
// Deck object implementation
// Assumption: a deck contains 52 cards after construction

#pragma once
#ifndef DECK_H
#define DECK_H

#include "d_node.h"

class deck
{
private:
    // card linked list front and back

    node<card>* front;  // front card
    node<card>* back;   // back card

public:
    // constructor
    deck();

    // overloaded constructor for empty deck
    deck(bool a);

    // destructor
    ~deck();

    // deck operations
    card deal();
    void replace(const card& obj);
    void printDeck();
    void shuffle();
    card getCardAtI(int i);
    friend std::ostream& operator << (std::ostream& ostr, const deck& rhs);

}; // end of deck class
#endif // End of header file.