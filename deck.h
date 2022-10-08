#pragma once
#ifndef DECK_H
#define DECK_H

#include "d_node.h"

class deck
{
private:
    //card linked list
    node<card>* front;
    node<card>* back;
public:
    deck();
    void printDeck();
    void shuffle();
    card drawTop();
    card getCardAtI(int i);
};
#endif