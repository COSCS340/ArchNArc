#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <cctype>
#include "fields.h"

const int MOVE = 0;
const int ATTACK = 1;
const int CHECK = 2;
const int SKILL = 3;
const int TAKE = 4;
const int TALK = 5;
const int MAP = 6;

int action();
int synonyms(char*);
//void synonyms(char*);
void actionUse(IS);
void actionCheck(IS);
void actionTry(IS);
void actionHelp();
void badInput();

int main () {
	using namespace std;
	int j = 1;
	while (j){
		cout << "What would you like to do?" << endl;
		j = action();
	}
}

int action () {
	using namespace std;
	int selection;
	/* We had talked about using the fields library and Ron was working on porting it over here, so I'll set this up using that.
	string command;
	getline(cin, command);
	string b;

	//Hey, Michaela here. This would be easier with strstr(), if you
	//wanted to simplify searching strings. It'd just need to be with
	//c_strings instead.

	size_t pos = command.find(" ");
	b = command.substr(0, pos);*/
	IS is = new_inputstruct();
	int j = get_line();
	if (j == -1)
		return 0;
	for (int i = 0; i < is->NF; i++)
		for (j = 0; fields[i][j] != 0; j++)
			tolower(field[i][j]);
	selections = synonyms(is->fields[0]);
/*	if (b == "try")
		actionTry(is);
	else if (b == "check")
		actionCheck(is);
	else if (b == "help")
		actionHelp();
	else if (b == "use")
		actionUse(is);
	else
		badInput();
*/
	switch(selections) {
		case MOVE:

		case ATTACK:

		default:
	}
	jettison_inputstruct();
	return 1;
}

void actionUse(IS is) {
	if (is->NF == 2){
		
	}
	return;
}

void actionCheck(IS is) {
	return;
}

void actionTry(IS is) {
	return;
}

void actionHelp() {
	std::cout << "Try using an item, skill or spell." << endl
		 << "You can check on the status of enemies and allies or list skills and spells." << endl;
		 << "If you want to know what something will do, try an action." << endl;
}

void badInput() {
	using namespace std;
	cout << "Invalid input. Try again." << endl;
}

//just trying out something new. If it don't work out, we'll go back to yours
//I do believe we're planning on doing vectors of synonyms. In that case, my
//basic idea stands that it'd be simpler to use constants and return the result,
//we'd just need to loop through the vector for comparisons. IE
//	for(int i = 0; i < move_vec.size(); i++) {
//		if(strcmp(b, move_vec[i]) == 0) return(MOVE);
//	}
int synonyms(char* b) {
	if(strcmp(b, "go") == 0 || strcmp(b, "walk") == 0 || strcmp(b, "move") == 0) {
		return(MOVE);
	}
	
	if(strcmp(b, "attack") == 0 || strcmp(b, "hit") == 0 || strcmp(b, "bash") == 0) {
		return(ATTACK);
	}
	
	if(strcmp(b, "check") == 0 || strcmp(b, "scan") == 0 || strcmp(b, "examine") == 0) {
		return(CHECK);
	}

	if(strcmp(b, "take") == 0 || strcmp(b, "grab") == 0 || strcmp(b, "snatch") == 0) {
		return(TAKE);
	}
}
/*
void synonyms(char* b) {
	if (command == "use")
		return;
	else if (b == "try")
		return;
	else if (b == "check")
		return;
	else if (b == "help")
		return;
	else if (command == "eat"){
		b = "use"
		return;
	}
	else if (command == "drink"){
		b = "use";
		return;
	}
	else if (command == "cast"){
		b = "use";
		return;
	}
}
*/
