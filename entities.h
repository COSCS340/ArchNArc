/*
 *
 */
#include <vector>
#include <string>
#include <map>
#include <set>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
//#include "job.h"

using namespace std;

typedef unsigned char byte;

const int NUM_JOBS = 6;

//ALL PRIVATIZATION HAS BEEN REMOVED. GOT FRUSTRATED ARGUING WITH THE COMPILER.
//IF WE WANT GOOD CODING PRACTICE, IT CAN BE TWEAKED LATER, BUT FOR NOW,
//EVERYTHING IS HELD IN PUBLIC TRUST. WHOO COMMUNISM.

class EquipItem {
	public:

//	private:
		string name;
		string type;
		int attack;
		int defence;
		map<string, int> elemental; //stores either resistance or elemental attack
									//under name "FIRE", "WATER", etc. Int is how much
};

class UseItem {
	public:

//	private:
		string name;
		string type;
		int how_many; //how many character has
		int effect_size; //says how much it heals, or whatever. No clue what the plan is here...
};

class Skill {
	public:
		Skill(int);
		//~Skill();
		string name;
		unsigned char maxlevel,currentlevel;
		vector<pair<string,unsigned char> >* prereqs;
		int effect_size; //for attack value, heal value, etc
		int skill_type; //ie 1 for attack, 2 for heal, etc
		int mp_cost;
		int accuracy;
		string element;
};

class Job {
	public:
		string name;
		map<string, Skill> skills;
		unsigned char addSkillPoint(string);
};


//moved these outside the class, as g++ was getting bitchy about it. Not sure if
//it's something that CAN'T be done in c++ or if we just did it wrong.
//Either way, it works like this, so I'm leaving it for now. -MDS
static const string EQUIPSLOTS[]={"weapon","head","torso","hands","legs","feet"};
static const string ATTNAMES[]={"serendipity","might","intelligence","grace","heart","tenacity"};
static const string RACES[]={"human","chosen"};
static const byte RACEATTS[][6] = {{10,10,10,10,10,10},{3,3,3,3,3,3}};
static const string JOBS[]={"fightard", "gambler", "prism wizard", "clay warrior", "dancomancer", "anime kid"}; //note: some names not final

class Entity {
	public:
		Entity();
		Entity(string);
		Entity(int);
		void setUpChar(byte j); //given name and job, initialize characters
		//static const string EQUIPSLOTS[]={"weapon","head","torso","hands","legs","feet"};
		//static const string ATTNAMES[]={"serendipity","might","intelligence","grace","heart","tenacity"};
		//static const string RACES[]={"human","chosen"};
		//static const byte RACEATTS[][] = {{10,10,10,10,10,10},{3,3,3,3,3,3}};
		//static const string JOBS[]={"fightard", "gambler", "prism wizard", "clay warrior", "dancomancer", "anime kid"}; //note: some names not final

		void setUpChar(string n, byte r); //given name and race, initialize character
		void addEquipment(EquipItem);
		void addUseable(UseItem);
		void listAttributes(); //list all info on character in nice format
		void tick(int, multiset<Entity>& inDungeon);
		bool operator< (Entity E);
		int getCooldown() {return cooldown;}
		int getGrace() {return grace;}
//	private:
		string name;
		Job job;
		string species;
        byte alignment;
		map<string, EquipItem> equipment; //mapped under type, ie "HAT", "TORSO", "WEAPON", etc.
		map<string, UseItem> useables; //mapped under type, ie "POTION", etc.
		map<string, Skill> skills; //mapped under name of skill
		int cash;
		int level;
		int cooldown;
		int grace;
		byte *attributes;
		int max_hp;
		int cur_hp;
		int max_mp;
		int cur_mp;
		void act(multiset<Entity>& inDungeon);
};
