////////////////////////////////////////////////////////////////
// Project Flip: Part A
// Written by James Napier, Julia Rasmussen, and Samuel Sheehan
////////////////////////////////////////////////////////////////
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

/*
* Initializes the deck object, in 1-13 and suit order.
*/
deck::deck()
{
    //linked list of a deck
    string suit_list[] = { "club", "diamond", "heart", "spade" };
    for (int s = 0; s < 4; s++)
    {
        for (int n = 1; n < 14; n++)
        {
            node<card>* newCard;
            //checks if first card
            if (s == 0 && n == 1)
            {
                card new_card(suit_list[s], n);
                newCard = new node<card>(new_card, NULL);
                front = newCard;
                back = newCard;
            }
            else
            {
                node<card>* curr;
                curr = front;
                while (curr->next != NULL)
                {
                    curr = curr->next;
                }
                card new_card(suit_list[s], n);
                newCard = new node<card>(new_card, NULL);
                curr->next = newCard;
                back = newCard;
            }
        }
    }
}

/*
* Initializes the deck object with single card.
*/
deck::deck(node<card>* first_card)
{
    front = first_card;
    back = first_card;
}


/*
* Shuffle the deck represented by the deck object.
*/
void deck::shuffle()
{
    node<card>* curr1;
    node<card>* prev1;
    node<card>* curr2;
    node<card>* prev2;
    curr1 = front;
    for (int ind = 0; ind < 50; ind++)
    {
        srand(time(NULL));
        int off = 51 - ind;
        int swap_ind = rand() % off + ind;
        if (ind != swap_ind)
        {
            if (ind != 0)
            {
                prev1 = curr1;
                curr1 = curr1->next;
                curr2 = curr1;
                card temp3 = prev1->nodeValue;
                card temp4 = curr1->nodeValue;
            }
            else
            {
                curr2 = curr1;
            }
            if (swap_ind != ind)
            {
                for (int ind2 = ind; ind2 < swap_ind; ind2++)
                {
                    prev2 = curr2;
                    curr2 = curr2->next;
                    card temp3 = prev2->nodeValue;
                    card temp4 = curr2->nodeValue;
                }

                node<card>* temp;
                if (ind == 0)
                {
                    front = curr2;
                    prev2->next = curr1;
                    temp = curr1->next;
                    curr1->next = curr2->next;
                    curr2->next = temp;
                    curr1 = curr2;
                }
                else
                {
                    prev1->next = curr2;
                    prev2->next = curr1;
                    temp = curr1->next;
                    curr1->next = curr2->next;
                    curr2->next = temp;
                    curr1 = curr2;
                }
            }
        }
    }
}

void deck::printDeck()
{
    node<card>* curr;
    curr = front;
    while (curr != NULL)
    {
        cout << curr->nodeValue << endl;
        curr = curr->next;
    }

}

card deck::getCardAtI(int i)
{
    node<card>* current_card;
    current_card = front;
    for (int n = 0; n < i; n++)
    {
        current_card = current_card->next;
    }
    return current_card->nodeValue;
}

node<card>* deck::drawTop()
{
    //get top card
    node<card>* top_card;
    top_card = front;

    //reassign next card as top
    front = top_card->next;
    top_card->next = NULL;

    //return top_card
    return top_card;
}

void deck::insertCard(node<card>* new_card)
{

    //reassign the new card as top
    new_card->next = front;
    front = new_card;
}

//=============================================================================
// Card Methods
//=============================================================================

/*
* Initializes the card object.
* v: integer v, the numerical value of the card (1 is ace, 11 is jack, 12 is queen, 13 is king).
* s: integer s, the suit of the card (0 = hearts, 1 = suits, etc.)
*/
card::card(const string& s, const int& v)                       // Done
{
    value = v;
    suit = s;
}

/*
* Overrides the << function for a card.
* ostr: the ostream to print to.
* rhs: the response to print out.
*/
ostream& operator << (ostream& ostr, const card& rhs)
{
    //card is ace
    if (rhs.getValue() == 1)
    {
        ostr << "Ace";
    }
    //card is 2 - 10
    else if (rhs.getValue() < 11)
    {
        ostr << rhs.getValue();
    }
    //card is jack
    else if (rhs.getValue() == 11)
    {
        ostr << "Jack";
    }
    else if (rhs.getValue() == 12)
    {
        ostr << "Queen";
    }
    else
    {
        ostr << "King";
    }
    char first_char = toupper(rhs.getSuit()[0]);
    ostr << " of " << first_char << rhs.getSuit().substr(1) << "s.";
    return ostr;
}


void card::setValue(const int& v)                               // Doneish
{
    bool valid = false;
    while (!valid)
    {
        if (v > 0 && v < 13)
        {
            valid == true;
        }
        else
        {
            cout << "\nInvalid value, please try again";
        }
    }
    value = v;
}


int card::getValue() const                                           // Doneish
{
    return value;
}


void card::setSuit(const string& s)                             // Doneish
{
    bool valid = false;
    cout << "\nPlease enter a suit (lowercase):";
    while (!valid)
    {
        valid = true;
        if (s == "club" || s == "diamond" || s == "heart" || s == "spade")
        {
            suit = s;
        }
        else
        {
            valid = false;
            cout << "\nInvalid suit, please try again.";
        }
    }
}


string card::getSuit() const
{
    return suit;
}

//=============================================================================
// 
//=============================================================================

int main()
{
    //print the welcome message
    cout << "==================================================================\n";
    cout << "Welcome to Card Flip!\n";
    cout << "You will draw from one of 24 cards from a shuffled deck.\n";
    cout << "If you draw an ace, you get 10 points.\n";
    cout << "If you draw a king, queen, or jack you get 5 points.\n";
    cout << "If you draw an 8, 9, or 10, you get 0 points.\n";
    cout << "If you draw a 7, you lose half your points.\n";
    cout << "If you draw a 2, 3, 4, 5, or 6, you lose all your points.\n";
    cout << "Additionally, if you draw a heart you gain a point!\n";
    cout << "You can end the game any time. Good luck!\n";
    cout << "==================================================================\n";

    //initialize the deck, shuffle, then draw.
    deck gameDeck;
    for (int i = 0; i < 3; i++)
    {
        gameDeck.shuffle();
    }

    //initialize the smaller deck of 25 cards by drawing the top card of the deck.
    node<card>* top_card = gameDeck.drawTop();
    deck top25(top_card);

    //only 24 more cards, because the first was already drawn.
    for (int i = 0; i < 24; i++)
    {
        node<card>* next_card = gameDeck.drawTop();
        top25.insertCard(next_card);
    }

    //print the deck with the top 25 cards
    top25.printDeck();

    //initialize the keep_playing character
    char keep_playing = 'y';

    //keep drawing a card until the user wants to stop.
    while (keep_playing == 'y')
    {
        //ask for index of a card
        cout << "What card would you like to draw? ";
        int card_index = 0;
        cin >> card_index;
        cout << "You chose " << top25.getCardAtI(card_index) << " ";

        //*************************************************************************!
        //calculate points for the drawn card and store it
        //*************************************************************************!

        //initialize the user_input character
        char user_input = 'a';

        //ask if user wants to keep playing
        while (1 == 1)
        {
            cout << "Would you like to draw another card (y) or quit (n)? ";
            cin >> user_input;
            if (user_input == 'y' | user_input == 'n')
            {
                break;
            }
        }

        //assign the user_input character to the keep_playing character
        keep_playing = user_input;
    }
}
