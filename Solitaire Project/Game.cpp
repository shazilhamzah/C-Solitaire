#include "Game.h"
#include"List.h"
#include<iostream>
#include<string>
#include<string.h>
#include<set>
#include<sstream>
using namespace std;

void Game::__init__()
{
	/* DEFINING VARIABLES*/
	int n = 0;
	
	/* INITIALIZING CARDS */
	Card** cards = new Card * [52];
	initializingCards(cards);


	/* SETTING UP FOR CARDS */
	settingCards(cards, n);

	/* SHUFFLING CARDS */
	shuffle(cards);

	/* PLACING CARDS IN TABLEUS */
	placingInTableu(cards);

	/* PLACING CARDS IN STOCK */
	placingInStock(cards);

	/* PRINTING DECK */
	printDeck();

	string quit = "quit";
	do {
		// INPUTTING COMMAND
		string s;	getline(cin, s);
		Command newCommand;
		newCommand.setCommand(s);

		// ANALYZING THE COMMAND VALIDITY
		if (!analyzeCommandType(newCommand)) {
			cout << "Invalid Command!" << endl;
			continue;
		}
		if (!validateCommandType(newCommand)) {
			cout << "Invalid Command!" << endl;
			continue;
		}

		// PUSHING IT INTO THE STACK
		pushCommand(newCommand);

	} while (!commands.isEmptyStack() && commands.top().getCommand() != quit || !matchWon());
}

void Game::initializingCards(Card** cards)
{
	for (int i = 0; i < 52; i++)
	{
		cards[i] = new Card();
	}
}

void Game::printCards(Card** cards)
{
	for (int i = 0; i < 52; i++)
	{
		cards[i]->print();
	}
}

void Game::settingCards(Card** cards, int& n)
{
	/* SETTING UP DIAMOND CARDS */
	for (int i = 2; i < 11; i++) {
		string c = (i == 10) ? "10" : to_string(i);
		cards[n]->setRank(c);
		n++;
	}
	cards[n]->setRank("A");	n++;
	cards[n]->setRank("J");	n++;
	cards[n]->setRank("K");	n++;
	cards[n]->setRank("Q");	n++;
	for (int i = n - 13; i < n; i++) {
		cards[i]->setSuit("Diamonds");
		cards[i]->setColor("Red");
	}

	/* SETTING UP HEART CARDS */
	for (int i = 2; i < 11; i++) {
		string c = (i == 10) ? "10" : to_string(i);
		cards[n]->setRank(c);
		n++;
	}
	cards[n]->setRank("A");	n++;
	cards[n]->setRank("J");	n++;
	cards[n]->setRank("K");	n++;
	cards[n]->setRank("Q");	n++;
	for (int i = n - 13; i < n; i++) {
		cards[i]->setSuit("Hearts");
		cards[i]->setColor("Red");
	}

	/* SETTING UP SPADE CARDS */
	for (int i = 2; i < 11; i++) {
		string c = (i == 10) ? "10" : to_string(i);
		cards[n]->setRank(c);
		n++;
	}
	cards[n]->setRank("A");	n++;
	cards[n]->setRank("J");	n++;
	cards[n]->setRank("K");	n++;
	cards[n]->setRank("Q");	n++;
	for (int i = n - 13; i < n; i++) {
		cards[i]->setSuit("Spades");
		cards[i]->setColor("Black");
	}
	/* SETTING UP CLUB CARDS */
	for (int i = 2; i < 11; i++) {
		string c = (i == 10) ? "10" : to_string(i);
		cards[n]->setRank(c);
		n++;
	}
	cards[n]->setRank("A");	n++;
	cards[n]->setRank("J");	n++;
	cards[n]->setRank("K");	n++;
	cards[n]->setRank("Q");	n++;
	for (int i = n - 13; i < n; i++) {
		cards[i]->setSuit("Clubs");
		cards[i]->setColor("Black");
	}
}

void Game::shuffle(Card**& cards)
{
	Stack<Card>randomCards(52);
	srand(time(0));

	for (int i = 0; i < 52; i++)
	{
		int r = i + (rand() % (52 - i));
		swap(cards[i], cards[r]);
	}
}

void Game::placingInTableu(Card**& cards)
{
	int n = 0;
	t1.insertAtTail(cards[n][0]);	n++;

	t2.insertAtTail(cards[n][0]);	n++;
	t2.insertAtTail(cards[n][0]);	n++;

	t3.insertAtTail(cards[n][0]);	n++;
	t3.insertAtTail(cards[n][0]);	n++;
	t3.insertAtTail(cards[n][0]);	n++;

	t4.insertAtTail(cards[n][0]);	n++;
	t4.insertAtTail(cards[n][0]);	n++;
	t4.insertAtTail(cards[n][0]);	n++;
	t4.insertAtTail(cards[n][0]);	n++;

	t5.insertAtTail(cards[n][0]);	n++;
	t5.insertAtTail(cards[n][0]);	n++;
	t5.insertAtTail(cards[n][0]);	n++;
	t5.insertAtTail(cards[n][0]);	n++;
	t5.insertAtTail(cards[n][0]);	n++;

	t6.insertAtTail(cards[n][0]);	n++;
	t6.insertAtTail(cards[n][0]);	n++;
	t6.insertAtTail(cards[n][0]);	n++;
	t6.insertAtTail(cards[n][0]);	n++;
	t6.insertAtTail(cards[n][0]);	n++;
	t6.insertAtTail(cards[n][0]);	n++;

	t7.insertAtTail(cards[n][0]);	n++;
	t7.insertAtTail(cards[n][0]);	n++;
	t7.insertAtTail(cards[n][0]);	n++;
	t7.insertAtTail(cards[n][0]);	n++;
	t7.insertAtTail(cards[n][0]);	n++;
	t7.insertAtTail(cards[n][0]);	n++;
	t7.insertAtTail(cards[n][0]);	n++;
}

