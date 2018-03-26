#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string>
#include "fields.h"
#include "entities.h"
using namespace std;

typedef unsigned char byte;

byte cinit();
byte crun();
byte cterm();

int spid; // PID of the server, only set to non-zero if this is the client that launched the server

int main(int argc,char** args) {
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
	
	jettison_inputstruct(in);
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
