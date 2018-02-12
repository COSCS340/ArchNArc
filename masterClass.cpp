/*
 *
 */
#include "masterClass.h"

MasterClass::MasterClass() {
	int p_id;
	char ans;
	char junk[256];
	int sock, port, fd;
	char server_name[256];
	//ask user whether they wanna start a server or join
	printf("Would you like to be the server (Y or N)?\n>> ");
	cin >> ans;
	cin.getline(junk);

	while(tolower(ans) != 'y' && tolower(ans) != 'n') {
		printf("Invalid option. Please enter Y or N\n>> ");
		cin >> ans;
		cin.getline(junk);
	}

	if(tolower(ans) == 'y') {
	//	fork and start server running seperately
		p_id = fork();
		if(p_id == 0) { //be the server
			printf("Please enter your host name\n>> ");
			cin.getline(server_name);
			port = 5041;

			//sock = serve_socket(server_name, port);
			//fd = accept_connection(sock);

			//test stuff

		} else { //be the client
			//wait a bit (to ensure server gets put up)
			//sleep();

			//check if server be working
			printf("Please enter the host name\n>> ");
			cin.getline(server_name);
			port = 5041;

			//fd = request_connection(server_name, port);

			//test stuff
		}
	} else {
		//ask what server they wanna join
		printf("Please enter your host name\n>> ");
		cin.getline(server_name);
		port = 5041;

		//sock = serve_socket(server_name, port);
		//fd = accept_connection(sock);

		//test

		//if success
		//	return to main, which'll then call the client
		//else
		//	fork and start server running seperately
		//	p_id = fork();
		//	if(p_id == 0) { //be the server
		//		//set up as server
		//		//give user info needed to let other people join server
		//	} else { //be the client
		//		//wait a bit (to ensure server gets put up)
		//		sleep();
		//
		//		printf("Please enter the host name\n>> ");
		//		cin.getline(server_name);
		//		port = 5041;
		//
		//		fd = request_connection(server_name, port);
		//		//test
		//	}
	}

}

void MasterClass::server() {
	//be the manager/server
}

void MasterClass::client() {
	//any set up
	
	//go into player functions/gameplay functions
}

void MasterClass::scrapAll() {
	//anything need to be disposed of? Here's where to do it.
}
