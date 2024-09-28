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

		printDeck();

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
	int size = Stock.getStackTop();
	cout << "Stock: " << endl;
	for (int i = 0; i < size; i++)
	{
		Card tempCard = Stock.pop();
		tempCard.print();
		tempStack.push(tempCard);
	}
	for (int i = 0; i < size; i++)
	{
		Card tempCard = tempStack.pop();
		Stock.push(tempCard);
	}
	
	/* PRINTING WASTE */
	Stack<Card> tempStack1(24);
	int size1 = WastePile.getStackTop();
	cout << "Waste: " << endl;
	for (int i = 0; i < size1; i++)
	{
		Card tempCard = WastePile.pop();
		tempCard.print();
		tempStack1.push(tempCard);
	}
	for (int i = 0; i < size1; i++)
	{
		Card tempCard = tempStack1.pop();
		WastePile.push(tempCard);
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
	if (cmdType == "m" && cmd.length() == 9) {
		char a = cmd[1];
		char b = cmd[2];
		char c = cmd[3];
		char d = cmd[4];
		char e = cmd[5];
		char f = cmd[6];
		char g = cmd[7];
		char h = cmd[8];
		if (a == ' ' && b == 'c' && (c - '0' > 0 && c - '0' < 8) && d == ',' && e == 'c' && (f - '0' > 0 && f - '0' < 8) && g == ',' && (h - '0' > 0 && h - '0' < 11)) {
			// CHECKING COLUMNS
			List<Card>whatColumn1;
			List<Card>whatColumn2;
			if (c - '0' == 1)whatColumn1 = t1;
			else if (c - '0' == 2)whatColumn1 = t2;
			else if (c - '0' == 3)whatColumn1 = t3;
			else if (c - '0' == 4)whatColumn1 = t4;
			else if (c - '0' == 5)whatColumn1 = t5;
			else if (c - '0' == 6)whatColumn1 = t6;
			else if (c - '0' == 7)whatColumn1 = t7;
			if (f - '0' == 1)whatColumn2 = t1;
			else if (f - '0' == 2)whatColumn2 = t2;
			else if (f - '0' == 3)whatColumn2 = t3;
			else if (f - '0' == 4)whatColumn2 = t4;
			else if (f - '0' == 5)whatColumn2 = t5;
			else if (f - '0' == 6)whatColumn2 = t6;
			else if (f - '0' == 7)whatColumn2 = t7;

			// MOVING LOGIC USING ITERATORS
			string arr[13] = { "A","2","3","4","5","6","7","8","9","10","Q","K" };
			for (int i = 0; i < h-'0'; i++)
			{
				if (whatColumn1.isEmpty()) {
					cout << "Not enough cards in column " << (c - '0') << endl;
					return true;
				}
				List<Card>::Iterator it1 = whatColumn1.end();	--it1;
				List<Card>::Iterator it2 = whatColumn2.end();	--it2;
				Card column1Card = *it1;	Card column2Card = *it2;
				if (column1Card.getColor() != column2Card.getColor()) {
					int index1;
					int index2;
					for (int i = 0; i < 13; i++)
					{
						if (column1Card.getRank() == arr[i]) {
							index1 = i;
						}
					}
					for (int i = 0; i < 13; i++)
					{
						if (column2Card.getRank() == arr[i]) {
							index2 = i;
						}
					}
					if (index1 == index2 - 1) {
						whatColumn1.removeLastElement();
						whatColumn2.insertAtTail(column2Card);
					}
					else {
						cout << "First tablue card must be one less in rank to move!" << endl;
					}
				}
				else {
					cout << "Top cards must be opposite in color to move!" << endl;
				}
			}

			return true;
		}
	}
	else if (cmdType == "m" && cmd.length() == 9 && cmd[1] == 'c' && cmd[3] == 'f') {
		char c = cmd[2];  
		char f = cmd[4];  
		char p = cmd[6];  

		if ((c - '0' > 0 && c - '0' < 8) && (f - '0' > 0 && f - '0' < 5) && (p - '0' == 1)) {
			List<Card> whatColumn;
			if (c - '0' == 1) whatColumn = t1;
			else if (c - '0' == 2) whatColumn = t2;
			else if (c - '0' == 3) whatColumn = t3;
			else if (c - '0' == 4) whatColumn = t4;
			else if (c - '0' == 5) whatColumn = t5;
			else if (c - '0' == 6) whatColumn = t6;
			else if (c - '0' == 7) whatColumn = t7;

			if (whatColumn.isEmpty()) {
				cout << "Column " << c << " is empty!" << endl;
				return true;
			}

			List<Card>::Iterator it = whatColumn.end();
			--it;
			Card columnCard = *it;

			Stack<Card>* foundation = nullptr;
			if (f - '0' == 1) foundation = &Foundation1;
			else if (f - '0' == 2) foundation = &Foundation2;
			else if (f - '0' == 3) foundation = &Foundation3;
			else if (f - '0' == 4) foundation = &Foundation4;

			if (foundation != nullptr) {
				if (foundation->isEmptyStack()) {
					if (columnCard.getRank() == "A") {
						whatColumn.removeLastElement();
						foundation->push(columnCard);
						cout << "Moved " << columnCard.getRank() << " of " << columnCard.getSuit() << " to Foundation " << f << endl;
					}
					else {
						cout << "Only Ace can be placed in an empty foundation." << endl;
					}
				}
				else {
					Card foundationCard = foundation->top();

					string arr[13] = { "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };
					int index1 = -1, index2 = -1;

					for (int i = 0; i < 13; i++) {
						if (columnCard.getRank() == arr[i]) {
							index1 = i;
						}
						if (foundationCard.getRank() == arr[i]) {
							index2 = i;
						}
					}

					if (columnCard.getSuit() == foundationCard.getSuit() && index1 == index2 + 1) {
						whatColumn.removeLastElement();
						foundation->push(columnCard);
						cout << "Moved " << columnCard.getRank() << " of " << columnCard.getSuit() << " to Foundation " << f << endl;
					}
					else {
						cout << "Invalid move! The foundation card must be one less in rank and match the suit." << endl;
					}
				}
			}
			return true;
		}
	}
	else if (cmdType == "m" && cmd.length() == 9 && cmd[1] == 'w' && cmd[3] == 'f') {
		char f = cmd[4];   
		char p = cmd[6];

		if ((f - '0' > 0 && f - '0' < 5) && (p - '0' == 1)) {
			if (WastePile.isEmptyStack()) {
				cout << "Waste pile is empty!" << endl;
				return true;
			}

			Card wasteCard = WastePile.top();

			Stack<Card>* foundation = nullptr;
			if (f - '0' == 1) foundation = &Foundation1;
			else if (f - '0' == 2) foundation = &Foundation2;
			else if (f - '0' == 3) foundation = &Foundation3;
			else if (f - '0' == 4) foundation = &Foundation4;

			if (foundation != nullptr) {
				if (foundation->isEmptyStack()) {
					if (wasteCard.getRank() == "A") {
						WastePile.pop();
						foundation->push(wasteCard);
						cout << "Moved " << wasteCard.getRank() << " of " << wasteCard.getSuit() << " from Waste to Foundation " << f << endl;
					}
					else {
						cout << "Only Ace can be placed in an empty foundation." << endl;
					}
				}
				else {
					Card foundationCard = foundation->top();

					string arr[13] = { "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };
					int index1 = -1, index2 = -1;

					for (int i = 0; i < 13; i++) {
						if (wasteCard.getRank() == arr[i]) {
							index1 = i;
						}
						if (foundationCard.getRank() == arr[i]) {
							index2 = i;
						}
					}

					if (wasteCard.getSuit() == foundationCard.getSuit() && index1 == index2 + 1) {
						WastePile.pop();
						foundation->push(wasteCard);
						cout << "Moved " << wasteCard.getRank() << " of " << wasteCard.getSuit() << " from Waste to Foundation " << f << endl;
					}
					else {
						cout << "Invalid move! The foundation card must be one less in rank and match the suit." << endl;
					}
				}
			}
			return true;
		}
		}

	else if (cmdType == "z") {
		return command.getCommand() == "z";
	}
	else if (cmdType == "m w" && cmd.length() == 8) {
		char a = cmd[3];
		char b = cmd[4];
		char c = cmd[5];
		char d = cmd[6];
		char e = cmd[7];
		if (a == ',' && b == 'c' && (c - '0' > 0 && c - '0' < 8) && d == ',' && (e - '0' > 0 && e - '0' < 11)) {
			// CHECKING COLUMNS
			List<Card>whatColumn2;
			if (c - '0' == 1)whatColumn2 = t1;
			else if (c - '0' == 2)whatColumn2 = t2;
			else if (c - '0' == 3)whatColumn2 = t3;
			else if (c - '0' == 4)whatColumn2 = t4;
			else if (c - '0' == 5)whatColumn2 = t5;
			else if (c - '0' == 6)whatColumn2 = t6;
			else if (c - '0' == 7)whatColumn2 = t7;

			// MOVING LOGIC USING ITERATORS
			string arr[13] = { "A","2","3","4","5","6","7","8","9","10","Q","K" };
			for (int i = 0; i < e - '0'; i++)
			{
				if (WastePile.isEmptyStack()) {
					cout << "Not enough cards in waste stack!" << endl;
					List<Card>::Iterator it = whatColumn2.end();  --it;
					Card column2Card = *it;
					Card wasteCard = WastePile.top();
					if (wasteCard.getColor() != column2Card.getColor()) {
						int index1;
						int index2;
						for (int i = 0; i < 13; i++)
						{
							if (wasteCard.getRank() == arr[i]) {
								index1 = i;
							}
						}
						for (int i = 0; i < 13; i++)
						{
							if (column2Card.getRank() == arr[i]) {
								index2 = i;
							}
						}
						if (index1 == index2 - 1) {
							WastePile.pop();
							whatColumn2.insertAtTail(wasteCard);
						}
						else {
							cout << "Waste stack card must be one less in rank to move!" << endl;
						}

					}
					else {
						cout << "Top cards must be opposite in color to move!" << endl;
					}
					return true;
				}
			}
			return true;
		}
	}
	else if (cmdType == "s") {
		if (command.getCommand() == "s") {
			stockToWaste();
			return true;
		}
	}
	return false; 
}

void Game::stockToWaste()
{
	if (!Stock.isEmptyStack()) {
		WastePile.push(Stock.pop());
	}
}

Game::Game()
	:t1(), t2(), t3(), t4(), t5(), t6(), t7(),
	Stock(24), WastePile(24), Foundation1(13), Foundation2(13),
	Foundation3(13), Foundation4(13), commands(5)
{
	__init__();
}