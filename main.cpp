#include <algorithm>
#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <set>
#include <sys/wait.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include "fields.h"
#include "entities.h"
using namespace std;

typedef unsigned char byte;

byte cinit();
byte crun();
byte cterm();
bool playerInDungeon(Entity*[]);
bool inBattle(Entity*[]);
void handler(Entity*[]);
void makeMines(Area&);

int spid; // PID of the server, only set to non-zero if this is the client that launched the server

int main(int argc,char** args) {
	//IS in = new_inputstruct(NULL);
	int i;
	IS in = new_inputstruct(NULL);
	printf("Welcome to Archery & Arcana, player.\n");
	if(cinit()) return 1;
	if(crun()) return 1;
	if(cterm()) return 1;

	Entity* party[7];
	int place = 0;
	char ans;
	string name;
	string fileName;
	string temp;
	string junk;
	byte classNum;
	ifstream input;
	int flag;

	srand(time(NULL));

	setUpParty(party);
	
	handler(party);

	jettison_inputstruct(in);

	return(0);

	for (i = 0; i < 7; i++)
		party[i] = NULL;
	while (true) {
		while (true){
			printf("Would you like to create a new character?(y/n) ");
			getline(cin, junk);
			ans = tolower(junk[0]);
			if (ans == 'y' || ans == 'n')
				break;
			printf("Error, incorrect input. Try Again.");
		}
		if (ans == 'y'){
			party[place] = new Entity;
			printf ("Enter the character's name: ");
			getline(cin, name);
			printf("What class would you like to be? Please choose one of the following.\n");
			printf(" ----------------------------\n");
			for(int i = 0; i < NUM_JOBS; i++) {
				printf("| %5d %-20s |\n", i+1, JOBS[i].c_str());
				//print job descriptions?
			}
			printf(" ----------------------------\n");
			while(true) {
				flag = 1;
				printf(" >> ");
				getline(cin, temp);
				if(temp[0] >= '1' && temp[0] <= '8') { //note: change second item to however many classes we end up having
					temp[1] = '\0';
					classNum = atoi(temp.c_str()) - 1;
					break;
				} else {
					for(int i = 0; temp[i] != '\0'; i++) {
						temp[i] = tolower(temp[i]);
					}
					for (classNum = 0; classNum < 6; classNum++) {
						if (temp == JOBS[classNum]) {
							flag = 0;
							break;
						}
					}
					if(flag == 0) {
						break;
					}
					if (classNum == 6){ //bad input
						printf("I don't recognize that. Please try again.\n");
					}
				}
			}
			party[place]->setUpChar(name, (byte) 0, classNum);
			party[place]->listAttributes();
			place++;
			if(place > 6){
				break;
			}
			continue;
		}
		while (true) {
			printf ("Would you like to load a character?(y/n) ");
			getline(cin, junk);
			ans = tolower(junk[0]);
			if (ans == 'y' || ans == 'n')
				break;
			printf("Error, incorrect input. Try Again.");
		}
		if (ans == 'y'){
			party[place] = new Entity;
			while (true){
				fileName = "";
				printf("Enter your character's name: ");
				getline(cin, name);
				for (i = 0; i < name.size(); i++)
					if (name[i] != ' ') {
						fileName[i] = tolower(name[i]);
					} else {
						fileName[i] = '_';
					}
				fileName[i] = '.';
				fileName[i+1] = 't';
				fileName[i+2] = 'x';
				fileName[i+3] = 't';
				fileName[i+4] = '\0';
				input.open(fileName.c_str());
				if (input.fail())
					printf("Bad file. Try again.");
				else 
					break;
			}
			party[place]->load(input);
			input.close();
			place++;
		} else {
			printf("Then let's generate a character for you.\n");
			party[place] = new Entity;
			party[place]->generateChar();
			party[place]->listAttributes();
			place++;
		}
		if (place > 6)
			break;
	}
	//jettison_inputstruct(in);
	handler(party);
}

byte cinit() {
    
    return 0;
}

byte crun() {

    return 0;
}

byte cterm() {

    return 0;
}

void handler (Entity* party[]) {
	int running = 1;
	Area mines;
	makeMines(mines);
	for (int i = 0; i < 7; i++){
		party[i]->room = mines.mapOfArea[0];
		mines.mapOfArea[0]->inRoom.push_back(party[i]);
		mines.inDungeon.push_back(party[i]);
	}
	sort(mines.inDungeon.begin(), mines.inDungeon.end(), comp);
	int tFactor;
    while(running == 1){
		tFactor = 100;
		if (playerInDungeon(party)){
			if (inBattle(party))
				tFactor = 1;
			else
				tFactor = 10;
			for (size_t i = 0; i < mines.inDungeon.size(); i++){
				running = mines.inDungeon[i]->tick(tFactor);
				if (running == 0)
					break;
			}
		}
    }
}

