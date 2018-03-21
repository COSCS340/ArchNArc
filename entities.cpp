/* File: entities.cpp
 * Author: collective effort of Team Archery and Arcana
 * Regrets: none
 */
#include <iostream>
#include <set>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <string>
//#include "anaParser.h"
#include "entities.h"
#include "fields.h"

const string pos_names[] = {"Manaliabrid", "Osfameron", "Deryn", "Brutha", "Anevka", "Enoch", "Sandrilene", "Theophrastus", "Hazel", "Kevin", "Gladys", "Anatolio", "Lyseria", "Bob", "Azula", "Krauss", "Amakusa", "Rudolph", "Adara", "Janus", "Aeronwen", "Keichi", "Branwen", "Alwyn", "Dwynwen", "Cadfael", "Hywela", "Emlyn", "Maelona", "Gwalchgwyn", "Nerys", "Idris", "Sioned", "Llywellyn", "Yseult"};
const string pos_titles[] = {" the Foolhardy", " the Cowardly", " the Crusader", " the Incompetent", " the Flautist", " the Sleep-Deprived", " the Tennessean", " the Overlord", " the Hatter", " the Sunseeker", " the Fluffy", " the Timejumper", " the Darwinist", " the Mentor", " the Lucky", " the Left-Footed", " the Ace", " the Stingy", " the Executioner", " the Fraudulent", " the NPC", " the Hopeful", " the Morbid", " the Bemused", " the Concerned", " the Unworthy", " the Tree-Hugger", " the Earthbound", " the Oblivious", " the Immortal", " the Mortal", " the Corrupted", " the Pessimist", " the Seg-Fault", " the Silent", " the Clothed", " the Paranoid", " the Caffeinated", " the Lost", " the Error", " the Conspirator", " the Punctual", " the Liar", " the Felon", " the Ignoble", " the Mispronounced", " the Righteous", " the Blasphemous"};
const int NUM_NAMES = 34;
const int NUM_TITLES = 48;

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

}

void Entity::generateChar() {
	int temp1, temp2;

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
	//memcpy(attributes,RACEATTS[r],6);
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
	printf("\nEquipment    \n-----------------------\n");
	for(e_it = equipment.begin(); e_it != equipment.end(); e_it++) {
		printf("%15s %s\n", e_it->first.c_str(), e_it->second.name.c_str());
	}

	printf("\nSupplies     \n-----------------------\n");
	for(u_it = useables.begin(); u_it != useables.end(); u_it++) {
		printf("%15s %d\n", u_it->first.c_str(), u_it->second.how_many);
	}

	printf("\nSkills       \n-----------------------\n");
	for(s_it = job.skills.begin(); s_it != job.skills.end(); s_it++) {
		printf("%15s\n", s_it->first.c_str());
	}
	printf("\n");
}

void Entity::tick (int tFactor) {
	if (cooldown <= tFactor){
		cooldown = 0;
		act();
		return;
	}
	cooldown -= tFactor;
}

void Entity::act() {
	int a;
	cout << "What does " << name  << " do? ";
	cin >> a;
	if (a == 0){
		cout << "You attack" << endl;
		cooldown = 100;
	}
	if (a == 1){
		cout << "You defend" << endl;
		cooldown = 10;
	}
	//action();
	// Then take parsed data and perform actions
}

void Entity::load(ifstream& input) {

}

void Entity::save() {
	ofstream output;
	string filename;
	int i;
	map<string, Skill>::iterator a_it;
	map<string, byte>::iterator b_it;
	map<string, EquipItem>::iterator c_it;
	map<string, UseItem>::iterator d_it;
	map<string, int>::iterator e_it;

	for(i = 0; name[i] != '\0'; i++) {
		filename[i] = tolower(name[i]);
	}
	filename[i] = '\0';
	filename = filename + ".txt";

	output.open(filename.c_str());

	//first up, do basic player info
	output << name << endl;
	output << species << endl;

	//I question whether this'll work. Oh well, can fix later
	output << alignment << endl;

	output << cash << endl;
	output << level << endl;
	output << cooldown << endl;
	output << grace << endl;
	output << max_hp << endl;
	output << cur_hp << endl;
	output << max_mp << endl;
	output << cur_mp << endl;

	for(i = 0; i < 6; i++) {
		output << attributes[i] << endl;
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