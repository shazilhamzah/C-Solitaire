#pragma once
#include<iostream>
using namespace std;


class Command {
	string command;
	string commandType;
public:
	Command() { this->command = ""; }
	Command(string s, string t) { this->command = s; this->commandType = t; }
	Command(const Command& rhs) { this->command = rhs.command; this->commandType = rhs.commandType; }
	Command& operator=(Command& rhs) { this->command = rhs.command; this->commandType = rhs.commandType; return *this; }
	void setCommand(string s) { this->command = s; }
	void setCommandType(string s) { this->commandType = s; }
	string getCommand() { return this->command; }
	string getCommandType() { return this->commandType; }
};