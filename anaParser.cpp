/* 	We had talked about using the fields library and Ron was working on 
		porting it over here, so I'll set this up using that.
		string command;
	
		//Hey, Michaela here. This would be easier with strstr(), if you
		//wanted to simplify searching strings. It'd just need to be with
		//c_strings instead
		
		Ron - began implementing the use of vectors that containing valid synonyms for each action
*/
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <cstring>
#include <cctype>
#include "fields.h"
using namespace std;

const int USE = 0;
const int MOVE = 1;
const int ATTACK = 2;
const int CHECK = 3;
const int TAKE = 4;
const int HELP = 5;
const int SKILL = 6;
const int TALK = 7;
const int MAP = 8;

const vector<string> use_vec = {"use", "drink", "eat", "consume"};
const vector<string> move_vec = {"go", "walk", "run", "move"};
const vector<string> attack_vec = {"attack", "hit"};
const vector<string> check_vec = {"check", "scan", "look", "examine"};
const vector<string> take_vec = {"take", "pickup", "grab", "snatch"};

int action();
int synonyms(char*);
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

	//call function for given action
	switch(selection){
		case MOVE:
			actionMove(is);
			break;
		case USE:
		   	actionUse(is);
		   	break;	
		case ATTACK:
		    	actionAttack(is);
		    	break;
		case CHECK:
		    	actionCheck(is);
		    	break;
		case TAKE:
		    	actionTake(is);
		    	break;
		case HELP:
			actionHelp();
			break;
		default:
		    	badinput();
	}
	
	//free memory and return
	jettison_inputstruct(is);
	return 1;
}

//move character 
void actionMove(IS is) {
	return;
}

//use an item
void actionUse(IS is) {
	return;
}

//attack designated target
void actionAttack(IS is) {
	return;
}

//look at available enemy stats
void actionCheck(IS is) {
	return;
}

//pickup/take item
void actionTake(IS is) {
	return;
}

//input assistance
void actionHelp() {
	std::cout << "Try using an item, skill or spell." << endl
		  << "You can check on the status of enemies and allies or list skills and spells." << endl;
		  << "If you want to know what something will do, try an action." << endl;
	return;
}

//incorrect input 
void badInput() {
	cout << "Invalid input. Type 'help' for help." << endl;
	return;
}

//gets command based on synonyms
int synonyms(char* b) {
	
	for(i = 0; i < use_vec.size(); i++) {
		if(strcmp(b,use_vec[i] == 0)
			return(USE);
	}
		   
	for(i = 0; i < move_vec.size(); i++) {
		if(strcmp(b,move_vec[i] == 0)
		   	return(MOVE);	
	}
		   
	for(i = 0; i < attack_vec.size(); i++) {
		if(strcmp(b,attack_vec[i] == 0)	
		   	return(ATTACK);	
	}
		   
	for(i = 0; i < check_vec.size(); i++) {
		if(strcmp(b,check_vec[i] == 0)
		   	return(CHECK);
	}
		   
	for(i = 0; i < take_vec.size(); i++) {
		if(strcmp(b,take_vec[i] == 0)
		   	return(TAKE);	
	}
	
	if(strcmp(b,"help") == 0)
		return(HELP);
}
