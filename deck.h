#pragma once
#ifndef DECK_H
#define DECK_H

#include "d_node.h"

class deck
{
    private:
        //card linked list
        node<card> front;

    public:
        deck();
        void shuffle();
        card drawTop();
};
#endif