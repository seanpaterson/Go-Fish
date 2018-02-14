//Sean Paterson (c) 4/13/2015
//Go Fish, Homework 1
#include <cstring>
#include <cctype>
#include <iostream>
#include <fstream>
#include <time.h>
#include <stdlib.h>
using namespace std;
//Playing card that is a parent to the node and DLL_node classes
class card
{
	public:
	card();//Safety
	card(int copy_pip);//Takes in a number and paces it in the card
	int display();//Outputs card's number
	int retrieve();//Return's the card's number to the calling function
	int compare(int find_pip);//Checks to see if the number asked is in the card
	protected:
	int pip;//The card's number
};
//Used to create the cards player's hand
class node:public card
{
	public:
	node();//Safety
	node(int copy_pip);//takes in an integer and sends it to the card constructor to create the integer in the card
	node *& go_next();//Allows us to recursively move to the next pointer since next is in private
	int set_next(node *);//Sets the next pointer
	protected:
	node * next;//allows us to create a LLL
};
//Used to create the cards in the deck
class DLL_node:public card
{
	public:
	DLL_node();//Safety
	DLL_node(int copy_pip);//takes in an integer and sends it to the card constructor to create the integer in the card
	DLL_node *& go_next();//Allows us to recursively move to the next pointer since next is in private
	DLL_node *& go_previous();//Allows us to recursively move to the previous pointer since previous is in private
	int set_previous(DLL_node *);//Sets the previous pointer
	int set_next(DLL_node *);//Sets the next pointer
	protected:
	DLL_node * next;//allows us to traverse forward
	DLL_node * previous;//allows us to traverse backward
};
