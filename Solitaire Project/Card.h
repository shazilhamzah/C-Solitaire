#pragma once
#include<iostream>
using namespace std;


class Card {
	string suit;
	string rank;
	string color;
	bool hide;
public:
	Card():suit(""),rank("") {}
	Card(string suit1, string rank1,string c,bool b) :suit(suit1), rank(rank1),color(c),hide(b) {}
	Card(const Card& right) { this->color = right.color; this->rank = right.rank; this->suit = right.suit; this->hide = right.hide; }
	Card operator=(const Card& right) { this->color = right.color; this->rank = right.rank; this->suit = right.suit; this->hide = right.hide; return *this; }
	string getSuit() { return suit; }
	string getRank() { return rank; }
	string getColor() { return this->color; }
	bool getHide() { return hide; }
	void setSuit(string s) { this->suit = s; }
	void setRank(string r) { this->rank= r; }
	void setColor(string c) { this->color = c; }
	void setHide(bool b) { this->hide= b; }
	void print() { cout << this->rank << " of " << this->suit << " - " << this->color << endl; }

};