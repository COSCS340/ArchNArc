#include <set>
#include <iterator>
#include "entities.h"

void handler(set<Entity> sEntity, set<Entity> inTown) {
    while(){
	set<Entity>::iterator it;    
	int tFactor = 100;
	if (playerInDungeon(sEntity)){
		if (inBattle(sEntity))
			tFactor = 1;
		else
			tFactor = 10;
		it = sEntity.begin();
		for (; it != sEntity.end(); it++)
			it->tick(tFactor);
	}
	it = inTown.begin();
	for (; it != inTown.end(); it++)
		it->tick(tFactor);
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
	
}
