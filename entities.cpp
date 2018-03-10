/*
 *
 */
#include <iostream>
#include <set>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <string>
#include "entities.h"
#include "fields.h"


//I feel this might work better as a function than a contructor. What do
//y'all think? Maybe something like
//
//void Entity::newGame() {
//
//to contrast with
//
//void Entity::loadGame() {
Entity::Entity () {
	string temp;
	printf("Enter your characters name: ");
	getline(std::cin, temp);
	name = temp;
	//char ans = 'j';

	//UNLESS WE END UP ADDING RACES, WE MIGHT DELETE THE FOLLOWING.
	//I'M LEAVING IT FOR NOW, THOUGH.

	/*
	while (ans == 'j'){
		printf("Would you like your charater to be a half breed? (y/n)");
		cin >> ans;
		ans = tolower(ans);
		if (ans == 'y' || ans == 'n')
			break;
		printf("Incorrect input. Try again.");
		ans = 'j';
	}
	if (ans == 'n'){
		while () {
			prinftf("What is %s's race?", name.c_str());
			cin >> temp;
			for (int i = 0; i < temp.size(); i++)
				temp[i] = tolower(temp[i]);
			if (temp == "human") {
				serendipity = rand()%20;
				might = 8;
				intelligence = 8;
				grace = 8;
				heart = 8;
				tenacity = 8;
				break;
			}
			else
				printf("Invalid input. Try again.\n");
		}
	}
	else {
		while () {
			prinftf("What is %s's first race?", name.c_str());
			cin >> temp;
			for (int i = 0; i < temp.size(); i++)
				temp[i] = tolower(temp[i]);
			if (temp == "human") {
				serendipity = rand()%10;
				might = 4;
				intelligence = 4;
				grace = 4;
				heart = 4;
				tenacity = 4;
				break;
			}
			else
				printf("Invalid input. Try again.\n");
		}
		while () {
			prinftf("What is %s's second race?", name.c_str());
			cin >> temp;
			for (int i = 0; i < temp.size(); i++)
				temp[i] = tolower(temp[i]);
			if (temp == "human") {
				serendipity += rand()%10;
				might += 4;
				intelligence += 4;
				grace += 4;
				heart += 4;
				tenacity += 4;
				break;
			}
			else
				printf("Invalid input. Try again.\n");
		}
	}
	*/

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
		if(temp == JOBS[0] || temp[0] == '1') {
			//however you use the cursed 'byte' nonsense to say
			//"Hey, make me a fighter"
			//setUpChar();
			break;
		} else if(temp == JOBS[1] || temp[0] == '2') {
			//however you use the cursed 'byte' nonsense to say
			//"Hey, make me a gambler"
			//setUpChar();
			break;
		} else if(temp == JOBS[2] || temp[0] == '3') {
			//however you use the cursed 'byte' nonsense to say
			//"Hey, make me a priz wiz"
			//setUpChar();
			break;
		} else if(temp == JOBS[3] || temp[0] == '4') {
			//however you use the cursed 'byte' nonsense to say
			//"Hey, make me a clay warrior"
			//setUpChar()
			break;
		} else if(temp == JOBS[4] || temp[0] == '5') {
			//however you use the cursed 'byte' nonsense to say
			//"Hey, make me a dancomancer"
			//setUpChar()
			break;
		} else if(temp == JOBS[5] || temp[0] == '6') {
			//however you use the cursed 'byte' nonsense to say
			//"Hey, make me an anime kid"
			//setUpChar()
			break;
		} else { //bad input
			printf("I don't recognize that. Please try again.\n");
		}
	}
}

Entity::Entity(string fileName) {
	
}

typedef unsigned char byte;

//a == race
//r == class
void Entity::setUpChar(string n, byte a, byte r) {
	cash = 500; //or whatever we let them start with
	level = 1;	
	job.name = JOBS[r];

	//why is attributes an array of ints, yet here is treated like an array of byes?
	attributes = (byte*)malloc(6);
    memcpy(attributes,RACEATTS[r],6);

}

void Entity::addEquipment(EquipItem a) {
	
}

void Entity::addUseable(UseItem a) {
	
}

void Entity::listAttributes() {
	map<string, EquipItem>::iterator e_it;
	map<string, UseItem>::iterator u_it;
	map<string, Skill>::iterator s_it;

	printf("\n%30sGold: %d\n", name.c_str(), cash);
	printf("Species: %s\n", species.c_str());
	printf("Class: %s\n\n", job.name.c_str());
	printf("\nCurrent stats\n-----------------------\n");
	printf("HP %3d/%3d        MP %3d/%3d", cur_hp, max_hp, cur_mp, max_mp);
    byte i;
	for(i=0;i<6;i++) printf("%-11s %hhx\n",ATTNAMES[i].c_str(),attributes[i]);

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

void Entity::tick (int tFactor, multiset <Entity>& inDungeon) {
	if (cooldown <= tFactor){
		cooldown = 0;
		act(inDungeon);
	}
	cooldown -= tFactor;
}

void Entity::act(multiset <Entity>& inDungeon) {
	//action();
	// Then take parsed data and perform actions
}

bool Entity::operator< (Entity e){
	return grace < e.getGrace();
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
