/*
 *
 */
#include <unistd.h>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

typedef unsigned char byte;

const int NUM_JOBS = 6;
static const string EQUIPSLOTS[]={"weapon","head","torso","hands","legs","feet"};
static const string ATTNAMES[]={"serendipity","might","intelligence","grace","heart","tenacity"};
static const string RACES[]={"human","chosen"};
static const byte RACEATTS[][6] = {{10,10,10,10,10,10},{3,3,3,3,3,3}};
static const string JOBS[]={"fightard", "gambler", "prism wizard", "clay warrior", "dancomancer", "anime kid", "VEGAN", "Cardmaster"}; //note: some names not final
static const string DUNGEON_OPTIONS[] = {"Attack", "Defend", "Skill", "Item", "Info"};


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
		map<string, byte> prereqs;
		//vector<pair<string,unsigned char> >* prereqs;
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

class Tile {
	public:
	vector <class Entity*> inRoom;
};

class Entity {
	public:
		Entity() {return;}
		void setUpChar(string, byte, byte); //given name and job, initialize characters
		void generateChar();
		void setUpChar(string n, byte r); //given name and race, initialize character
		void addEquipment(EquipItem);
		void addUseable(UseItem);
		void listAttributes(); //list all info on character in nice format
		void tick(int);
		bool operator< (const Entity& e) const {return grace > e.grace;}
		//bool operator> (const Entity& e) const {return grace < e.grace;}
		int getCooldown() {return cooldown;}
		int getGrace() {return grace;}
		void save();
		void load(ifstream&);
		void attack();
		void defend();
		void skill();
		void item();
		void info();
//	private:
		string name;
		Job job;
		string species;
		byte alignment;
		int npc;
		map<string, EquipItem> equipment; //mapped under type, ie "HAT", "TORSO", "WEAPON", etc.
		map<string, UseItem> useables; //mapped under type, ie "POTION", etc.
		int cash;
		int level;
		int cooldown;
		int grace;
		byte *attributes;
		int max_hp;
		int cur_hp;
		int max_mp;
		int cur_mp;
		void act();
		Tile* room;
		void npcAttack();
};