bool playerInDungeon(Entity* party[]) {
	for (int i = 0; i < 7; i++){
		if (party[i]->room != NULL)
			return true;
	}
	return false;
}

void makeMines (Area& mines) {
	Entity* ePtr;
	mines.name = "Mines of Michaela";
	for (int i = 0; i < 17; i++){
		mines.mapOfArea.push_back(new Tile);
		mines.mapOfArea[i]->zone = &mines;
	}
	mines.mapOfArea[0]->door.push_back(make_pair(mines.mapOfArea[1], "West"));
	mines.mapOfArea[1]->door.push_back(make_pair(mines.mapOfArea[0], "East"));
	mines.mapOfArea[1]->door.push_back(make_pair(mines.mapOfArea[2], "South"));
	mines.mapOfArea[2]->door.push_back(make_pair(mines.mapOfArea[1], "North"));
	mines.mapOfArea[2]->door.push_back(make_pair(mines.mapOfArea[3], "South by Southeast"));
	mines.mapOfArea[2]->door.push_back(make_pair(mines.mapOfArea[4], "Southwest"));
	mines.mapOfArea[2]->door.push_back(make_pair(mines.mapOfArea[5], "Northwest"));
	mines.mapOfArea[3]->door.push_back(make_pair(mines.mapOfArea[2], "North by Northwest"));
	mines.mapOfArea[4]->door.push_back(make_pair(mines.mapOfArea[2], "Northeast"));
	mines.mapOfArea[4]->door.push_back(make_pair(mines.mapOfArea[5], "North"));
	mines.mapOfArea[4]->door.push_back(make_pair(mines.mapOfArea[6], "Northwest"));
	mines.mapOfArea[5]->door.push_back(make_pair(mines.mapOfArea[2], "Southeast"));
	mines.mapOfArea[5]->door.push_back(make_pair(mines.mapOfArea[7], "Northeast"));
	mines.mapOfArea[5]->door.push_back(make_pair(mines.mapOfArea[6], "South"));
	mines.mapOfArea[5]->door.push_back(make_pair(mines.mapOfArea[4], "South by Southeast"));
	mines.mapOfArea[6]->door.push_back(make_pair(mines.mapOfArea[4], "Southeast"));
	mines.mapOfArea[6]->door.push_back(make_pair(mines.mapOfArea[5], "North"));
	mines.mapOfArea[6]->door.push_back(make_pair(mines.mapOfArea[8], "West"));
	mines.mapOfArea[6]->door.push_back(make_pair(mines.mapOfArea[10], "North by Northwest"));
	mines.mapOfArea[7]->door.push_back(make_pair(mines.mapOfArea[9], "South"));
	mines.mapOfArea[7]->door.push_back(make_pair(mines.mapOfArea[5], "Southwest"));
	mines.mapOfArea[8]->door.push_back(make_pair(mines.mapOfArea[6], "East"));
	mines.mapOfArea[8]->door.push_back(make_pair(mines.mapOfArea[10], "North by Northeast"));
	mines.mapOfArea[9]->door.push_back(make_pair(mines.mapOfArea[7], "North"));
	mines.mapOfArea[10]->door.push_back(make_pair(mines.mapOfArea[11], "Southwest"));
	mines.mapOfArea[10]->door.push_back(make_pair(mines.mapOfArea[8], "South by Southwest"));
	mines.mapOfArea[10]->door.push_back(make_pair(mines.mapOfArea[6], "South by Southeast"));
	mines.mapOfArea[10]->door.push_back(make_pair(mines.mapOfArea[12], "North by Northwest"));
	mines.mapOfArea[10]->door.push_back(make_pair(mines.mapOfArea[13], "Northeast"));
	mines.mapOfArea[10]->door.push_back(make_pair(mines.mapOfArea[14], "North"));
	mines.mapOfArea[11]->door.push_back(make_pair(mines.mapOfArea[10], "Northest"));
	mines.mapOfArea[12]->door.push_back(make_pair(mines.mapOfArea[10], "South by Southeast"));
	mines.mapOfArea[12]->door.push_back(make_pair(mines.mapOfArea[13], "Southeast"));
	mines.mapOfArea[12]->door.push_back(make_pair(mines.mapOfArea[14], "Southeast"));
	mines.mapOfArea[13]->door.push_back(make_pair(mines.mapOfArea[10], "Southwest"));
	mines.mapOfArea[13]->door.push_back(make_pair(mines.mapOfArea[12], "Northwest"));
	mines.mapOfArea[13]->door.push_back(make_pair(mines.mapOfArea[14], "Northwest"));
	mines.mapOfArea[14]->door.push_back(make_pair(mines.mapOfArea[10], "South"));
	mines.mapOfArea[14]->door.push_back(make_pair(mines.mapOfArea[12], "Northwest"));
	mines.mapOfArea[14]->door.push_back(make_pair(mines.mapOfArea[13], "Southeast"));
	mines.mapOfArea[14]->door.push_back(make_pair(mines.mapOfArea[15], "East"));
	mines.mapOfArea[14]->door.push_back(make_pair(mines.mapOfArea[16], "East by Northeast"));
	mines.mapOfArea[15]->door.push_back(make_pair(mines.mapOfArea[14], "West"));
	mines.mapOfArea[16]->door.push_back(make_pair(mines.mapOfArea[14], "West by Southwest"));
	for (int i = 0; i < 30; i++){
		ePtr = new Entity;
		ePtr->name = "Goblin ";
		for (int j = 0; j < i%5; j++)
			ePtr->name += "I";
		ePtr->attributes = (byte*)malloc(6);
		ePtr->max_mp = ePtr->cur_mp = 0;
		ePtr->attributes[0] = rand()%5000;
		ePtr->attributes[1] = 5;
		ePtr->attributes[2] = 3;
		ePtr->attributes[3] = 5;
		ePtr->attributes[4] = 5;
		ePtr->attributes[5] = 5;
		ePtr->max_hp = ePtr->cur_hp = ePtr->attributes[5]*2;
		ePtr->npc = 1;
		ePtr->cooldown = 0;
		ePtr->illusion = NULL;
		ePtr->defense = 0;
		mines.inDungeon.push_back(ePtr);
	}
	ePtr = new Entity;
	ePtr->name = "Clay Golem";
	ePtr->attributes = (byte*)malloc(6);
	ePtr->max_mp = ePtr->cur_mp = 0;
	ePtr->attributes[0] = rand()%5000;
	ePtr->attributes[1] = 15;
	ePtr->attributes[2] = 0;
	ePtr->attributes[3] = 3;
	ePtr->attributes[4] = 5;
	ePtr->attributes[5] = 15;
	ePtr->max_hp = ePtr->cur_hp = ePtr->attributes[5]*2;
	ePtr->npc = 1;
	ePtr->cooldown = 0;
	ePtr->illusion = NULL;
	ePtr->defense = 0;
	mines.inDungeon.push_back(ePtr);
	ePtr = new Entity;
	ePtr->name = "Alaskan Bull Worm";
	ePtr->attributes = (byte*)malloc(6);
	ePtr->max_mp = ePtr->cur_mp = 0;
	ePtr->attributes[0] = rand()%5000;
	ePtr->attributes[1] = 20;
	ePtr->attributes[2] = 0;
	ePtr->attributes[3] = 11;
	ePtr->attributes[4] = 0;
	ePtr->attributes[5] = 15;
	ePtr->max_hp = ePtr->cur_hp = ePtr->attributes[5]*2;
	ePtr->npc = 1;
	ePtr->cooldown = 0;
	ePtr->illusion = NULL;
	ePtr->defense = 0;
	mines.inDungeon.push_back(ePtr);
	for (int i = 0; i < 30; i++){
		if (i < 5){
			mines.inDungeon[i]->room = mines.mapOfArea[2];
			mines.mapOfArea[2]->inRoom.push_back(mines.inDungeon[i]);
		}
		else if (i < 10){
			mines.inDungeon[i]->room = mines.mapOfArea[6];
			mines.mapOfArea[6]->inRoom.push_back(mines.inDungeon[i]);
		}
		else if (i < 15){
			mines.inDungeon[i]->room = mines.mapOfArea[3];
			mines.mapOfArea[3]->inRoom.push_back(mines.inDungeon[i]);
		}
		else if (i < 20){
			mines.inDungeon[i]->room = mines.mapOfArea[9];
			mines.mapOfArea[9]->inRoom.push_back(mines.inDungeon[i]);
		}
		else if (i < 25){
			mines.inDungeon[i]->room = mines.mapOfArea[12];
			mines.mapOfArea[12]->inRoom.push_back(mines.inDungeon[i]);
		}
		else if (i < 30){
			mines.inDungeon[i]->room = mines.mapOfArea[14];
			mines.mapOfArea[14]->inRoom.push_back(mines.inDungeon[i]);
		}
	}
	mines.inDungeon[30]->room = mines.mapOfArea[14];
	mines.mapOfArea[14]->inRoom.push_back(mines.inDungeon[30]);
	mines.inDungeon[31]->room = mines.mapOfArea[16];
	mines.mapOfArea[16]->inRoom.push_back(mines.inDungeon[31]);
}

bool inBattle (Entity* party[]) {
	for (int i = 0; i < 7; i++){
		for (int j = 0; j < party[i]->room->inRoom.size() && party[i]->room->inRoom[j] != NULL; j++){
			if (party[i]->room->inRoom[j]->npc == 1 && party[i]->room->inRoom[j]->cur_hp > 0)
				return true;
		}
	}
	return false;
}
