#pragma once
#ifndef CARD_H
#define CARD_H

class card
{
private:
    int value;
    String suit;
public:
    card(int v, int s);
    printCard();
};
#endif