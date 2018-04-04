/* File: entities.cpp
 * Author: collective effort of Team Archery and Arcana
 * Regrets: none
 */
#include <algorithm>
#include <iostream>
#include <set>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <string>
//#include "anaParser.h"
#include "entities.h"
#include "fields.h"
#include "skills.h"

const string pos_names[] = {"Manaliabrid", "Osfameron", "Deryn", "Brutha", "Anevka", "Enoch", "Sandrilene", "Theophrastus", "Hazel", "Kevin", "Gladys", "Anatolio", "Lyseria", "Bob", "Azula", "Krauss", "Amakusa", "Rudolph", "Adara", "Janus", "Aeronwen", "Keichi", "Branwen", "Alwyn", "Dwynwen", "Cadfael", "Hywela", "Emlyn", "Maelona", "Gwalchgwyn", "Nerys", "Idris", "Sioned", "Llywellyn", "Yseult", "Leimu", "Yukari", "Marisa", "Aya", "Jenga", "Califaan", "STEVE"};
const string pos_titles[] = {" the Foolhardy", " the Cowardly", " the Crusader", " the Incompetent", " the Flautist", " the Sleep-Deprived", " the Tennessean", " the Overlord", " the Hatter", " the Sunseeker", " the Fluffy", " the Timejumper", " the Darwinist", " the Mentor", " the Lucky", " the Left-Footed", " the Ace", " the Stingy", " the Executioner", " the Fraudulent", " the NPC", " the Hopeful", " the Morbid", " the Bemused", " the Concerned", " the Unworthy", " the Tree-Hugger", " the Earthbound", " the Oblivious", " the Immortal", " the Mortal", " the Corrupted", " the Pessimist", " the Seg-Fault", " the Silent", " the Clothed", " the Paranoid", " the Caffeinated", " the Lost", " the Error", " the Conspirator", " the Punctual", " the Liar", " the Felon", " the Ignoble", " the Mispronounced", " the Righteous", " the Blasphemous", " the Bane of Existence"};
const int NUM_NAMES = 41;
const int NUM_TITLES = 49;

