#pragma once
#ifndef DECK_H
#define DECK_H

#include "card.h"

class deck
{
    private:
        //card linked list
    public:
        deck();
        void shuffle();
        card drawTop();
};
#endif