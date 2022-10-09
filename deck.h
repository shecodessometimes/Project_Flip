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
    deck(node<card>* first_card);
    void printDeck();
    void shuffle();
    void insertCard(node<card>* new_card);
    node<card>* drawTop();
    card getCardAtI(int i);
};
#endif