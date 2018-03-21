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
bool playerInDungeon(vector<Entity>);
bool inBattle(Entity*[]);
void handler(Entity*[]);

int spid; // PID of the server, only set to non-zero if this is the client that launched the server

int main(int argc,char** args) {
	//IS in = new_inputstruct(NULL);
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

	for (int i = 0; i < 7; i++)
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
				if(temp[0] >= '1' && temp[0] <= '6') { //note: change second item to however many classes we end up having
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
				for (int i = 0; i < name.size(); i++)
					if (name[i] != ' ') {
						fileName += tolower(name[i]);
					} else {
						fileName += '_';
					}
				fileName += ".txt";
				input.open(fileName.c_str());
				if (input.fail())
					printf("Bad file. Try again.");
				else 
					break;
			}
			party[place]->load(input);
			place++;
		} else {
			printf("Then let's generate a character for you.\n");
			party[place] = new Entity;
			party[place]->generateChar();
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
	vector<Entity> inDungeon;
	cout << "before";
	for (int i = 0; party[i] != NULL; i++)
		inDungeon.push_back(*party[i]);
	cout << "after";
	sort(inDungeon.begin(), inDungeon.end());
	for (int i = 0; i < 5; i++)
		int j = 0;
    while(running == 1){  
		int tFactor = 100;
		if (playerInDungeon(inDungeon)){
			if (inBattle(party))
				tFactor = 1;
			else
				tFactor = 10;
			for (size_t i = 0; i < inDungeon.size(); i++){
				inDungeon[i].tick(tFactor);
			}
		}
		if (false)// need to exit
			running = 0;
    }
}

bool playerInDungeon(vector <Entity> sEntity) {
	for (size_t i = 0; i < sEntity.size(); i++){
		if (!sEntity[i].npc)
			return true;
	}
	return false;
}

bool inBattle (Entity* party[]) {
	return false;
	//Not sure how we will be storing rooms, just need to check and see if enemies are in the room with the player 
}