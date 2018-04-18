#include <algorithm>
#include <iostream>
#include <set>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <string>
#include <utility>
//#include "anaParser.h"
#include "entities.h"
#include "fields.h"
#include "skills.h"

void coinFlip(Entity* ePtr){
	if (ePtr->cur_mp < 5){
		printf("%s doesn't have the energy to cast this.\n", ePtr->name.c_str());
		return;
	}
	int payment;
	do {
		printf("How much gold do you pay to Weddench?\n >> ");
		cin >> payment;
		if (payment < 0 || payment > ePtr->cash)
			printf("Invalid input");
	} while (payment > ePtr->cash || payment < 0);
	if (payment == 0)
		payment = 1;
	ePtr->cash -= payment;
	if (rand()%2 == 1){
		printf("Heads. You deal %d damage to all Enemies in this room\n", payment*5);
		for (int i = 0; i < ePtr->room->inRoom.size() && ePtr->room->inRoom[i] != NULL; i++)
			if (ePtr->room->inRoom[i]->npc)
				ePtr->room->inRoom[i]->cur_hp -= payment*5;
	}
	else{
		printf("Tails. You deal %d damage to yourself\n", payment*5);
			ePtr->cur_hp -= payment*5;
	}
	ePtr->cooldown = 20;
	ePtr->cur_mp -= 5;
}

