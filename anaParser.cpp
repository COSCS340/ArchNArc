#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <cstring>
#include <cctype>
#include "fields.h"
using namespace std;

/* 
commands to be supported (working list)
    use = {drink, eat, use}
    check = {open, look}
    try
    move = {walk, go}
    attack = {hit, bash, slash, ... }
*/

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
	int j = 1;
	while (j){
		cout << "What would you like to do?" << endl;
		j = action();
	}
}

int action () {
	/* 	We had talked about using the fields library and Ron was working on 
		porting it over here, so I'll set this up using that.
		string command;
	
		//Hey, Michaela here. This would be easier with strstr(), if you
		//wanted to simplify searching strings. It'd just need to be with
		//c_strings instead.
		
		Ron - thinking about implementing the synonyms function using a vector
		for each action that contain valid synonyms
	*/
	int selection;
	
	//open inputstruct for reading stdin
	IS is = new_inputstruct(NULL);
	
	//pull player action -- return on fail
	if(get_line(is) < 0);
		return 0;
	
	//coverts all letters to lower case
	for (int i = 0; i < is->NF; i++)
		for (j = 0; fields[i][j] != 0; j++)
			tolower(field[i][j]);
	
	//check for action word synonyms
	selections = synonyms(is->fields[0]);
/*	
	//call action function
	if (is->fields[0] == "try")
		actionTry(is);
	else if (is->fields[0] == "check")
		actionCheck(is);
	else if (is->fields[0] == "help")
		actionHelp();
	else if (is->fields[0] == "use")
		actionUse(is);
	else
		badInput();
*/
	switch(selection){
		case MOVE:
			
		case ATTACK:
		
		default:
	}
	
	//free memory and return
	jettison_inputstruct(is);
	return 1;
}

//use an item
void actionUse(IS is) {
	string item;
	if (is->NF < 2){
		cout << "Invalid input: no specified item to use.\n";
		return;
	}else{
		//use item
	}
	return;
}

//look at available enemy stats
void actionCheck(IS is) {
	return;
}

//preview results of performing action
void actionTry(IS is) {
	return;
}

//input assistance
void actionHelp() {
	std::cout << "Try using an item, skill or spell." << endl
		 << "You can check on the status of enemies and allies or list skills and spells." << endl;
		 << "If you want to know what something will do, try an action." << endl;
}

//incorrect input 
void badInput() {
	cout << "Invalid input. Type 'help' for help." << endl;
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
void synonyms(char* action) {
	if (action == "use")
		return;
	else if (action == "try")
		return;
	else if (action == "check")
		return;
	else if (action == "help")
		return;
	else if (action == "eat"){
		action = "use"
		return;
	}
	else if (action == "drink"){
		b = "use";
		return;
	}
	else if (action == "cast"){
		b = "use";
		return;
	}
	else if (
}
*/
