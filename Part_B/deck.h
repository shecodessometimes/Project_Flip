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

    // deck operations
    card getCardAtI(const int& i) const;
    void printDeck();
    void shuffle();
    friend std::ostream& operator << (std::ostream& ostr, const deck& rhs);

}; // end of deck class
#endif // End of header file.