void setUpParty(Entity* party[]) {
	int place = 0;
	int i;
	char ans;
	string name;
	string fileName;
	string temp;
	string junk;
	byte classNum;
	ifstream input;
	int flag;

	for(i = 0; i < 7; i++)
		party[i] = NULL;

	while(true) {
		while(true) {
			printf("Would you like to create a new character?(y/n) ");
			getline(cin, junk);
			ans = tolower(junk[0]);
			if (ans == 'y' || ans == 'n')
				break;
			printf("Error, incorrect input. Try Again.");
		}
		if(ans == 'y') {
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

		//START FROM HERE!!! LOAD CHAR!
		while(true) {
			printf ("Would you like to load a character?(y/n) ");
			getline(cin, junk);
			ans = tolower(junk[0]);
			if (ans == 'y' || ans == 'n')
				break;
			printf("Error, incorrect input. Try Again.");
		}
		if(ans == 'y') {
			party[place] = new Entity;
			while(true) {
				fileName = "";
				printf("Enter your character's name: ");
				getline(cin, name);
				for (i = 0; i < name.size(); i++) {
					if (name[i] != ' ') {
						fileName[i] = tolower(name[i]);
					} else {
						fileName[i] = '_';
					}
				}
				fileName[i] = '.';
				fileName[i+1] = 't';
				fileName[i+2] = 'x';
				fileName[i+3] = 't';
				fileName[i+4] = '\0';
				input.open(fileName.c_str());
				if(input.fail()) {
					printf("Bad file. Try again.\n");
				} else {
					break;
				}
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
		if(place > 6) {
			break;
		}
	}
}

Skill::Skill() {

}

//I feel this might work better as a function than a contructor. What do
//y'all think? Maybe something like
//
//void Entity::newGame() {
//
//to contrast with
//
//void Entity::loadGame() {

typedef unsigned char byte;

//r == race
//c == class
void Entity::setUpChar(string n, byte r, byte c) {
	npc = 0;
	cash = 500; //or whatever we let them start with
	level = 1;
	name = n;
	job.name = JOBS[c];
	jobNum = c;

	//if we end up doing alternate races, fix it here
	species = "Human";

	attributes = (byte*)malloc(6);
	max_hp = cur_hp = 20;
	max_mp = cur_mp = 10;
	attributes[0] = 10;
	attributes[1] = 10;
	attributes[2] = 10;
	attributes[3] = 10;
	attributes[4] = 10;
	attributes[5] = 10;
    //memcpy(attributes,RACEATTS[r],6);
	illusion = NULL;
	defense = 0;

	if(job.name == "fightard" || job.name == "anime kid") { //medium armor
		equipment["Weapon"].name = "Dagger";
		equipment["Weapon"].type = "edged weapon";
		equipment["Weapon"].attack = 3;
		equipment["Weapon"].defence = 0;
		equipment["Torso"].name = "Leather Tunic";
		equipment["Torso"].type = "shirt";
		equipment["Torso"].attack = 0;
		equipment["Torso"].defence = 2;
	} else if(job.name == "clay warrior") { //heavy armor
		equipment["Weapon"].name = "Oak Club";
		equipment["Weapon"].type = "blunt weapon";
		equipment["Weapon"].attack = 1;
		equipment["Weapon"].defence = 0;
		equipment["Torso"].name = "Wooden Breastplate";
		equipment["Torso"].type = "shirt";
		equipment["Torso"].attack = 0;
		equipment["Torso"].defence = 4;
	}
	else if (job.name == "gambler"){
		equipment["Weapon"].name = "Dagger";
		equipment["Weapon"].type = "edged weapon";
		equipment["Weapon"].attack = 3;
		equipment["Weapon"].defence = 0;
		equipment["Torso"].name = "Dandy's Blouse";
		equipment["Torso"].type = "shirt";
		equipment["Torso"].attack = 0;
		equipment["Torso"].defence = 2;
		skills.push_back(coinFlip);
		skills.push_back(multislash);
		skills.push_back(diceBomb);
	}
	else if (job.name == "Illusionist"){
		equipment["Weapon"].name = "Magic for Dummies";
		equipment["Weapon"].type = "magic paper";
		equipment["Weapon"].attack = 4;
		equipment["Weapon"].defence = 0;
		skills.push_back(nightmare);
		skills.push_back(tai);
		skills.push_back(illStrength);
	}
	else { //light armor
		equipment["Weapon"].name = "Small Pamphlet";
		equipment["Weapon"].type = "magic paper";
		equipment["Weapon"].attack = 4;
		equipment["Weapon"].defence = 0;
		equipment["Torso"].name = "Airy Robe";
		equipment["Torso"].type = "shirt";
		equipment["Torso"].attack = 0;
		equipment["Torso"].defence = 1;
	}

	useables["potion"].name = "Small potion";
	useables["potion"].type = "healing";
	useables["potion"].how_many = 3;
	useables["potion"].effect_size = 4;
}

void Entity::generateChar() {
	byte temp1, temp2;

	cash = 500;
	level = 1;

	temp1 = rand() % NUM_NAMES;
	temp2 = rand() % NUM_TITLES;

	name = pos_names[temp1] + pos_titles[temp2];
	printf("Your adventurer's name is %s.\n", name.c_str());

	//may wanna make it only select from jobs not already in the party. 
	//Especially if we get a good few more than 7 jobs.
	temp1 = rand() % NUM_JOBS;
	job.name = JOBS[temp1];
	printf("And their class is %s.\n", job.name.c_str());
	printf("So please don't get them killed.\n");

	attributes = (byte*)malloc(6);
	max_hp = cur_hp = 20;
	max_mp = cur_mp = 10;
	attributes[0] = 10;
	attributes[1] = 10;
	attributes[2] = 10;
	attributes[3] = 10;
	attributes[4] = 10;
	attributes[5] = 10;
	cooldown = 0;
	//memcpy(attributes,RACEATTS[r],6);
	setUpChar(name, 0, temp1);
}

void Entity::addEquipment(EquipItem a) {
	
}

void Entity::addUseable(UseItem a) {
	
}

void Entity::listAttributes() {
	map<string, EquipItem>::iterator e_it;
	map<string, UseItem>::iterator u_it;
	map<string, Skill>::iterator s_it;

	printf("\n%-30sGold: %d\n", name.c_str(), cash);
	printf("Species: %s\n", species.c_str());
	printf("Class: %s\n\n", job.name.c_str());
	printf("\nCurrent stats\n-----------------------\n");
	printf("HP %3d/%d     MP %3d/%d\n\n", cur_hp, max_hp, cur_mp, max_mp);
    byte i;
	//for(i=0;i<6;i++) printf("%-15s %hhx\n",ATTNAMES[i].c_str(),attributes[i]);
	for(i=0;i<6;i++) printf("%-15s %d\n",ATTNAMES[i].c_str(),(int)attributes[i]);

	//print skills
	printf("\nEquipment    \n-------------------------------\n");
	for(e_it = equipment.begin(); e_it != equipment.end(); e_it++) {
		printf("%-15s %s\n", e_it->first.c_str(), e_it->second.name.c_str());
	}

	printf("\nSupplies     \n-------------------------------\n");
	for(u_it = useables.begin(); u_it != useables.end(); u_it++) {
		printf("%-15s %13d\n", u_it->second.name.c_str(), u_it->second.how_many);
	}

	printf("\nSkills       \n-------------------------------\n");
	for(s_it = job.skills.begin(); s_it != job.skills.end(); s_it++) {
		printf("%-15s\n", s_it->first.c_str());
	}
	printf("\n");
}

int Entity::tick (int tFactor) {
	if (illusion != NULL){
		cout << "ill" << endl;
		int mag, res;
		if (illusion->name == "tai"){
			int mag = rand()%illusion->illusion->attributes[2];
			if (attributes[4] != 0)
				int res = rand()%attributes[4];
			else 
				res = 0;
			if (mag > res){
				if (cooldown < tFactor)
					cooldown = 0;
				else
					cooldown -= tFactor;
				if (cooldown == 0){
					int c = illusion->illusion->cooldown;
					illusion->illusion->act();
					cooldown = illusion->illusion->cooldown;
					illusion->illusion->cooldown = c;
					delete illusion;
					illusion = NULL;
				}
				return 1;
			}
			else {
				printf("%s breaks %s's illusion.\n", name.c_str(), illusion->illusion->name.c_str());
				delete illusion;
				illusion = NULL;
			}
		}
	}
	if (npc){
		if (cooldown < tFactor)
			cooldown = 0;
		else
			cooldown -= tFactor;
		if (cur_hp < 1){
			if (cooldown == 0){
				cur_hp = max_hp;
				cooldown = 50;
			}
			else {
				if (rand()%100000 == 99999){
					cur_hp = max_hp;
					cooldown = 0;
				}
			}
		}
		if (cooldown == 0)
			npcAttack();
		return 1;
	}
	if (cur_hp < 1)
		return 1;
	if (cooldown <= tFactor)
		cooldown = 0;
	else
		cooldown -= tFactor;
	int temp;
	while (cooldown == 0){
		temp = act();
	};
	return temp;
}

int Entity::act() {
	int action, flag;
	string temp;
	printf("What should %s do?\n", name.c_str());
	printf(" ----------------------------\n");
	for(int i = 0; i < 7; i++) {
		printf("| %5d %-20s |\n", i+1, DUNGEON_OPTIONS[i].c_str());
	}
	printf(" ----------------------------\n");
	while(true) {
		flag = 1;
		printf(" >> ");
		getline(cin, temp);
		if(temp[0] >= '1' && temp[0] <= '7') { 
			temp[1] = '\0';
			action = atoi(temp.c_str()) - 1;
			break;
		} 
		else {
			for(int i = 0; temp[i] != '\0'; i++) {
				temp[i] = tolower(temp[i]);
			}
			for (action = 0; action < 7; action++) {
				if (temp == DUNGEON_OPTIONS[action]) {
					flag = 0;
					break;
				}
			}
			if(flag == 0) {
				break;
			}
			if (action == 6){ //bad input
				printf("I don't recognize that. Please try again.\n");
			}
		}
	}
	if (action == 0)
		attack();
	else if (action == 1)
		defend();
	else if (action == 2)
		skill();
	else if (action == 3)
		item();
	else if (action == 4)
		info();
	else if (action == 5)
		move();
	else if (action == 6){
		cooldown = 100;
		return 0;
	}
	return 1;
}

void Entity::attack() {
	Entity* ePtr;
	int target, size, flag, strSize;
	char charSize;
	string temp;
	size = room->inRoom.size();	
	do {
		printf("Who does %s attack?\n", name.c_str());
		printf(" --------------------------------------\n");
		for(int i = 0; i < size && room->inRoom[i] != NULL; i++) {
			if (room->inRoom[i]->cur_hp < 1){
				strSize = room->inRoom[i]->name.size();
				room->inRoom[i]->name += " dead";
				ePtr = room->inRoom[i];
				printf("| %5d %-30s |\n", i+1, ePtr->name.c_str());
				room->inRoom[i]->name.resize(strSize);
			}
			else {
				ePtr = room->inRoom[i];
				printf("| %5d %-30s |\n", i+1, ePtr->name.c_str());
			}
		}
		printf(" --------------------------------------\n");
		while(true) {
			flag = 1;
			printf(" >> ");
			getline(cin, temp);
			target = atoi(temp.c_str()) - 1;
			if(target >= 0 && target < size) { 
				break;
			} 
			else {
				for(int i = 0; temp[i] != '\0'; i++) {
					temp[i] = tolower(temp[i]);
				}
				for (target = 0; target < size; target++) {
					if (temp == room->inRoom[target]->name) {
						flag = 0;
						break;
					}
				}
				if(flag == 0) {
					break;
				}
				if (target == size){ //bad input
					printf("I don't recognize that. Please try again.\n");
				}
			}
		}
	}while (target == size);
	ePtr = room->inRoom[target];
	if (ePtr->cur_hp < 1){
		ePtr->cooldown += 100;
		return;
	}
	int check = rand()%20;
	if (attributes[3]+check < ePtr->attributes[3]+(rand()%20)){
		printf("%s misses.\n", name.c_str());
		cooldown = 15;
		return;
	}
	check = rand()%attributes[1];
	check -= rand()%ePtr->attributes[5];
	check *= 2;
	if (check < 0)
		check = 0;
	printf("%s deals %d damage.\n", name.c_str(), check);
	ePtr->cur_hp -= check;
	if (ePtr->cur_hp < 1){
		printf("%s has died.\n", ePtr->name.c_str());
		ePtr->cooldown = 100;
		delete ePtr->illusion;
		ePtr->illusion = NULL;
	}
	cooldown = 10;
}

void Entity::defend() {
	defense = attributes[5]*2;
	cooldown = 5;
}

void Entity::skill() {
	Entity* ePtr;
	int target, flag, strSize;
	char charSize;
	string temp;	
	do {
		printf("Which skill does %s use?\n", name.c_str());
		printf(" ----------------------------\n");
		for(int i = 0; i < SKILLS[jobNum]; i++) {
			printf("| %5d %-20s |\n", i+1, SKILL_LIST[jobNum][i].c_str());
		}
		printf(" ----------------------------\n");
		while(true) {
			flag = 1;
			printf(" >> ");
			getline(cin, temp);
			target = atoi(temp.c_str()) - 1;
			if(target >= 0 && target < SKILLS[jobNum]) { 
				break;
			} 
			else {
				for(int i = 0; temp[i] != '\0'; i++) {
					temp[i] = tolower(temp[i]);
				}
				for (target = 0; target < SKILLS[jobNum]; target++) {
					if (temp == room->inRoom[target]->name) {
						flag = 0;
						break;
					}
				}
				if(flag == 0) {
					break;
				}
				if (target == SKILLS[jobNum]){ //bad input
					printf("I don't recognize that. Please try again.\n");
				}
			}
		}
	}while (target == SKILLS[jobNum]);
	skills[target](this);
}

void Entity::item() {return;}

void Entity::info() {return;}

void Entity::move() {
	Entity* ePtr;
	int target, flag;
	string temp;
	do {
		printf("Where does %s move?\n", name.c_str());
		printf(" ----------------------------\n");
		for(int i = 0; i < 4; i++) {
			if (room->doors[i] != NULL)
				printf("| %5d %-20s |\n", i+1, DIRECTIONS[i].c_str());
		}
		printf(" ----------------------------\n");
		while(true) {
			flag = 1;
			printf(" >> ");
			getline(cin, temp);
			target = atoi(temp.c_str()) - 1;
			if(target >= 0 && target < 4) { 
				break;
			} 
			else {
				for(int i = 0; temp[i] != '\0'; i++) {
					temp[i] = tolower(temp[i]);
				}
				for (target = 0; target < 4; target++) {
					if (temp == DIRECTIONS[target]) {
						flag = 0;
						break;
					}
				}
				if(flag == 0) {
					break;
				}
				if (target == 4){ //bad input
					printf("I don't recognize that. Please try again.\n");
				}
			}
		}
	}while (target == 4);
	for (int i = 0; i <= room->doors[target]->inRoom.size(); i++){
		if (i == room->doors[target]->inRoom.size()){
			room->doors[target]->inRoom.push_back(this);
			break;
		}
		if (room->doors[target]->inRoom[i] == NULL){
			room->doors[target]->inRoom[i] = this;
			break;
		}
	}
	for (int i = 0; i < room->inRoom.size(); i++){
		if (room->inRoom[i]->name == name){
			room->inRoom[i] = NULL;
			break;
		}
	}
	sort(room->inRoom.begin(), room->inRoom.end(), comp);
	room = room->doors[target];
	sort(room->inRoom.begin(), room->inRoom.end(), comp);
	cooldown = 10;
}

void Entity::npcAttack() {
	Entity* ePtr;
	if (npc == 1){
		int target = rand()%room->inRoom.size();
		ePtr = room->inRoom[target];
		while (ePtr->name == name || ePtr == NULL){
			target = rand()%room->inRoom.size();
			ePtr = room->inRoom[target];
		}
		printf("%s attacks %s\n", name.c_str(), ePtr->name.c_str());
		int check = rand()%20;
		if (attributes[3]+check < ePtr->attributes[3]+(rand()%20)){
			printf("%s misses.\n", name.c_str());
			cooldown = 20;
			return;
		}
		check = rand()%attributes[1];
		check -= rand()%ePtr->attributes[5];
		if (check < 0)
			check = 0;
		else if (ePtr->defense > 0){
			if (check < ePtr->defense){
				ePtr->defense -= check;
				check = 0;
			}
			else {
				check -= ePtr->defense;
				ePtr->defense = 0;
			}
		}
		check *= 2;
		printf("%s deals %d damage.\n", name.c_str(), check);
		ePtr->cur_hp -= check;
		if (ePtr->cur_hp < 1)
			printf("%s has died.\n", ePtr->name.c_str());
		cooldown = 15;
	}
}

void Entity::load(ifstream& input) {
	int i, j;
	string junk, t_str, argh;
	int temp1, temp2;

	//basic character info reading
	getline(input, name);
	getline(input, species);
	
	input >> cash;
	getline(input, junk);
	input >> level;
	getline(input, junk);
	input >> cooldown;
	getline(input, junk);
	input >> grace;
	getline(input, junk);
	input >> max_hp;
	getline(input, junk);
	input >> cur_hp;
	getline(input, junk);
	input >> max_mp;
	getline(input, junk);
	input >> cur_mp;
	getline(input, junk);
	
	attributes = (byte*)malloc(6);

	for(i = 0; i < 6; i++) {
		getline(input, t_str);
		attributes[i] = (byte) (atoi(t_str.c_str()));
		//input >> attributes[i];
		//getline(input, junk);
	}

	//freaking job time
	getline(input, job.name);
	input >> temp1;
	getline(input, junk);
	for(i = 0; i < temp1; i++) {
		getline(input, t_str);
		job.skills[t_str].name = t_str;
		input >> job.skills[t_str].maxlevel;
		getline(input, junk);
		input >> job.skills[t_str].currentlevel;
		getline(input, junk);
		input >> job.skills[t_str].effect_size;
		getline(input, junk);
		input >> job.skills[t_str].skill_type;
		getline(input, junk);
		input >> job.skills[t_str].mp_cost;
		getline(input, junk);
		input >> job.skills[t_str].accuracy;
		getline(input, junk);
		getline(input, job.skills[t_str].element);

		input >> temp2;
		for(j = 0; j < temp2; j++) {
			getline(input, argh);
			input >> job.skills[t_str].prereqs[argh];
			getline(input, junk);
		}
	}

	//equipment time
	input >> temp1;
	getline(input, junk);
	for(i = 0; i < temp1; i++) {
		getline(input, t_str);
		getline(input, equipment[t_str].name);
		getline(input, equipment[t_str].type);
		input >> equipment[t_str].attack;
		getline(input, junk);
		input >> equipment[t_str].defence;
		getline(input, junk);

		input >> temp2;
		getline(input, junk);
		for(j = 0; j < temp2; j++) {
			getline(input, argh);
			input >> equipment[t_str].elemental[argh];
			getline(input, junk);
		}
	}

	//and. now. for. the. useables. FINALLY.
	input >> temp1;
	getline(input, junk);
	for(i = 0; i < temp1; i++) {
		getline(input, t_str);
		getline(input, useables[t_str].name);
		getline(input, useables[t_str].type);
		input >> useables[t_str].how_many;
		getline(input, junk);
		input >> useables[t_str].effect_size;
		getline(input, junk);
	}

	listAttributes();
}

void Entity::save() {
	ofstream output;
	string filename, temp;
	int i;
	map<string, Skill>::iterator a_it;
	map<string, byte>::iterator b_it;
	map<string, EquipItem>::iterator c_it;
	map<string, UseItem>::iterator d_it;
	map<string, int>::iterator e_it;

	//printf("name: %s\n", name.c_str());

	for(i = 0; name[i] != '\0'; i++) {
		if(name[i] == ' ') {
			filename[i] = '_';
		} else {
			filename[i] = tolower(name[i]);
		}
	}

	filename[i] = '\0';
	//printf("%s\n", filename.c_str());
	filename[i] = '.';
	filename[i+1] = 't';
	filename[i+2] = 'x';
	filename[i+3] = 't';
	filename[i+4] = '\0';

	//printf("%s\n", filename.c_str());

	output.open(filename.c_str());

	//first up, do basic player info
	output << name << endl;
	output << species << endl;

	//I question whether this'll work. Oh well, can fix later
	//output << alignment << endl;

	output << cash << endl;
	output << level << endl;
	output << cooldown << endl;
	output << grace << endl;
	output << max_hp << endl;
	output << cur_hp << endl;
	output << max_mp << endl;
	output << cur_mp << endl;

	for(i = 0; i < 6; i++) {
		output << (int)attributes[i] << endl;
	}

	//next, let's do the job data
	output << job.name << endl;
	output << job.skills.size() << endl;
	for(a_it = job.skills.begin(); a_it != job.skills.end(); a_it++) {
		output << a_it->second.name << endl;
		output << a_it->second.maxlevel << endl;
		output << a_it->second.currentlevel << endl;
		output << a_it->second.effect_size << endl;
		output << a_it->second.skill_type << endl;
		output << a_it->second.mp_cost << endl;
		output << a_it->second.accuracy << endl;
		output << a_it->second.element << endl;
		
		output << a_it->second.prereqs.size() << endl;
		for(b_it = a_it->second.prereqs.begin(); b_it != a_it->second.prereqs.end(); b_it++) {
			output << b_it->first << endl;
			output << b_it->second << endl;
		}
	}

	//and now, for the two maps
	output << equipment.size() << endl;
	for(c_it = equipment.begin(); c_it != equipment.end(); c_it++) {
		output << c_it->first << endl;
		output << c_it->second.name << endl;
		output << c_it->second.type << endl;
		output << c_it->second.attack << endl;
		output << c_it->second.defence << endl;

		output << c_it->second.elemental.size() << endl;
		for(e_it = c_it->second.elemental.begin(); e_it != c_it->second.elemental.end(); e_it++) {
			output << e_it->first << endl;
			output << e_it->second << endl;
		}
	}

	output << useables.size() << endl;
	for(d_it = useables.begin(); d_it != useables.end(); d_it++) {
		output << d_it->first << endl;
		output << d_it->second.name << endl;
		output << d_it->second.type << endl;
		output << d_it->second.how_many << endl;
		output << d_it->second.effect_size << endl;
	}

	output.close();
}

void Entity::levelUp() {
	int temp;

	level++;
	temp = attributes[level%6];
	temp++;
	attributes[level%6] = (byte)temp;

	if(level == 3) {
		skillOne();
	}

	if(level == 5) {
		skillTwo();
	}

	if(level == 8) {
		skillThree();
	}
}

void Entity::skillOne() {
	int i;
	for(i = 0; i < NUM_JOBS; i++) {
		if(job.name == JOBS[i]) {
			break;
		}
	}

	//add skills earned at level 3
	switch(i) {
		case 0: //class == fightared

			break;
		case 1: //class == gambler

			break;
		case 2: //class == prism wizard

			break;
		case 3: //class == clay warrior

			break;
		case 4: //class == dancer

			break;
		case 5: //class == anime kid

			break;
		case 6: //class == vegan

			break;
		case 7: //class == cardmaster

			break;
	}
}

void Entity::skillTwo() {
	int i;
	for(i = 0; i < NUM_JOBS; i++) {
		if(job.name == JOBS[i]) {
			break;
		}
	}

	//add skills earned at level 5
	switch(i) {
		case 0: //class == fightared

			break;
		case 1: //class == gambler

			break;
		case 2: //class == prism wizard

			break;
		case 3: //class == clay warrior

			break;
		case 4: //class == dancer

			break;
		case 5: //class == anime kid

			break;
		case 6: //class == vegan

			break;
		case 7: //class == cardmaster
		
			break;
	}
}

void Entity::skillThree() {

}

bool comp (Entity* ePtr1, Entity* ePtr2){
	if (ePtr1 == NULL)
		return false;
	else if (ePtr2 == NULL)
		return true;
	else
		return ePtr1->attributes[2] < ePtr2->attributes[2];
}