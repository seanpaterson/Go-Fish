#include "deck.h"
//Sean Paterson (c) 4/13/2015
//Go Fish, Homework 1
//Default Constructor
deck::deck()
{

	srand(time(NULL));
	SIZE = 4;//Size of the array of DLLs
	cards_per_suit = 13;//Number of cards in each array
	head = new DLL_node * [SIZE];//Allocates memory for the array
	for (int i = 0;i < SIZE;++i)//Sets each head in the array to null
	{
		head[i] = NULL;
		counts[i] = 13;//Whenever a card is drawn from an array index, we negate 1 from that index
	}
	create_deck();//Calls a function that will create the DLLs in each array index
}
//Copy Constructor (However we do not need it for this program)
deck::deck(deck & copy_from)
{
	SIZE = 4;
	head = new DLL_node * [SIZE];
	for(int i = 0;i < SIZE; ++i)
	{
		counts[i] = copy_from.counts[i];//Takes the current number of DLL_nodes in each index of the array were copying from
	}
	copy_deck(copy_from);//Calls the wrapper function to copy all nodes from the deck
}
//Creates thirteen DLL_nodes in each array index (13 x 4 = 52)
int deck::create_deck()
{
	DLL_node * temp;
	//Runs until each index has thirteen DLL_nodes
	for (int i = 0;i <SIZE;++i)
	{
		head[i] = new DLL_node(1);//Creates the first node in the list
		for (int j = 2;j <= cards_per_suit;++j)//Creates 12 more nodes
		{
			temp = head[i];//Sets temp equal to head
			head[i] = new DLL_node(j);//Creates new node at head
			head[i]->set_next(temp);//Sets head's next to temp
			temp->set_previous(head[i]);//Set's previous to head
		}
	}
	
}
//Deletes a random card from the deck and returns a number to the player class
int deck::draw_from_deck()
{
	int random_suit;//Decides which suit we will draw from
	int suit_node_number;//Decides which node we will delete from the deck
	int draw_tries = 0;//Records how many time we've tried drawing from the deck
	do{
		random_suit = rand() % SIZE;//Picks random suit to draw from
		if (counts[random_suit])suit_node_number = rand() % counts[random_suit];//Chooses a random node to delete from the deck
		++draw_tries;
	
	}while(!head[random_suit]||draw_tries == 30);//Will run until weve tried drawing from the deck 30 times or 
	if (draw_tries == 30)//If the deck is empty
	{
		cout << "The deck is empty! You do not draw a card." << endl;
		return 0;
	}
	--counts[random_suit];//Records that a card has been drawn from the current index
	return delete_from_deck(suit_node_number,random_suit);//Returns the card number we drew from the deck
	
	
}
//Wrapper function for delete from deck
int deck::delete_from_deck(int node_number,int current_suit)
{
	int current_node = 0;//Sets the node we are currently on
	return delete_from_deck(node_number, current_node, head[current_suit]);//Returns the card number to the calling routine
		
}
//Traverses recursively until we have found the node we want to delete. if the node we are currently on is the one we want to delete, then we delete it
int deck::delete_from_deck(int node_number, int current_node, DLL_node *& head)
{
	int returned_number = 0;//If we find the node we want, then we place it's contense into this variable and returns it to the calling routine
	if (!head) return 0;//If were at the end of the list
	DLL_node * temp = head;
	returned_number = delete_from_deck(node_number,(current_node + 1),head->go_next());//Recursively calls the function 
	if (node_number == current_node)//If we have traversed to the node we want to stop at
	{
		returned_number = head->retrieve();//Retrieves the number found in the node
		if (!head->go_next()&&!head->go_previous())//If the node in the deck is the last one
		{
		delete head;
		head = NULL;
		}
		else if (!head->go_next())//If there is no head->next
		{
			delete head;
			head = NULL;
		}
		else if (!head->go_previous())//If there is no previous
		{
			head = head->go_next();
			head->set_previous(NULL);
			delete temp;
		}
		else//If we are just in the middle ofthe DLL
		{
			temp->go_previous()->set_next(temp->go_next());
			temp->go_next()->set_previous(temp->go_previous());
			delete temp;
			temp = NULL;
		}
		
	}
	return returned_number;//Return the number to the calling routine
}
//Wrapper function for Display_all
int deck::display_all()
{
	for(int i = 0;i < SIZE;++i)
	{
		display_all(head[i]);
		cout << endl;
	}
}
//Displays all DLL_nodes in the deck(Not used in the program)
int deck::display_all(DLL_node * head)
{
	if(!head) return 0;
	head->display();
	display_all(head->go_next());
}
//Wrapper function to delete all DLL_nodes in the deck
int deck::delete_all()
{
	for(int i = 0;i < 4;++i)
	{
		delete_all(head[i]);
	}
	delete []  head;
}
//Deletes all DLL_nodes in the deck
int deck::delete_all(DLL_node *& head)
{
	if (!head) return 0;
	delete_all(head->go_next());
	delete head;
	head = NULL;
	return 1;
}
//Wrapper function to copy_all nodes from another deck
int deck::copy_deck(deck & copy_from)
{
	for(int i = 0;i < SIZE;++i)
	{
		copy_deck(head[i],copy_from.head[i]);
	}
	return 1;
}
//copy_all nodes from another deck
int deck::copy_deck(DLL_node *& head,DLL_node * copy_head)
{
	if(!copy_head) return 0;//If the DLL we want to copy is empty
	if (!head)//If this is the first node we've put in the deck
	{
		head = new DLL_node(copy_head->retrieve());//takes the number from the node we want to copy and copies it into this new node
	}
	if(copy_head->go_next())//If there is a next DLL node in the DLL we want to copy
	{
		DLL_node * temp = new DLL_node(copy_head->go_next()->retrieve());
		head->set_next(temp);
		temp->set_previous(head);
	}
	copy_deck(head->go_next(),copy_head->go_next());
	
}
//Destructor
deck::~deck()
{
	delete_all();	
}
