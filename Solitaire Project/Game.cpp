#include "Game.h"
#include"List.h"
#include<iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <locale>
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

	/* MAKING TOP VISIBLE */
	makeTopVisible();

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

		system("cls");

		/* MAKING TOP VISIBLE */
		//makeTopVisible();

		// PRINTING DECK
		printDeck();
		printDeck1();

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

void Game::printDeck1()
{
	/* PRINTING TABLEAUS */
	List<Card> whatTableau; int tSize;
	string s;
	List<Card>::Iterator i1;

	for (int i = 1; i <= 7; i++)
	{
		if (i == 1) { whatTableau = t1; s = "Tableau 1:\n"; }
		else if (i == 2) { whatTableau = t2; s = "Tableau 2:\n"; }
		else if (i == 3) { whatTableau = t3; s = "Tableau 3:\n"; }
		else if (i == 4) { whatTableau = t4; s = "Tableau 4:\n"; }
		else if (i == 5) { whatTableau = t5; s = "Tableau 5:\n"; }
		else if (i == 6) { whatTableau = t6; s = "Tableau 6:\n"; }
		else if (i == 7) { whatTableau = t7; s = "Tableau 7:\n"; }

		cout << s;
		i1 = whatTableau.begin();
		for (i1 = whatTableau.end(); --i1!=whatTableau.begin();) {
			Card newCard = *i1;
			newCard.print();
		}
		cout << endl;
	}

	/* PRINTING STOCK */
	Stack<Card> tempStockStack(24);
	int stockSize = Stock.getStackTop();
	cout << "Stock: " << endl;
	for (int i = 0; i < stockSize; i++)
	{
		Card tempCard = Stock.pop();
		tempCard.print();
		tempStockStack.push(tempCard);
	}
	for (int i = 0; i < stockSize; i++)
	{
		Card tempCard = tempStockStack.pop();
		Stock.push(tempCard);
	}

	/* PRINTING WASTE */
	Stack<Card> tempWasteStack(24);
	int wasteSize = WastePile.getStackTop();
	cout << "Waste: " << endl;
	for (int i = 0; i < wasteSize; i++)
	{
		Card tempCard = WastePile.pop();
		tempCard.print();
		tempWasteStack.push(tempCard);
	}
	for (int i = 0; i < wasteSize; i++)
	{
		Card tempCard = tempWasteStack.pop();
		WastePile.push(tempCard);
	}

	/* PRINTING FOUNDATIONS */
	// Foundation 1
	Stack<Card> tempFoundationStack1(13);
	int foundationSize1 = Foundation1.getStackTop();
	cout << "Foundation 1: " << endl;
	for (int i = 0; i < foundationSize1; i++)
	{
		Card tempCard = Foundation1.pop();
		tempCard.print();
		tempFoundationStack1.push(tempCard);
	}
	for (int i = 0; i < foundationSize1; i++)
	{
		Card tempCard = tempFoundationStack1.pop();
		Foundation1.push(tempCard);
	}

	// Foundation 2
	Stack<Card> tempFoundationStack2(13);
	int foundationSize2 = Foundation2.getStackTop();
	cout << "Foundation 2: " << endl;
	for (int i = 0; i < foundationSize2; i++)
	{
		Card tempCard = Foundation2.pop();
		tempCard.print();
		tempFoundationStack2.push(tempCard);
	}
	for (int i = 0; i < foundationSize2; i++)
	{
		Card tempCard = tempFoundationStack2.pop();
		Foundation2.push(tempCard);
	}

	// Foundation 3
	Stack<Card> tempFoundationStack3(13);
	int foundationSize3 = Foundation3.getStackTop();
	cout << "Foundation 3: " << endl;
	for (int i = 0; i < foundationSize3; i++)
	{
		Card tempCard = Foundation3.pop();
		tempCard.print();
		tempFoundationStack3.push(tempCard);
	}
	for (int i = 0; i < foundationSize3; i++)
	{
		Card tempCard = tempFoundationStack3.pop();
		Foundation3.push(tempCard);
	}

	// Foundation 4
	Stack<Card> tempFoundationStack4(13);
	int foundationSize4 = Foundation4.getStackTop();
	cout << "Foundation 4: " << endl;
	for (int i = 0; i < foundationSize4; i++)
	{
		Card tempCard = Foundation4.pop();
		tempCard.print();
		tempFoundationStack4.push(tempCard);
	}
	for (int i = 0; i < foundationSize4; i++)
	{
		Card tempCard = tempFoundationStack4.pop();
		Foundation4.push(tempCard);
	}
}

