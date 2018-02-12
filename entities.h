/*
 *
 */
#include <vector>
#include <string>
#include <map>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>

using namespace std;

class EquipItem {
	public:

	private:
		string name;
		string type;
		int attack;
		int defence;
		map<string, int> elemental; //stores either resistance or elemental attack
									//under name "FIRE", "WATER", etc. Int is how much
};

class UseItem {
	public:

	private:
		string name;
		string type;
		int how_many; //how many character has
		int effect_size; //says how much it heals, or whatever. No clue what the plan is here...
};

class Entity {
	public:
		void setUpChar(string n, string j); //given name and job, initialize character
		void addEquipment(EquipItem);
		void addUseable(UseItem);
		void listAttributes(); //list all info on character in nice format
	private:
		string name;
		string job;
		string species;
		map<string, EquipItem> equipment; //mapped under type, ie "HAT", "TORSO", "WEAPON", etc.
		map<string, UseItem> useables; //mapped under type, ie "POTION", etc.
		int cash;
		
		int serendipity;
		int might;
		int intelligence;
		int grace;
		int heart;
		int tenacity;
		int max_hp;
		int cur_hp;
		int max_mp;
		int cur_mp;
};

class Zone {
	public:

	private:
		vector<Entity> active_folks; //all characters in the zone
		string description;
};
