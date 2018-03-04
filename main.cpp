#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "fields.h"
#include "entities.h"
using namespace std;

typedef unsigned char byte;

byte cinit();
byte crun();
byte cterm();

int spid; // PID of the server, only set to non-zero if this is the client that launched the server

int main(int argc,char** args) {
	spid=0;
	IS in = new_inputstruct(NULL);
	printf("Welcome to Archery & Arcana, player.\n");
	if(cinit()) return 1;
	if(crun()) return 1;
	if(cterm()) return 1;
	int i;

	Entity ne;

	jettison_inputstruct(in);
	if(spid) wait(&i);
}

byte cinit() {
    
    return 0;
}

byte crun() {

    return 0;
}

byte cterm() {

    return 0;
}