string whatColor(string s) {
	const std::string RED = "\033[31m";
	const std::string BLACK = "\033[30m";
	const std::string RESET = "\033[0m";
	const std::string BOLD = "\033[1m";
	if (s == "Red") {
		return RED;
	}
	else {
		return "";
	}
}

void Game::printDeck()
{
	const std::string RED = "\033[31m";
	const std::string BLACK = "\033[30m";
	const std::string RESET = "\033[0m";
	const std::string BOLD = "\033[1m";

	// ROW 1 - TOP HEADINGS
	cout << "STOCK\t\tWASTE\t\t\tFOUNDATION 1\tFOUNDATION 2\tFOUNDATION 3\tFOUNDATION 4\n";

	//ROW 2	- TOP CARD
	cout << "[  ]\t\t";
	if (!WastePile.isEmptyStack()) {
		string s = whatColor(WastePile.top().getColor());
		cout << s << WastePile.top().getRank() << " of " << WastePile.top().getSuit() << RESET << "\t\t";
	}
	else {
		cout << "[  ]\t\t\t";
	}
	if (!Foundation1.isEmptyStack()) {
		string s = whatColor(Foundation1.top().getColor());
		cout << s << Foundation1.top().getRank() << " of " << Foundation1.top().getSuit() << RESET<<"\t";
	}
	else {
		cout << "[  ]\t\t";
	}
	if (!Foundation2.isEmptyStack()) {
		string s = whatColor(Foundation2.top().getColor());
		cout << s << Foundation2.top().getRank() << " of " << Foundation2.top().getSuit() << RESET << "\t";
	}
	else {
		cout << "[  ]\t\t";
	}
	if (!Foundation3.isEmptyStack()) {
		string s = whatColor(Foundation3.top().getColor());
		cout << s << Foundation3.top().getRank() << " of " << Foundation3.top().getSuit() << RESET << "\t";
	}
	else {
		cout << "[  ]\t\t";
	}
	if (!Foundation4.isEmptyStack()) {
		string s = whatColor(Foundation4.top().getColor());
		cout << s << Foundation4.top().getRank() << " of " << Foundation4.top().getSuit() << RESET << "\n";
	}
	else {
		cout << "[  ]\n";
	}

	// ROW 3 - CARD COUNTS
	cout << "(" << Stock.getStackTop() << " cards)\t" << "(" << WastePile.getStackTop() << " cards)\t\t" << "(" << Foundation1.getStackTop() << " cards)\t" << "(" << Foundation2.getStackTop() << " cards)\t" << Foundation3.getStackTop() << " cards)\t" << Foundation4.getStackTop() << " cards)\n\n\n";

	// ROW 4 - COLUMN HEADINGS
	cout << "Column 1\t" << "Column 2\t" << "Column 3\t" << "Column 4\t" << "Column 5\t" << "Column 6\t" << "Column 7\t" << endl;

	// ROW 5 - COLUMN CARD COUNTS
	cout << "(" << t1.getLength() << " cards)\t" << "(" << t2.getLength() << " cards)\t" << "(" << t3.getLength() << " cards)\t" << "(" << t4.getLength() << " cards)\t" << "(" << t5.getLength() << " cards)\t" << "(" << t6.getLength() << " cards)\t" << "(" << t7.getLength() << " cards)\n\n";

	// ROW 6 - CARDS
	List<Card> whatTableau; int tSize;
	string s;
	List<Card>::Iterator i1 = t1.end(); --i1;
	List<Card>::Iterator i2 = t2.end(); --i2;
	List<Card>::Iterator i3 = t3.end(); --i3;
	List<Card>::Iterator i4 = t4.end(); --i4;
	List<Card>::Iterator i5 = t5.end(); --i5;
	List<Card>::Iterator i6 = t6.end(); --i6;
	List<Card>::Iterator i7 = t7.end(); --i7;
	List<Card>::Iterator whatIterator;
	int findMax[7] = { t1.getLength(),t2.getLength(),t3.getLength() ,t4.getLength() ,t5.getLength() ,t6.getLength() ,t7.getLength() };
	int max=0;
	for (int i = 0; i < 7; i++) {
		if (findMax[i] > max) {
			max = findMax[i];
		}
	}

	for (int j = 0; j < max; j++) {
		for (int i = 1; i <= 7; i++) {
			// Select the correct column
			List<Card>::Iterator whatIterator;
			if (i == 1 && j < t1.getLength()) { whatIterator = i1; }
			else if (i == 2 && j < t2.getLength()) { whatIterator = i2; }
			else if (i == 3 && j < t3.getLength()) { whatIterator = i3; }
			else if (i == 4 && j < t4.getLength()) { whatIterator = i4; }
			else if (i == 5 && j < t5.getLength()) { whatIterator = i5; }
			else if (i == 6 && j < t6.getLength()) { whatIterator = i6; }
			else if (i == 7 && j < t7.getLength()) { whatIterator = i7; }
			else { // No more cards in this column, print empty space
				cout << "\t\t";
				continue;
			}

			// Print the card
			Card tmpCard = *whatIterator;
			if (tmpCard.getColor() == "Red" || tmpCard.getColor() == "Black") {
				if (tmpCard.getHide()) {
					cout << "[  ]\t\t";
				}
				else {
					string s = whatColor(tmpCard.getColor());
					cout << s << tmpCard.getRank() << " of " << tmpCard.getSuit() << RESET << "\t";
				}
			}

			// Decrement the iterator if there are more cards left to print
			if (i == 1 && i1 != t1.begin()) --i1;
			else if (i == 2 && i2 != t2.begin()) --i2;
			else if (i == 3 && i3 != t3.begin()) --i3;
			else if (i == 4 && i4 != t4.begin()) --i4;
			else if (i == 5 && i5 != t5.begin()) --i5;
			else if (i == 6 && i6 != t6.begin()) --i6;
			else if (i == 7 && i7 != t7.begin()) --i7;
		}
		cout << endl;
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
			return tablueToTablue(c, f, h);
		}
		else if (a == ' ' && b == 'c' && (c - '0' > 0 && c - '0' < 8) && d == ',' && e == 'f' && (f - '0' > 0 && f - '0' < 5) && g == ',' && (h - '0' > 0 && h - '0' < 11)) {
			return TablueToFoundation(c, f, h);
		}
	}
	else if (cmdType == "z") {
		return undoLastMove();
	}
	else if (cmdType == "m w" && cmd.length() == 8) {
		char a = cmd[3];
		char b = cmd[4];
		char c = cmd[5];
		char d = cmd[6];
		char e = cmd[7];
		if (a == ',' && b == 'c' && (c - '0' > 0 && c - '0' < 8) && d == ',' && (e - '0' > 0 && e - '0' < 11)) {
			return wasteToTablue(c, e);
		}
		else if (a == ',' && b == 'f' && (c - '0' > 0 && c - '0' < 5) && d == ',' && (e - '0' > 0 && e - '0' < 11)) {
			return wasteToFoundation(c, e);
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

bool Game::wasteToFoundation(char c, char e)
{
	Stack<Card>foundation(13);
	if (c - '0' == 1)foundation = Foundation1;
	else if (c - '0' == 2)foundation = Foundation2;
	else if (c - '0' == 3)foundation = Foundation3;
	else if (c - '0' == 4)foundation = Foundation4;
	string arr[13] = { "A","2","3","4","5","6","7","8","9","10","Q","K" };
	for (int i = 0; i < e - '0'; i++) {
		if (WastePile.isEmptyStack()) {
			cout << "Not enough cards in waste stack!" << endl;
			return true;
		}
		else {
			Card wasteCard = WastePile.top();
			if (foundation.isEmptyStack()) {
				if (wasteCard.getRank() == "A") {
					WastePile.pop();
					foundation.push(wasteCard);
					cout << "Moved " << wasteCard.getRank() << " of " << wasteCard.getSuit() << " to Foundation " << c - '0' << endl;
					if (c - '0' == 1)Foundation1 = foundation;
					else if (c - '0' == 2)Foundation2 = foundation;
					else if (c - '0' == 3)Foundation3 = foundation;
					else if (c - '0' == 4)Foundation4 = foundation;
					return true;
				}
				else {
					cout << "Only Ace can be placed in an empty foundation." << endl;
				}
			}
			else {
				Card foundationCard = foundation.top();
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
					foundation.push(wasteCard);
					if (c - '0' == 1)Foundation1 = foundation;
					else if (c - '0' == 2)Foundation2 = foundation;
					else if (c - '0' == 3)Foundation3 = foundation;
					else if (c - '0' == 4)Foundation4 = foundation;
					cout << "Moved " << wasteCard.getRank() << " of " << wasteCard.getSuit() << " to Foundation " << c - '0' << endl;
				}
				else {
					cout << "Invalid move! The foundation card must be one less in rank and match the suit." << endl;
				}
			}
		}
	}
	return true;
}

bool Game::wasteToTablue(char c, char e)
{
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
			return true;
		}
		else {
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
					wasteCard.setHide(false);
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

bool Game::TablueToFoundation(char c, char f, char h)
{
	List<Card>whatColumn1;
	Stack<Card>foundation(13);
	if (c - '0' == 1)whatColumn1 = t1;
	else if (c - '0' == 2)whatColumn1 = t2;
	else if (c - '0' == 3)whatColumn1 = t3;
	else if (c - '0' == 4)whatColumn1 = t4;
	else if (c - '0' == 5)whatColumn1 = t5;
	else if (c - '0' == 6)whatColumn1 = t6;
	else if (c - '0' == 7)whatColumn1 = t7;
	if (f - '0' == 1)foundation = Foundation1;
	else if (f - '0' == 2)foundation = Foundation2;
	else if (f - '0' == 3)foundation = Foundation3;
	else if (f - '0' == 4)foundation = Foundation4;

	// MOVING LOGIC USING ITERATORS
	string arr[13] = { "A","2","3","4","5","6","7","8","9","10","Q","K" };
	for (int i = 0; i < h - '0'; i++)
	{
		if (whatColumn1.isEmpty()) {
			cout << "Not enough cards in column " << (c - '0') << endl;
			return true;
		}
		else {
			List<Card>::Iterator it = whatColumn1.end();	--it;
			Card whatCard = *it;
			if (foundation.isEmptyStack()) {
				whatCard.print();
				if (whatCard.getRank() == "A") {
					whatColumn1.removeLastElement();
					foundation.push(whatCard);
					cout << "Moved " << whatCard.getRank() << " of " << whatCard.getSuit() << " to Foundation " << f - '0' << endl;
					if (f - '0' == 1)Foundation1 = foundation;
					else if (f - '0' == 2)Foundation2 = foundation;
					else if (f - '0' == 3)Foundation3 = foundation;
					else if (f - '0' == 4)Foundation4 = foundation;
					return true;
				}
				else {
					cout << "Only Ace can be placed in an empty foundation." << endl;
				}

			}
			else {
				Card foundationCard = foundation.top();
				int index1 = -1, index2 = -1;
				for (int i = 0; i < 13; i++) {
					if (whatCard.getRank() == arr[i]) {
						index1 = i;
					}
					if (foundationCard.getRank() == arr[i]) {
						index2 = i;
					}
				}
				if (whatCard.getSuit() == foundationCard.getSuit() && index1 == index2 + 1) {
					WastePile.pop();
					foundation.push(whatCard);
					if (c - '0' == 1)Foundation1 = foundation;
					else if (c - '0' == 2)Foundation2 = foundation;
					else if (c - '0' == 3)Foundation3 = foundation;
					else if (c - '0' == 4)Foundation4 = foundation;
					cout << "Moved " << whatCard.getRank() << " of " << whatCard.getSuit() << " to Foundation " << f - '0' << endl;
				}
				else {
					cout << "Invalid move! The foundation card must be one less in rank and match the suit." << endl;
				}

			}
		}
	}
	return true;
}

bool Game::tablueToTablue(char c, char f, char h)
{
	// CHECKING COLUMNS
	List<Card> whatColumn1;
	List<Card> whatColumn2;

	if (c - '0' == 1) whatColumn1 = t1;
	else if (c - '0' == 2) whatColumn1 = t2;
	else if (c - '0' == 3) whatColumn1 = t3;
	else if (c - '0' == 4) whatColumn1 = t4;
	else if (c - '0' == 5) whatColumn1 = t5;
	else if (c - '0' == 6) whatColumn1 = t6;
	else if (c - '0' == 7) whatColumn1 = t7;

	if (f - '0' == 1) whatColumn2 = t1;
	else if (f - '0' == 2) whatColumn2 = t2;
	else if (f - '0' == 3) whatColumn2 = t3;
	else if (f - '0' == 4) whatColumn2 = t4;
	else if (f - '0' == 5) whatColumn2 = t5;
	else if (f - '0' == 6) whatColumn2 = t6;
	else if (f - '0' == 7) whatColumn2 = t7;

	string arr[13] = { "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };  

	for (int i = 0; i < h - '0'; i++)
	{
		if (whatColumn1.isEmpty()) {
			cout << "Not enough cards in column " << (c - '0') << endl;
			return true;
		}
		List<Card>::Iterator it1 = whatColumn1.end();	--it1;  
		List<Card>::Iterator it2 = whatColumn2.end();	--it2; 

		Card column1Card = *it1;
		Card column2Card = *it2;

		if (column1Card.getColor() != column2Card.getColor()) {
			int index1 = -1;  
			int index2 = -1; 

			// Find index1 in arr
			for (int i = 0; i < 13; i++) {
				if (column1Card.getRank() == arr[i]) {
					index1 = i;
					break; 
				}
			}

			// Find index2 in arr
			for (int i = 0; i < 13; i++) {
				if (column2Card.getRank() == arr[i]) {
					index2 = i;
					break; 
				}
			}

			// Check if both indexes were found
			if (index1 == -1 || index2 == -1) {
				cout << "Error: Invalid card rank detected." << endl;
				return false;
			}

			// Check if the ranks differ by one
			if (index1 == index2 - 1) {
				whatColumn1.removeLastElement();
				whatColumn2.insertAtTail(column1Card);  // Move card from column1 to column2
			}
			else {
				cout << "First tableau card must be one less in rank to move!" << endl;
				return false;
			}
		}
		else {
			cout << "Top cards must be opposite in color to move!" << endl;
			return false;
		}
	}
	return true;
}

void Game::stockToWaste()
{
	if (!Stock.isEmptyStack()) {
		WastePile.push(Stock.pop());
	}
}

void Game::makeTopVisible()
{
	List<Card>::Iterator i = t1.end();	--i;
	if (i != t1.begin()) {
		Card tmpCard = *i;
		tmpCard.setHide(false);
		t1.removeLastElement();
		t1.insertAtTail(tmpCard);
	}
	i = t2.end();	--i;
	if (i != t2.begin()) {
		Card tmpCard = *i;
		tmpCard.setHide(false);
		t2.removeLastElement();
		t2.insertAtTail(tmpCard);
	}
	i = t3.end();	--i;
	if (i != t3.begin()) {
		Card tmpCard = *i;
		tmpCard.setHide(false);
		t3.removeLastElement();
		t3.insertAtTail(tmpCard);
	}
	i = t4.end();	--i;
	if (i != t4.begin()) {
		Card tmpCard = *i;
		tmpCard.setHide(false);
		t4.removeLastElement();
		t4.insertAtTail(tmpCard);
	}
	i = t5.end();	--i;
	if (i != t5.begin()) {
		Card tmpCard = *i;
		tmpCard.setHide(false);
		t5.removeLastElement();
		t5.insertAtTail(tmpCard);
	}
	i = t6.end();	--i;
	if (i != t6.begin()) {
		Card tmpCard = *i;
		tmpCard.setHide(false);
		t6.removeLastElement();
		t6.insertAtTail(tmpCard);
	}
	i = t7.end();	--i;
	if (i != t7.begin()) {
		Card tmpCard = *i;
		tmpCard.setHide(false);
		t7.removeLastElement();
		t7.insertAtTail(tmpCard);
	}
}

Game::Game()
	:t1(), t2(), t3(), t4(), t5(), t6(), t7(),
	Stock(24), WastePile(24), Foundation1(13), Foundation2(13),
	Foundation3(13), Foundation4(13), commands(5)
{
	__init__();
}

bool Game::undoLastMove() {
	if (commands.isEmptyStack()) {
		cout << "No moves to undo." << endl;
		return false;
	}

	Command lastCommand = commands.pop();
	string cmdType = lastCommand.getCommandType();
	string cmd = lastCommand.getCommand();

	if (cmdType == "m") {
		// Undo move between tableaus or tableau to foundation
		char sourceCol = cmd[6];
		char destCol = cmd[2];
		char numCards = cmd[8];

		if (cmd[5] == 'f') {
			// Undo move from tableau to foundation
			return undoTableauToFoundation(sourceCol, destCol, numCards);
		}
		else {
			// Undo move between tableaus
			return undoTableauToTableau(sourceCol, destCol, numCards);
		}
	}
	else if (cmdType == "m w") {
		// Undo move from waste
		char destType = cmd[4];
		char destCol = cmd[5];

		if (destType == 'c') {
			// Undo move from waste to tableau
			return undoWasteToTableau(destCol);
		}
		else if (destType == 'f') {
			// Undo move from waste to foundation
			return undoWasteToFoundation(destCol);
		}
	}
	else if (cmdType == "s") {
		// Undo stock to waste move
		return undoStockToWaste();
	}

	cout << "Unable to undo the last move." << endl;
	return false;
}

bool Game::undoTableauToTableau(char sourceCol, char destCol, char numCards) {
	List<Card>& sourcePile = getPileFromChar(sourceCol);
	List<Card>& destPile = getPileFromChar(destCol);

	int cardsToMove = numCards - '0';
	for (int i = 0; i < cardsToMove; i++) {
		if (destPile.isEmpty()) {
			cout << "Error: Destination pile is empty." << endl;
			return false;
		}
		Card card = destPile.getLastElement();
		destPile.removeLastElement();
		sourcePile.insertAtTail(card);
	}

	// Reveal the card in the source pile if it was hidden
	if (!sourcePile.isEmpty()) {
		Card& topCard = sourcePile.getLastElement();
		if (topCard.getHide()) {
			topCard.setHide(false);
		}
	}

	cout << "Undid move from Column " << destCol << " to Column " << sourceCol << endl;
	return true;
}

bool Game::undoTableauToFoundation(char sourceCol, char foundationNum, char numCards) {
	List<Card>& sourcePile = getPileFromChar(sourceCol);
	Stack<Card>& foundation = getFoundationFromChar(foundationNum);

	if (foundation.isEmptyStack()) {
		cout << "Error: Foundation is empty." << endl;
		return false;
	}

	Card card = foundation.pop();
	sourcePile.insertAtTail(card);

	cout << "Undid move from Column " << sourceCol << " to Foundation " << foundationNum << endl;
	return true;
}

bool Game::undoWasteToTableau(char destCol) {
	List<Card>& destPile = getPileFromChar(destCol);

	if (destPile.isEmpty()) {
		cout << "Error: Destination pile is empty." << endl;
		return false;
	}

	Card card = destPile.getLastElement();
	destPile.removeLastElement();
	WastePile.push(card);

	cout << "Undid move from Waste to Column " << destCol << endl;
	return true;
}

bool Game::undoWasteToFoundation(char foundationNum) {
	Stack<Card>& foundation = getFoundationFromChar(foundationNum);

	if (foundation.isEmptyStack()) {
		cout << "Error: Foundation is empty." << endl;
		return false;
	}

	Card card = foundation.pop();
	WastePile.push(card);

	cout << "Undid move from Waste to Foundation " << foundationNum << endl;
	return true;
}

bool Game::undoStockToWaste() {
	if (WastePile.isEmptyStack()) {
		cout << "Error: Waste pile is empty." << endl;
		return false;
	}

	Card card = WastePile.pop();
	Stock.push(card);

	cout << "Undid move from Stock to Waste" << endl;
	return true;
}

List<Card>& Game::getPileFromChar(char col) {
	switch (col) {
	case '1': return t1;
	case '2': return t2;
	case '3': return t3;
	case '4': return t4;
	case '5': return t5;
	case '6': return t6;
	case '7': return t7;
	default: throw std::runtime_error("Invalid column number");
	}
}

Stack<Card>& Game::getFoundationFromChar(char foundationNum) {
	switch (foundationNum) {
	case '1': return Foundation1;
	case '2': return Foundation2;
	case '3': return Foundation3;
	case '4': return Foundation4;
	default: throw std::runtime_error("Invalid foundation number");
	}
}