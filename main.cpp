#include "fields.h"
#include <cstdio>
using namespace std;

unsigned char cinit();
unsigned char crun();
unsigned char cterm();
unsigned char sinit();
unsigned char srun();
unsigned char sterm();

int spid; // PID of the server, only set to non-zero if this is the client that launched the server

int main(int argc,char** args) {
	spid=0;
	IS* in = new_inputstruct(NULL);
	printf("Welcome to Archery & Arcana, player.\nWill you be connecting to a server (0) or starting your own (1)?\n");
	getline(in);
	if(strcmp(in->fields[0],"0")) {
		spid = fork();
		if(!spid) {
			if(sinit()) exit(1);
			if(srun()) exit(1);
			if(sterm()) exit(1);
		}
	}
	if(cinit()) exit(1);
	if(crun()) exit(1);
	if(cterm()) exit(1);
	int i;
	if(spid) wait(&i);
}