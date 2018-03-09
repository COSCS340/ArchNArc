#include "entities.h"
using namespace std;

class Zone {
public:
    int pop,mpop;
    Entity** ents;
    int empty();
    int full();
    int nsEnt(Entity* e); // I[ns]ert [Ent]ity
    int rmEnt(Entity* e); // [r]e[m]ove [Ent]ity
    int tick();
}

int Zone::empty() {
    return mpop-pop;
}

int Zone::full() {
    return mpop<=pop;
}

int Zone::nsEnt(Entity* e) {
    if(full()) {
        fprintf(stderr,"zone: full, cannot insert entity\n");
        return -1;
    }
    int i=0;
    while(i<mpop&&ents[i]!=0) i++;
    ents[i] = e;
    return 0;
}

int Zone::rmEnt(Enity* e) {
    if(empty()) {
        fprinf(stderr,"zone: empty, cannot remove entity\n");
        return -1;
    }
    int i=0;
    while(i<mpop&&ents[i]!=e) i++;
    if(i==mpop) {
        fprintf(stderr,"zone: cannot remove entity not in zone\n");
        return -1;
    }
    ents[i] = 0;
    return 0;
}

int tick() {
    // Put stuff here to call tick() on all the Entities in the zone
    return 0;
}
