//Sean Paterson (c) 4/13/2015
//Go Fish, Homework 1
//Deck will have an array of doubly-linked-lists. Array will be of size 4 since there are five suits
#include "node.h"
class deck
{
	public:
		deck();//Calls the create deck function to create the game deck
		deck(deck &);//Copy constructor
		~deck();//Destructs the array of DLLs
		int create_deck();//Creates a deck of 52 cards
		int draw_from_deck();//Randomly decides which index to draw from and which DLL node to delete
		int delete_from_deck(int node_number, int current_suit);//wrapper function for the delete_from deck
		int display_all();//Wrapper function for display all
		int delete_all();//Wrapper function of delete_all
		int copy_deck(deck &);//Wrapper function for copy function

	protected:
		int display_all(DLL_node * head);//Displays all cards in the deck. We don't really need this but it's nice to have
		int delete_from_deck(int node_number, int current_node, DLL_node *& head);//Removes a random card from the deck. This is (in a way) the shuffle function
		int delete_all(DLL_node *& head);//Deletes all remaining DLL_nodes in the deck
		int copy_deck(DLL_node *& head,DLL_node * copy_head);//Copies a deck completely
		DLL_node ** head;//Creates an array of DLLs. No suit class since the array is of size 4. 4 x 13 = 52
		int SIZE;//Sets the number of DLLs in our deck
		int cards_per_suit;//Used to remember how many DLL nodes are in each DLL
		int counts[4];//Sets the integers in each index to 13 since there are 13 cards of each suit
};


