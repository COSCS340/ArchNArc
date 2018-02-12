/*
 *
 */
#include "entities.h"

void Entity::setUpChar(string n, string j) {
	name = n;
	job = j;
	cash = 500; //or whatever we let them start with
	
	if(job == "Prism Wizard") { //or whatever job
		//just throwing out numbers. Finalize later
		serendipity = 3;
		might = 1;
		intelligence = 4;
		grace = 2;
		heart = 4;
		tenacity = 2;
		max_hp = 20;
		cur_hp = max_hp;
		max_mp = 20;
		cur_mp = max_hp;
	} //else if(job == ) { //however many jobs we got
}

void Entity::addEquipment(EquipItem a) {
	
}

void Entity::addUseable(UseItem) {
	
}

void Entity::listAttributes() {
	vector<string, EquipItem>::iterator e_it;
	vector<string, UseItem>::iterator u_it;
}
