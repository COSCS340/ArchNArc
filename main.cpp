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
	byte classNum;
	ifstream input;
	for (int i = 0; i < 7; i++)
		party[i] = NULL;
	while (true) {
		while (true){
			printf("Would you like to create a new character?(y/n)");
			cin >> ans;
			ans = tolower(ans);
			if (ans == 'y' || ans == 'n')
				break;
			printf("Error, incorrect input. Try Again.");
		}
		if (ans == 'y'){
			party[place] = new Entity;
			printf ("Enter the character's name: ");
			cin >> name;
			printf("What class would you like to be? Please choose one of the following.\n");
			printf(" ----------------------------\n");
			for(int i = 0; i < NUM_JOBS; i++) {
				printf("| %5d %-20s |\n", i+1, JOBS[i].c_str());
				//print job descriptions?
			}
			printf(" ----------------------------\n");
			while(true) {
				printf(" >> ");
				getline(std::cin, temp);
				for (classNum = 0; classNum < 6; classNum++)
					if (temp == JOBS[classNum])
						break;
				if (classNum == 6){ //bad input
					printf("I don't recognize that. Please try again.\n");
				}
			}
			party[place]->setUpChar(name, (byte) 0, classNum);
			place++;
			continue;
		}
		while (true) {
			printf ("Would you like to load a character?(y/n)");
			cin >> ans;
			ans = tolower(ans);
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
					if (name[i] != ' ')
						fileName += tolower(name[i]);
				fileName += ".txt";
				input.open(fileName.c_str());
				if (input.fail())
					printf("Bad file. Try again.");
				else 
					break;
			}
			party[place]->load(input);
			place++;
		}
		if (ans == 'n' || place == 7)
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
