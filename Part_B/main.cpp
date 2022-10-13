///////////////////////////////////////////////////////////////////////////////
// Project#2
// Flip-Card: Part A
// Written by:
// James Napier:                                      napier.j@northeastern.edu
// Julia Rasmussen:                                rasmussen.j@northeastern.edu
// Samuel Sheehan:                                   sheehan.s@northeastern.edu
//
// Main program file for homework 2a. Contains declarations for 
// deck, shuffle, printDeck, << operator overload for the card object, setValue,
// getValue, setSuit and getSuit
//
///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <tuple>
#include "d_node.h"
#include "card.h"
#include "deck.h"

using namespace std;

//=============================================================================
// Deck Methods
//=============================================================================

deck::deck()
/*
* Initializes the deck object, in 1-13 and suit order.
*/
{
    string suit_list[] = { "club", "diamond", "heart", "spade" };
    for (int s = 0; s < 4; s++)
    // loop for each suit
    {
        for (int n = 1; n < 14; n++)
        // loop for each card in suit
        {
            // create new card pointer
            node<card> *newCard;
            if (s == 0 && n == 1)
            // checks if first card
            {
                // create new card, set to front
                card new_card(suit_list[s], n);
                newCard = new node<card>(new_card, NULL);
                front = newCard;
                back = newCard;
            }
            else
            // if not first card
            {
                // set front
                node<card>* curr;
                curr = front;
                while (curr->next != NULL)
                // nagivate to end of current deck
                {
                    curr = curr->next;
                }
                // create new card, set current->next to new card
                card new_card(suit_list[s], n);
                newCard = new node<card>(new_card, NULL);
                curr->next = newCard;
                back = newCard;
            }
        }
    }
} // end of deck constructor

void deck::shuffle()
/*
* Shuffle the deck represented by the deck
* object according to Fisher-Yates shuffle.
* https://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle
* Assumption: Deck has 52 items exactly
*/
{
    // create tracking pointers for swapped cards (1st and 2nd)
    node<card> *curr1;
    node<card> *prev1;
    node<card> *curr2;
    node<card> *prev2;
    // Set curr1 to first card
    curr1 = front;
    for (int ind = 0; ind < 50; ind++)
    // completes operation for each card except the last
    {
        // seed psuedo-random number generator
        srand(time(NULL));
        int off = 52 - ind;
        int swap_ind = rand() % off + ind;
        if (ind != swap_ind)
        {
            // set 1st card's previous and current values
            // set 2nd card's current value to 1st card's current value
            if (ind != 0)
            {
                prev1 = curr1;
                curr1 = curr1->next;
                curr2 = curr1;
            }
            else
            // base case: set 2nd card's current value to front card
            // 1st card's previous value is unneeded because it is the front
            {
                curr2 = curr1;
            }
            // base case: do not move card if swap_ind = ind
            if (swap_ind != ind)
            {
                for (int ind2 = ind; ind2 < swap_ind; ind2++)
                // navigate to 2nd card to be swapped
                {
                    prev2 = curr2;
                    curr2 = curr2->next;
                }
                // instantiate temporary card pointer to store swapped card
                node<card>* temp;
                if (ind == 0)
                // base case: 1st card is the front card
                {
                    front = curr2;
                    prev2->next = curr1;
                    // use temporary card pointer to store 1st card
                    temp = curr1->next;
                    curr1->next = curr2->next;
                    curr2->next = temp;
                    // reset 1st card pointer to the 2nd card
                    // (fixes 1st card current pointer back for future)
                    curr1 = curr2;
                }
                else
                {
                    prev1->next = curr2;
                    prev2->next = curr1;
                    // use temporary card pointer to store 1t card
                    temp = curr1->next;
                    curr1->next = curr2->next;
                    curr2->next = temp;
                    // reset 1st card pointer to the 2nd card
                    // (fixes 1st card current pointer back for future)
                    curr1 = curr2;
                }
            }
        }
        else
        // card is randomly chosen to stay in it's original position
        {
            curr1 = curr1->next;
        }
    }
} // End of shuffle

ostream& operator << (ostream& ostr, const deck& rhs)
/*
* overloads the << operator for the deck class
* Iterates through each node in the linked list
* and utilizes the overloaded << operator for 
* the card object in the current node's nodeValue.
* Finishes after printing the last node
*/
{
    node<card> *curr;
    curr = rhs.front;
    cout << "\n====================\n";
    while (curr != NULL)
    // loop until end of list
    {
        // print card values to command line
        cout << curr->nodeValue << endl;
        curr = curr->next;
    }
    cout << "====================\n";

    return ostr;
}

//=============================================================================
// Card Methods
//=============================================================================

card::card(const string& s, const int& v)
/*
* Initializes the card object.
* v: integer v, the numerical value of the card (1 is ace,
* 11 is jack, 12 is queen, 13 is king).
* s: integer s, the suit of the card (0 = hearts, 1 = suits, etc.)
*/
{
    value = v;
    suit = s;
}

ostream& operator << (ostream& ostr, const card& rhs)
/*
* Overrides the << function for a card.
* ostr: the ostream to print to.
* rhs: the response to print out.
*/
{
    // card is ace
    if (rhs.getValue() == 1)
    {
        ostr << "Ace";
    }
    // card is 2 - 10
    else if (rhs.getValue() < 11)
    {
        ostr << rhs.getValue();
    }
    // card is jack
    else if (rhs.getValue() == 11)
    {
        ostr << "Jack";
    }
    // card is queen
    else if (rhs.getValue() == 12)
    {
        ostr << "Queen";
    }
    // card is king
    else
    {
        ostr << "King";
    }
    char first_char = toupper(rhs.getSuit()[0]);
    ostr << " of " << first_char << rhs.getSuit().substr(1) << "s.";
    return ostr;
} // end of << overload


void card::setValue(const int& v)
/*
* Sets the value of the card to v
* v: integer between 1 and 13 inclusive.
* Invalid inputs are rejected and user is prompted again
*/
{
    // looping condition
    bool valid = false;
    // loop until input is valid
    while (!valid)
    {
        // set value if valid and break loop
        if (v > 0 && v < 14)
        {
            valid = true;
            value = v;
        }
        // reject value if not within v accept
        else
        {// Header file deck.h for the Deck object.
// Deck object implementation
// Assumption: a deck contains 52 cards after construction
            cout << "\nInvalid value, please try again";
        }
    }
} // end of setValue


int card::getValue() const
/*
* returns int value from card
*/
{
    return value;
}


void card::setSuit(const string& s)
/*
* Sets the suit of the card to s
* s: club, diamond, heart, or spade
* Invalid inputs are rejected and user is prompted again
*/
{
    // looping condition
    bool valid = false;
    cout << "\nPlease enter a suit (lowercase):";
    // loop until input is valid
    while (!valid)
    {
        // set value if valid and break loop
        if (s == "club" || s == "diamond" || s == "heart" || s == "spade")
        {
            valid = true;
            suit = s;
        }
        // reject value if not within s accept
        else
        {
            cout << "\nInvalid suit, please try again.";
        }
    }
} // End of setSuit


string card::getSuit() const
/*
* returns string suit from card
*/
{
    return suit;
}

//=============================================================================
// 
//=============================================================================

int main()
{
    //initialize the deck, shuffle, then draw.
    deck gameDeck;
    cout << "Unshuffled Deck: ";
    cout << gameDeck;
    gameDeck.shuffle();
    cout << endl << "Shuffled Deck: " << endl << gameDeck;
}
