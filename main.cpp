#include "fields.h"
#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
using namespace std;

typedef unsigned char byte;

byte cinit();
byte crun();
byte cterm();
byte sinit(byte);
byte srun();
byte sterm();

int spid; // PID of the server, only set to non-zero if this is the client that launched the server

int main(int argc,char** args) {
	spid=0;
	IS in = new_inputstruct(NULL);
	printf("Welcome to Archery & Arcana, player.\nWill you be connecting to a server (0) or starting your own (1)?\n");
	get_line(in);
	if(strcmp(in->fields[0],"0")) {
        printf("How many players will be joining the game?\n");
        get_line(in);
		spid = fork();
		if(!spid) {
			if(sinit(atoi(in->fields[0]))) return 1;
			if(srun()) return 1;
			if(sterm()) return 1;
		}
	}
	if(cinit()) return 1;
	if(crun()) return 1;
	if(cterm()) return 1;
	int i;
	jettison_inputstruct(in);
	if(spid) wait(&i);
}

byte cinit() {

    return 0;
}

byte sinit(byte pc) {

    return 0;
}

byte crun() {

    return 0;
}

byte srun() {

    return 0;
}

byte cterm() {

    return 0;
}

byte sterm() {

    return 0;
}
