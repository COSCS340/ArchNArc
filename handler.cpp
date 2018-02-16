#include <set>
#include <iterator>
#include "entities.h"

void handler(set<Entity> sEntity, Entity[] party, int partySize) {
    while(){
		int inDungeon = playerInDungeon(sEntity);
		if (inDungeon){
			
			set<Entity>::iterator it = sEntity.begin();
			for (; it != sEntity.end(); it++)
				it->tick();
		}
		
		for (int i = 0; i < partySize; i++)
			party[i].act();
		if ()// need to exit
			break;
    }
}

int playerInDungeon(set<Entity> sEntity) {
	using namespace std;
	int rv = 0;
	set<Entity>::iterator it;
	for (it = sEntity.begin(); it != sEntity.end(); it++)
		if (it->player)
			rv++;
	return ;
}

