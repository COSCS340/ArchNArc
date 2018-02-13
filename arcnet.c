#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
//#include "planksockets.cpp"

typedef unsigned char byte;

int main(int argc,char** argv) {
    if(argc != 2) {
        fprintf(stderr," usage: arcnet [s|c]\n");
        exit(1);
    }
    if(rinit(0,1,0)) exit(1);
    if(rtick()) exit(1);
    if(rterm()) exit(1);
    exit(0);
}

int ifd,ofd,pc;
byte DEBUG=1;

byte rinit(int i,int o,int pc) { // Takes two FDs, which should each be part of a pipe pairing
    if(DEBUG) printf("arcnet: entering init(%d,%d)\n",i,o);
    ifd = i;
    ofd = o;
    if(DEBUG) printf("arcnet: exiting init(%d,%d)\n",i,o);
    return 0;
}

byte rtick() { // Executes an internal loop that exits when necessary
    if(DEBUG) printf("arcnet: entering rtick()\n");
    unsigned char nd=1,r=0;
    while(nd) {
        
    }
    if(DEBUG) printf("arcnet: exiting rtick()\n");
    return r;
}

unsigned char rterm() {
    if(DEBUG) printf("arcnet: entering term()\n");
    if(ifd > 2 && close(ifd)) {
        fprintf(stderr,"term(): unable to close input file descriptor %d\n",ifd);
        return 1;
    }
    if(ofd > 2 && close(ofd)) {
        fprintf(stderr,"term(): unable to close output file descriptor %d\n",ofd);
        return 1;
    }
    if(DEBUG) printf("arcnet: exiting term()\n");
    return 0;
}
