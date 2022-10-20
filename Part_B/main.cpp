///////////////////////////////////////////////////////////////////////////////
// Project#2
// Flip-Card: Part B
// Written by:
// James Napier:                                      napier.j@northeastern.edu
// Julia Rasmussen:                                rasmussen.j@northeastern.edu
// Samuel Sheehan:                                   sheehan.s@northeastern.edu
//
// Main program file for homework 2b. Contains declarations for 
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
#pragma region Deck
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
            node<card>* newCard;
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

deck::~deck()
{
    node<card>* current;
    node<card>* next;
    current = front;
    while (current != NULL)
    {
        next = current->next;
        delete current;
        current = next;
    }
    front = NULL;
    back = NULL;
}

void deck::shuffle()
/*
* Shuffle the deck represented by the deck
* object according to Fisher-Yates shuffle.
* https://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle
* Assumption: Deck has 52 items exactly
*/
{
    // create tracking pointers for swapped cards (1st and 2nd)
    node<card>* curr1;
    node<card>* prev1;
    node<card>* curr2;
    node<card>* prev2;
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
                    if (ind == 49)
                    {
                        temp = curr1;
                        while (temp->next != NULL)
                        {
                            temp = temp->next;
                        }
                        back = temp;
                    }
                }
            }
        }
        else
            // card is randomly chosen to stay in it's original position
        {
            curr1 = curr1->next;
            if (ind == 49)
            {
                while (curr1->next != NULL)
                {
                    curr1 = curr1->next;
                }
                back = curr1;
            }
        }
    }
} // End of shuffle

card deck::getCardAtI(int i)
{
    node<card>* current_card;
    node<card>* prev_card;
    current_card = front;
    prev_card = front;

    if (i == 0)
    {
        card drawnCard = front->nodeValue;
        node<card>* front_del = front;
        front = front->next;
        delete front_del;
        return drawnCard;
    }

    for (int n = 0; n < i; n++)
    {
        //only moves pointer for current_card forward if on the first iteration.
        if (n == 0)
        {
            current_card = current_card->next;
        }
        else
        {
            current_card = current_card->next;
            prev_card = prev_card->next;
        }
    }
    card drawnCard = current_card->nodeValue;
    prev_card->next = current_card->next;
    delete current_card;
    return drawnCard;
}

ostream& operator << (ostream& ostr, const deck& rhs)
/*
* overloads the << operator for the deck class
* Iterates through each node in the linked list
* and utilizes the overloaded << operator for
* the card object in the current node's nodeValue.
* Finishes after printing the last node
*/
{
    node<card>* curr;
    curr = rhs.front;
    cout << "\n==================================================================\n";
    while (curr != NULL)
        // loop until end of list
    {
        // print card values to command line
        cout << curr->nodeValue << endl;
        curr = curr->next;
    }
    cout << "\n==================================================================\n";

    return ostr;
}

card deck::deal()                                       // Tested
{
    card newCard(front->nodeValue);
    node<card>* temp;
    temp = front->next;
    delete front;
    front = temp;
    return newCard;
}

void deck::replace(const card& obj)                     // Tested
{
    node<card>* newCard;
    newCard = new node<card>(obj, NULL);
    if (front == NULL)
    {
        front = newCard;
        back = newCard;
    }
    else
    {
        back->next = newCard;
        back = newCard;
    }
}
#pragma endregion Deck
//=============================================================================
// Card Methods
//=============================================================================
#pragma region Card
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

card& card::operator=(const card& obj)
/*
* Overloaded = operator
*/
{
    value = obj.value;
    suit = obj.suit;
    return *this;
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
#pragma endregion Card
//=============================================================================
void playFlip()
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

    // make gameDeck
    deck gameDeck;
    // empty deck for play prep  
    gameDeck.~deck();
    // make drawDeck and play prep
    deck drawDeck;
    //shuffle the initial deck three times
    for (int i = 0; i < 3; i++)
    {
        drawDeck.shuffle();
    }

    // loop to draw 24 cards into gameDeck
    for (int i = 0; i < 24; i++)
    {
        gameDeck.replace(drawDeck.deal());
    }

    // debug printing for grading
    cout << endl << "Remaining Cards in Original Deck: " << endl << drawDeck;
    cout << endl << "Game Deck: " << endl << gameDeck;

    //initialize the keep_playing character
    char keep_playing = 'y';

    //keep drawing a card until the user wants to stop.
    while (keep_playing == 'y')
    {
        //ask for index of a card
        cout << "What card would you like to draw? ";
        int card_index = 0;
        cin >> card_index;
        cout << "You chose " << gameDeck.getCardAtI(card_index) << " ";

        //*************************************************************************!
        //calculate points for the drawn card and store it
        //*************************************************************************!

        cout << "\n==================================================================\n";
        cout << endl << "Remaining Cards for Game: " << endl << gameDeck;

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
//=============================================================================

int main()
{
    //initialize the deck, shuffle, then draw.
    playFlip();
    /*
    deck drawDeck;
    deck gameDeck;
    gameDeck.~deck();
    cout << "Unshuffled Deck: ";
    cout << gameDeck;
    drawDeck.shuffle();
    cout << endl << "Shuffled Deck: " << endl << drawDeck;
    cout << "This is for debugging";
    gameDeck.replace(drawDeck.deal());
    cout << "This is for debugging" << endl << gameDeck;
    */
}
