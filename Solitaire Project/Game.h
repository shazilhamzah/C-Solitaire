#pragma once
#include"Card.h"
#include"List.h"
#include"Stack.h"
#include"Command.h"
#include<string>
#include<string.h>

class Game {
	List<Card>t1;
	List<Card>t2;
	List<Card>t3;
	List<Card>t4;
	List<Card>t5;
	List<Card>t6;
	List<Card>t7;
	Stack<Card>Stock;
	Stack<Card>WastePile;
	Stack<Card>Foundation1;
	Stack<Card>Foundation2;
	Stack<Card>Foundation3;
	Stack<Card>Foundation4;
	Stack<Command>commands;

public:
	Game();
	void __init__();
	void initializingCards(Card** cards);
	void printCards(Card** cards);
	void settingCards(Card** cards, int& n);
	void shuffle(Card**& cards);
	void placingInTableu(Card**& cards);
	void placingInStock(Card**& cards);
	void printDeck();
	bool matchWon();
	void pushCommand(Command& tempCommand);
	bool analyzeCommandType(Command& command);
	bool validateCommandType(Command& command);
	void stockToWaste();
};