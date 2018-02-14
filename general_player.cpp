#include "general_player.h"
//Sean Paterson (c) 4/13/2015
//Go Fish, Homework 1
//Default
hand::hand()
{
	head = NULL;
}
//Used to draw a player's hand
hand::hand(deck & game_deck)
{
	head = NULL;
	draw_hand(game_deck);//Draws seven nodes for the hand
}
//Copy constructor
hand::hand(hand & to_copy)
{
	head = NULL;
	copy_hand(to_copy);//Copies all nodes in a hand
}
//Will draw a card for the player's hand seven times
int hand::draw_hand(deck & game_deck)
{
	for (int i = 0;i < 7;++i)
	{
		draw_card(game_deck);
	}
	return 1;
	
}
//Adds a card to a player's hand at the head
int hand::draw_card(deck & game_deck)
{
	int drawn_number = 0;
	node * temp;
	drawn_number = game_deck.draw_from_deck();//Draws a number from the deck and places it in the player's hand
	if(drawn_number == 0)//if the deck is empty then the player doesn't draw a card
	{
		return 0;
	}
	else //If there was a card in the deck to draw
	{
		temp = head;
		head = new node(drawn_number);
		head->set_next(temp);
	}
	if (search_hand(drawn_number) == 4)//If we search the hand and there is four of a kind in the deck
	{
		remove_cards(drawn_number);//Remove those cards from your hand
		cout << "Found a book!" << endl;
	}
	return 1;
	
}
//Wrapper function
int hand::display_all()
{
	display_all(head);
}
//Recursively display all nodes in a hand
int hand::display_all(node * head)
{
	if (!head) return 0;
	head->display();//Display what's at head
	display_all(head->go_next());//goes to the next in the LLL
}
//Wrapper function
int hand::search_hand(int find_number)
{
	return search_hand(find_number,head);
}
//Searches the LLL for a cartain number and returns then number of nodes that contained that number
int hand::search_hand(int find_number,node * head)
{
	if (!head) return 0;//If we are at the end of the list
	if (head->compare(find_number))//If the number we are searching for is in this node
	{
		return search_hand(find_number,head->go_next()) + 1;//Recursively call the next node
	}
	return search_hand(find_number,head->go_next());
}
//Wrapper function
int hand::remove_cards(int find_number)
{
	return remove_cards (find_number,head);
}
//Will delete cards that have the number we want to remove from the hand
int hand::remove_cards(int find_number, node *& head)
{
	node * temp;
	if (!head) return 0;//If were at the end of the list
	remove_cards(find_number,head->go_next());
	if (head->compare(find_number))//If we have found a card we want to delete
	{
		temp = head;
		head = head->go_next();
		delete temp;
		temp = NULL;
	}
	return 1;
}
//Used to represent puting the cards from the opposing player's hand into your hand
int hand::create_card(int copy_pip,int amount_of_card)
{
	node * temp;
	for (int i = 0;i < amount_of_card;++i)//While we still haven't created all of the cards to add to the hand
	{
		temp = head;
		head = new node(copy_pip);
		head->set_next(temp);
	}
	return 1;
}
//Wrapper function
int hand::delete_all()
{
	delete_all(head);
	return 1;
}
//Deletes all nodes in the hand
int hand::delete_all(node *& head)
{
	if (!head) return 0;
	delete_all(head->go_next());
	delete head;
	head = NULL;
	return 1;
}
//Wrapper function for copy hand
int hand::copy_hand(hand & to_copy)
{
	copy_hand(head,to_copy.head);
	return 1;
}
//Copies an entire hand of nodes (cards)
int hand::copy_hand(node *& head,node * copy_head)
{
	if(!copy_head) return 0;//If we are at the end of the LLL we want to copy from
	head = new node(copy_head->retrieve());//Place the data in the node we want to copy into the node were creating
	copy_hand(head->go_next(),copy_head->go_next());
	return 1;
}
//Destructor for the hand
hand::~hand()
{
	delete_all();
}
//Default constructor that has the default constructor for hand in it's derivation list
general_player::general_player():hand(){}

//Has the hand constructor in derivation list
general_player::general_player(deck & game_deck):hand(game_deck){}

//Used to check if the player has won the game
int general_player::win(int player_number)
{
	if (!head)//If the player has no cards in hand
	{
		cout << "Player " << player_number << " wins!" << endl;
		return 1;
	}
	return 0;
}

//Default constructor that uses the default constructor of general_player in it's derivation list
computer::computer():general_player(){}

//Default constructor for C -> GP -> H
computer::computer(deck & game_deck):general_player(game_deck){}

//Wrapper function
int computer::check_hand_size()
{
	return check_hand_size(head);
}

//Counts the number of nodes in the computer's hand
int computer::check_hand_size(node * head)
{
	if (!head) return 0;
	return (check_hand_size(head->go_next()) + 1);
}

//Wrapper function
int computer::make_card_guess()
{
	int card_guess = rand() % check_hand_size();//Chooses a random card to ask for by choosing which node to stop at
	int current_node = 0;
	return make_card_guess(card_guess,current_node,head); 
}
//Recursively calls to the node we want to ask for. Then we return that nodes card number to the calling routine
int computer::make_card_guess(int card_guess,int current_node,node * head)
{
	int found_card;//Hold the card number we found in the LLL
	if (!head) return 0;//If we have traversed to the end of the node
	found_card = make_card_guess(card_guess,(current_node + 1),head->go_next());
	if (card_guess == current_node)//If we have stopped and the node we want to stop at
	{
		found_card = head->retrieve();// Places the number in the current node into the found_card variable that will be returned to the calling routine
	}
	return found_card;
}
