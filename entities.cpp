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
	map<string, EquipItem>::iterator e_it;
	map<string, UseItem>::iterator u_it;
	map<string, Skill>::iterator s_it;

	printf("\n%30sGold: %d\n", name.c_str(), cash);
	printf("Species: %s\n", species.c_str());
	printf("Class: %s\n\n", job.c_str());
	printf("Current stats\n-----------------------\n");
	printf("HP %3d/%3d        MP %3d/%3d", cur_hp, max_hp, cur_mp, max_mp);
	printf("Serendipity      %d\n", serendipity);
	printf("Might            %d\n", might);
	printf("Intelligence     %d\n", intelligence);
	printf("Grace            %d\n", grace);
	printf("Heart            %d\n", heart);
	printf("Tenacity         %d\n", tenacity);

	//print equipment, useables, and skills
}
