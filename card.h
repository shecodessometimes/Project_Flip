#pragma once
#ifndef CARD_H
#define CARD_H

class card
{
private:
    int value;
    String suit;
public:
    deck();
    void shuffle();
    card drawTop();
};
#endif