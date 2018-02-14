//Sean Paterson (c) 4/13/2015
//Go Fish, Homework 1
#include "node.h"

card::card()
{
	pip = 0;
}

card::card(int copy_pip)
{
	pip = copy_pip;
}
//Displays the number on a single card
int card::display()
{
	cout << pip << " ";
	return 1;
}

//Returns the card's number to the calling function
int card::retrieve()
{
	return pip;
}

//Compares a card number with another. If they are the same then we return true
int card::compare(int find_pip)
{
	if(find_pip == pip)
	{
		return 1;
	}
	return 0;
}

//Default Constructor
node::node():card(),next(NULL){}

//Calls the card constructor
node::node(int copy_pip):card(copy_pip),next(NULL){}

//Connects the a node to it's next node
int node::set_next(node * copy_next)
{
	next = copy_next;
}

//Our OOP version of head->next since we can't access another node's next ptr
node *& node::go_next()
{
	return next;
}

//Default constructor
DLL_node::DLL_node():card(),previous(NULL),next(NULL){}

//Calls the card constructor
DLL_node::DLL_node(int copy_pip):card(copy_pip),previous(NULL),next(NULL){}

//Connects the a node to it's next node
int DLL_node::set_next(DLL_node * copy_next)
{
	next = copy_next;
}

//Connects the a node to it's previous node
int DLL_node::set_previous(DLL_node * copy_previous)
{
	previous = copy_previous;
}

//Our OOP version of head->next since we can't access another node's next ptr
DLL_node *& DLL_node::go_next()
{
	return next;
}

//Our OOP version of head->previous since we can't access another node's previous ptr
DLL_node *& DLL_node::go_previous()
{
	return previous;
}

