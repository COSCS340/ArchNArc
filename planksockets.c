// Many thanks and all credit to Dr. Plank for this one

#pragma once
#include <cstring>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <cstdio>
#include <stdlib.h>

namespace NeuroUtils {

/*
    SocketAccept():
    Serves a socket using the given port and accepts a connection on it. 
    Returns a file descriptor for the connection.

    Example usage:
        int port = 5456;
        int fd = SocketAccept(port);
        if(fd <= 0) { perror("SocketAccept"); exit(1);}
        FILE* fin = fdopen(fd, "r");
        FILE* fout = fdopen(fd, "w");

        // Send a message
        fprintf(fout, "Hello! I'm using port %d\n", port);
        fflush(fout);
    
        // Receive a message
        char buf[1000];
        if (fgets(buf, 1000, fin) != NULL)
            printf("I got the message: %s\n", buf);
        else 
            printf("Connection closed\n");
*/
int SocketAccept(int port)
{
    int sock;
    struct sockaddr_in serv_addr, cli_addr;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == -1) {
        perror("SocketAccept: ERROR opening socket");
        exit(1);
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    memset(&cli_addr, 0, sizeof(cli_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);

    // This should help us dodge the "address in use" error as much as possible
    int yes = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1) {
        perror("setsockopt");
        exit(1);
    }
    
    if(::bind(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr))) {
        perror("SocketAccept: bind()");
        exit(1);
    }

    if(listen(sock, 500)) {
        perror("SocketAccept: listen()");
        exit(1);
    }

    return accept(sock, (struct sockaddr *) NULL, NULL);
}

/*
    SocketRequest():
    Connects to the given host using the given port. Returns a file descriptor 
    for the connection. This retries connecting to the given host and port
    until the connection is accepted, sleeping 1 second between tries.

    Example usage:
        int port = 5456;
        int fd = SocketRequest("localhost", port);
        FILE* fin = fdopen(fd, "r");
        FILE* fout = fdopen(fd, "w");

        // Send a message
        fprintf(fout, "Hello! I'm using port %d\n", port);
        fflush(fout);
    
        // Receive a message
        char buf[1000];
        if (fgets(buf, 1000, fin) != NULL)
            printf("I got the message: %s\n", buf);
        else 
            printf("Connection closed\n");
*/
int SocketRequest(const char* host, int port)
{
    int fd;
    struct hostent *he;
    struct sockaddr_in serv_addr;
    bool ok;

    fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd == -1){
        perror("SocketRequest: ERROR opening socket");
        exit(1);
    }
    he = gethostbyname(host);
    if(he == NULL){
        fprintf(stderr, "SocketRequest: ERROR, no such host '%s'\n", host);
        exit(0);
    }

    ok = false;
    while(!ok) {
        bzero((char *) &serv_addr, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(port);
        serv_addr.sin_addr = *(struct in_addr *)(he->h_addr_list[0]);

        ok = (connect(fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) != -1);
        if(!ok) {sleep(1); fprintf(stderr, "Waiting to connect to %s: %d\n", host, port);}
    }

    return fd;

}

}