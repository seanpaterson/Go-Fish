//Sean Paterson Copyright (c) 4/6/2015
//This program is based on the card game Go Fish
#include "general_player.h"

int main ()
{
	deck game_deck;//Creates the game deck
	int asked_card;//Takes in the card number a player is looking for and seeis if it's in the opposing player's hand
	int asked_card_number;//Records how many of a cartain card are in a player's hand
	int winner = 0;
	int go_again = 1;//used in the loops on lines 18 and 46 to loop until that player has to go fish
	general_player player1(game_deck);//Creates player1 and they draw seven nodes(cards)
	computer player2(game_deck);//Creates player2 and they draw seven nodes(cards)
	cout << "The deck has been shuffled and each player's hand has been drawn." << endl;
	cout << "Player 1 will go first." << endl;
	while(!winner)//Will pretty much run forever
	{
		while(go_again == 1)//Will run until the player has to go fish
		{
			cout << "It is your turn. Here is your current hand:  ";
			player1.display_all(); cout << endl;//Displays the player's hand
			cout << "What card will you ask for? ";
			cin >> asked_card; cin.ignore(100,'\n');//Takes in the number the player is asking for
			cout << "You: Do you have any " << asked_card << "s?" << endl;
			asked_card_number = player2.search_hand(asked_card);//Checks to see how many of the asked card are in the opposing player's hand
			if (asked_card_number)//If that player hand any of that card in their hand
			{
				cout << "Computer: here are " << asked_card_number << " " << asked_card << "s." << endl;
				player1.create_card(asked_card,asked_card_number);//Adds the amount of cards from the other players hand to this player's hand
				player2.remove_cards(asked_card);//Remove those cards from the opposing player's hand
				if (player1.search_hand(asked_card) == 4)//If the current player has 4 of a card
				{
					cout << "Found a book!" << endl;
					player1.remove_cards(asked_card);//Remove those cards from the player's hand
				}
			}
			else//If the opposing player didn't have any of the card asked for
			{
				cout << "Computer: Go Fish!" << endl;
				player1.draw_card(game_deck);//Draw a card and add it to the player's hand
				go_again = 0;//Stops the player for asking for another card
			}
			if (player1.win(1)) return 0;//If the player's hand is empty
		}
		go_again = 1;
		while(go_again == 1)
		{
			cout << "It is now the computer's turn!" << endl;
			asked_card = player2.make_card_guess();//Chooses a random card from their hand to ask for
			cout << "Computer: Do you have any " << asked_card << "s?" << endl;
			asked_card_number = player1.search_hand(asked_card);//See's if the other player has it
			if (asked_card_number)
			{
				cout << "Player: here are " << asked_card_number << " " << asked_card << "s." << endl;
				player2.create_card(asked_card,asked_card_number);
				player1.remove_cards(asked_card);
				if (player2.search_hand(asked_card) == 4)
				{
					cout << "Found a book!" << endl;
					player2.remove_cards(asked_card);
				}
			}
			else
			{
				cout << "Player: Go Fish!" << endl;
				player2.draw_card(game_deck);
				go_again = 0;
			}
			if (player2.win(2)) return 0;//Checks to see if the player's had is empty
		}
		go_again = 1;
	}
	return 0;
}
