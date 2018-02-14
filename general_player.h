#include "deck.h"
//Sean Paterson (c) 4/13/2015
//Go fish
class hand
{
		public:
		hand();//Safety
                hand(deck &);//Take in deck, calls draw_hand(), and constructs the player's hand
		hand(hand &);//Copy constructor
		~hand();
                int display_all();//Wrapper function used to output the entire player's hand
                int search_hand(int find_number);//Wrapper function for search hand
                int remove_cards(int find_number);//Wrapper funstion to remove cards
                int draw_hand(deck &);//Used in the constructor to draw each player's seven cards
                int draw_card(deck &);//Calls the draw_from_deck function which returns a number from the deck
                int create_card(int copy_pip,int amount_of_card);//Creates a certain numbers
		int delete_all();//Wrapper function for delete all
		int copy_hand(hand &);//Copy function
		protected:
		node * head;//LLL which will act as the player's hand
                int display_all(node * head);//Traverses the player's hand and outputs the number on each card
                int search_hand(int find_number,node * head);//Used to see how mant of certain type of card is in your hand
                int remove_cards(int find_number,node *& head);//Removes cards of a certain number from your hand
		int delete_all(node *& head);//Deletes all nodes in a hand
		int copy_hand(node *& head,node * copy_head);//Copies an entire hand
};
//Parent of both player and computer since there are only a few differences between the two child classes
class general_player:public hand
{
	public:
		general_player();//Safety
		general_player(deck &);//Take in deck, calls draw_hand(), and constructs the player's hand
		int win(int player_number);//Checks to see if the player's hand is NULL
	protected:
};

//Child class of general_player
class computer:public general_player
{
	public:
		computer();//Safety
		computer(deck &);//Will use general_player in it's derivation list
		int check_hand_size();//Wrapper function for the check hand size function
		int make_card_guess();//Wrapper function for the make card guess funtion
	protected:
		int check_hand_size(node * head);//Traverses the list and counts all nodes in the computer's hand
		int make_card_guess(int card_guess,int current_node,node * head);//Traverses until the desired node has been found
};
