#include <set>
#include <iterator>
#include "entities.h"

bool playerInDungeon(set<Entity> sEntity);
bool inBattle (set<Entity> sEntity);

void handler(std::multiset<Entity> sEntity, set<Entity> inTown) {
    while(){
	std::multiset<Entity>::iterator it;    
	int tFactor = 100;
	if (playerInDungeon(sEntity)){
		if (inBattle(sEntity))
			tFactor = 1;
		else
			tFactor = 10;
		it = sEntity.begin();
		for (; it != sEntity.end(); it++)
			it->tick(tFactor, sEntity);
	}
	it = inTown.begin();
	for (; it != inTown.end(); it++)
		it->tick(tFactor, sEntity);
	if ()// need to exit
		break;
    }
}

bool playerInDungeon(set<Entity> sEntity) {
	using namespace std;
	set<Entity>::iterator it;
	for (it = sEntity.begin(); it != sEntity.end(); it++)
		if (it->player)
			retrun true;
	return false;
}

bool inBattle (set<Entity> sEntity) {
	return false;
	//Not sure how we will be storing rooms, just need to check and see if enemies are in the room with the player 
}