void Game::placingInStock(Card**& cards)
{
	for (int i = 28; i < 52; i++)
	{
		this->Stock.push(cards[i][0]);
	}
}

void Game::printDeck()
{
	/* PRINTING TABELUES */
	List<Card>whatTablue;
	string s;
	List<Card>::Iterator i1;
	
	for (int i = 1; i <= 7; i++)
	{
		if (i == 1) { whatTablue = t1; s = "Tabelue 1:\n"; }
		else if (i == 2) { whatTablue = t2; s = "Tabelue 2:\n"; }
		else if (i == 3) { whatTablue = t3; s = "Tabelue 3:\n"; }
		else if (i == 4) { whatTablue = t4; s = "Tabelue 4:\n"; }
		else if (i == 5) { whatTablue = t5; s = "Tabelue 5:\n"; }
		else if (i == 6) { whatTablue = t6; s = "Tabelue 6:\n"; }
		else if (i == 7) { whatTablue = t7; s = "Tabelue 7:\n"; }
		cout << s;
		i1 = whatTablue.begin();
		for (int j = 0; j < i; j++) {
			++i1;
			Card newCard = *i1;
			newCard.print();
		}
		cout << endl;
	}

	/* PRINTING STOCKS */
	Stack<Card> tempStack(24);
	cout << "Stock: " << endl;
	for (int i = 0; i < 24; i++)
	{
		Card tempCard = Stock.pop();
		tempCard.print();
		tempStack.push(tempCard);
	}
	for (int i = 0; i < 24; i++)
	{
		Card tempCard = tempStack.pop();
		Stock.push(tempCard);
	}
}

bool Game::matchWon()
{
	if (Foundation1.getStackTop() == 13 && Foundation2.getStackTop() == 13 && Foundation3.getStackTop() == 13 && Foundation4.getStackTop() == 13) {
		return true;
	}
	return false;
}

void Game::pushCommand(Command& tempCommand)
{
	if (commands.isFullStack()) {
		Stack<Command>tempStack(5);
		tempStack.push(tempCommand);
		for (int i = 0; i < 4; i++)
		{
			tempStack.push(commands.pop());
		}
		commands.pop();
		for (int i = 0; i < 5; i++)
		{
			commands.push(tempStack.pop());
		}
	}
	else {
		commands.push(tempCommand);
	}
	cout << endl << endl;
	Stack<Command>temp(5);
	int n = commands.getStackTop();
	for (int i = 0; i < n; i++)
	{
		cout << commands.top().getCommand() << endl;
		temp.push(commands.pop());
	}
	for (int i = 0; i < n; i++)
	{
		commands.push(temp.pop());
	}
}

bool Game::analyzeCommandType(Command& command) {
	string s = command.getCommand();
	cout << "Analyzing command: " << s << endl; // Debug output
	if (s[0] == 'm' && s[1] == ' ' && s[2] == 'w') {
		command.setCommandType("m w");
		return true;
	}
	else if (s[0] == 'm') {
		command.setCommandType("m");
		return true;
	}
	else if (s == "s") {
		command.setCommandType("s");
		return true;
	}
	else if (s == "z") {
		command.setCommandType("z");
		return true;
	}
	return false;
}

bool Game::validateCommandType(Command& command) {
	string cmdType = command.getCommandType();
	string cmd = command.getCommand();
	if (cmdType == "m" && cmd.length()==9) {
		char a = cmd[1];
		char b = cmd[2];
		char c = cmd[3];
		char d = cmd[4];
		char e = cmd[5];
		char f = cmd[6];
		char g = cmd[7];
		char h = cmd[8];
		if (a == ' ' && b == 'c' && (c-'0' > 0 && c-'0' < 8) && d == ',' && e == 'c' && (f-'0' > 0 && f-'0' < 8) && g == ',' && (h-'0' > 0 && h-'0' < 11)) {
			cout << "Command is valid!" << endl;
			return true;
		}
	}
	else if (cmdType == "z") {
		return command.getCommand() == "z";
	}
	else if (cmdType == "m w" && cmd.length()==8	) {
		char a = cmd[3];
		char b = cmd[4];
		char c = cmd[5];
		char d = cmd[6];
		char e = cmd[7];
		if (a == ',' && b == 'c' && (c - '0' > 0 && c - '0' < 8) && d == ',' && (e - '0' > 0 && e - '0' < 11)) {
			cout << "Command is valid!" << endl;
			return true;
		}
	}
	else if (cmdType == "s") {
		return command.getCommand() == "s";
	}

	return false; 
}

Game::Game()
	:t1(), t2(), t3(), t4(), t5(), t6(), t7(),
	Stock(24), WastePile(24), Foundation1(13), Foundation2(13),
	Foundation3(13), Foundation4(13), commands(5)
{
	__init__();
}