// Header file card.h for the card object.
// Card object implementation
// Assumption: all card values are ints (even face cards)

#pragma once
#ifndef CARD_H
#define CARD_H

class card
{
private:

    int value;          // card value
    std::string suit;   // card suit

public:
    // constructor
    card(const std::string& s, const int& v);

    // copy constructor
    card(const card& obj) : 
        value(obj.value), suit(obj.suit)
        {};

    // card operations

    void setValue(const int& v);
    void setSuit(const std::string& s);
    int getValue() const;
    std::string getSuit() const;
    friend std::ostream& operator << (std::ostream& ostr, const card& rhs);
    card& operator = (const card& rhs);     // is this right??
};

#endif