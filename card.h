#pragma once
#ifndef CARD_H
#define CARD_H

class card
{
private:
    int value;
    std::string suit;
public:
    card(const std::string& s, const int& v);
    void setValue(const int& v);
    void setSuit(const std::string& s);
    int getValue() const;
    std::string getSuit() const;
    friend std::ostream& operator << (std::ostream& ostr, const card& rhs);
};

#endif