void multislash(Entity* ePtr) {
	if (ePtr->cur_mp < 3){
		printf("%s doesn't have the energy to cast this.\n", ePtr->name.c_str());
		return;
	}
	Entity* ePtr1;
	int target, size, flag, strSize;
	string temp;
	size = ePtr->room->inRoom.size();	
	do {
		printf("Who does %s attack?\n", ePtr->name.c_str());
		printf(" --------------------------------------\n");
		for(int i = 0; i < size && ePtr->room->inRoom[i] != NULL; i++) {
			if (ePtr->room->inRoom[i]->cur_hp < 1){
				strSize = ePtr->room->inRoom[i]->name.size();
				ePtr->room->inRoom[i]->name += " dead";
				ePtr1 = ePtr->room->inRoom[i];
				printf("| %5d %-30s |\n", i+1, ePtr1->name.c_str());
				ePtr->room->inRoom[i]->name.resize(strSize);
			}
			else {
				ePtr1 = ePtr->room->inRoom[i];
				printf("| %5d %-30s |\n", i+1, ePtr1->name.c_str());
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
					if (temp == ePtr->room->inRoom[target]->name) {
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
	ePtr1 = ePtr->room->inRoom[target];
	int payment, strikes, odds;
	do {
		printf("How much gold do you pay to Weddench?\n >> ");
		cin >> payment;
		if (payment < 0 || payment > ePtr->cash)
			printf("Invalid input");
	} while (payment > ePtr->cash || payment < 0);
	ePtr->cash -= payment;
	if (payment > 5){
		payment -= 5;
		strikes = 5;
	}
	else if (payment < 4)
		strikes = 3;
	else {
		strikes = payment;
		payment = 0;
	}
	int tStrikes = 0;
	while (strikes > 0){
		if (payment > 70)
			odds = 70;
		else 
			odds = payment;
		payment -= odds;
		if (ePtr1->cur_hp < 1){
			ePtr1->cooldown += 100;
			if (rand()%100 < 29+odds)
				strikes++;
			strikes--;
			tStrikes++;
			continue;
		}
		int check = rand()%20;
		if (ePtr->attributes[3]+check < ePtr1->attributes[3]+(rand()%20))
			printf("%s misses.\n", ePtr->name.c_str());
		check = rand()%ePtr->attributes[1];
		check -= rand()%ePtr1->attributes[5];
		check *= 2;
		if (check < 0)
			check = 0;
		printf("%s deals %d damage.\n", ePtr->name.c_str(), check);
		ePtr1->cur_hp -= check;
		if (ePtr1->cur_hp < 1){
			printf("%s has died.\n", ePtr1->name.c_str());
			ePtr1->cooldown = 100;
		}
		if (rand()%100 < 29+odds)
			strikes++;
		strikes--;
		tStrikes++;
	}
	ePtr->cooldown = 5*tStrikes;
	ePtr->cur_mp -= 3;
}

void diceBomb(Entity* ePtr) {
	if (ePtr->cur_mp < 10){
		printf("%s doesn't have the energy to cast this.\n", ePtr->name.c_str());
		return;
	}
	int payment, roll, check;
	Entity* ePtr1;
	do {
		printf("How much gold do you pay to Weddench?\n >> ");
		cin >> payment;
		if (payment < 0 || payment > ePtr->cash)
			printf("Invalid input");
	} while (payment > ePtr->cash || payment < 0);
	if (payment == 0)
		payment = 1;
	ePtr->cash -= payment;
	roll = rand()%20;
	if (roll == 0){
		ePtr->cur_hp -= 10;
		ePtr->cooldown = 20;
		return;
	}
	if (roll == 19){
		printf("You hear laughter as Weddench smites your foes.\n");
		for (int i = 0; i < ePtr->room->inRoom.size() && ePtr->room->inRoom[i] != NULL; i++){
			if (ePtr->room->inRoom[i]->npc){
				ePtr->room->inRoom[i]->cur_hp = 0;
				ePtr->room->inRoom[i]->cooldown = 100;
			}
		}
		ePtr->cooldown = 20;
		return;
	}
	if (roll < 8){
		printf("Your dice roll fails.\n");
		ePtr->cooldown = 20;
		return;
	}
	else {
		for (int i = 0; i < ePtr->room->inRoom.size(); i++){
			if (ePtr->room->inRoom[i]->npc){
				ePtr1 = ePtr->room->inRoom[i];
				check = rand()%(ePtr->attributes[1]+payment);
				check -= rand()%ePtr1->attributes[5];
				check *= roll;
				if (check < 0)
					check = 0;
				printf("%s deals %d damage to %s.\n", ePtr->name.c_str(), check, ePtr1->name.c_str());
				ePtr1->cur_hp -= check;
				if (ePtr1->cur_hp < 1){
					printf("%s has died.\n", ePtr1->name.c_str());
					ePtr->cooldown = 100;
				}
			}
		}
	}
	ePtr->cooldown = 20;
	ePtr->cur_mp -= 10;
}

void nightmare(Entity* ePtr){
	if (ePtr->cur_mp < 5){
		printf("%s doesn't have the energy to cast this.\n", ePtr->name.c_str());
		return;
	}
	int size = ePtr->room->inRoom.size();
	for (int i = 0; i < size; i++){
		int res, mag;
		mag = rand()%ePtr->attributes[2];
		if (ePtr->room->inRoom[i]->attributes[4] == 0)
			res = 0;
		else
			res = rand()%ePtr->room->inRoom[i]->attributes[4];
		if (mag > res){
			printf("%s falls to sleep and confronts their worst fears.\n", ePtr->room->inRoom[i]->name.c_str());
			ePtr->room->inRoom[i]->se.push_back(make_pair(0, 30));
		}
		else {
			printf("%s resists your magic.\n", ePtr->room->inRoom[i]->name.c_str());
		}
	}
	ePtr->cooldown = 5;
	ePtr->cur_mp -= 5;
}

void tai(Entity* ePtr){
	if (ePtr->cur_mp < 10){
		printf("%s doesn't have the energy to cast this.\n", ePtr->name.c_str());
		return;
	}
	Entity* ePtr1;
	int target, size, flag, strSize;
	string temp;
	size = ePtr->room->inRoom.size();
	do {
		printf("Who does %s create an illusion for?\n", ePtr->name.c_str());
		printf(" --------------------------------------\n");
		for(int i = 0; i < size && ePtr->room->inRoom[i] != NULL; i++) {
			if (ePtr->room->inRoom[i]->cur_hp < 1){
				strSize = ePtr->room->inRoom[i]->name.size();
				ePtr->room->inRoom[i]->name += " dead";
				printf("| %5d %-30s |\n", i+1, ePtr->room->inRoom[i]->name.c_str());
				ePtr->room->inRoom[i]->name.resize(strSize);
			}
			else {
				printf("| %5d %-30s |\n", i+1, ePtr->room->inRoom[i]->name.c_str());
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
					if (temp == ePtr->room->inRoom[target]->name) {
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
	ePtr->room->inRoom[target]->makeIll("tai");
	ePtr->room->inRoom[target]->illusion->illusion = ePtr;
	ePtr->cur_mp -= 10;
	ePtr->cooldown = 30;
}

void dreamReaper (Entity* ePtr){
	if (ePtr->cur_mp < 5){
		printf("%s doesn't have the energy to cast this.\n", ePtr->name.c_str());
		return;
	}
	int size = ePtr->room->inRoom.size();
	for (int i = 0; i < size; i++){
		if (sleeping(ePtr->room->inRoom[i])){
			int res, mag;
			mag = rand()%ePtr->attributes[2];
			if (ePtr->room->inRoom[i]->attributes[4] == 0)
				res = 0;
			else
				res = rand()%ePtr->room->inRoom[i]->attributes[4];
			if (mag > res){
				printf("%s couldn't escape the reaper.\n", ePtr->room->inRoom[i]->name.c_str());
				ePtr->room->inRoom[i]->cur_hp = 0;
				ePtr->room->inRoom[i]->cooldown = 100;
				delete ePtr->room->inRoom[i]->illusion;
				ePtr->room->inRoom[i]->illusion = NULL;
			}
			else {
				printf("%s resists your magic.\n", ePtr->room->inRoom[i]->name.c_str());
			}
		}
	}
	ePtr->cooldown = 5;
	ePtr->cur_mp -= 5;
}

bool sleeping (Entity* ePtr){
	for (int j = 0; j < ePtr->se.size(); j++)
		if (ePtr->se[j].first == 0)
			return true;
	return false;
}