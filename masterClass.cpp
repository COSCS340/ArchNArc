/*
 *
 */
#include "masterClass.h"

MasterClass::MasterClass() {
	int p_id;
	char ans;
	char junk[256];
	//ask user whether they wanna start a server or join
	printf("Would you like to be the server (Y or N)?\n>>");
	cin >> ans;
	cin.getline(junk);

	while(tolower(ans) != 'y' && tolower(ans) != 'n') {
		printf("Invalid option. Please enter Y or N\n>>");
		cin >> ans;
		cin.getline(junk);
	}

	if(tolower(ans) == 'y') {
	//	fork and start server running seperately
		p_id = fork();
		if(p_id == 0) {
			//be the server
		} else {
			//be the client
		}
	} else {
	//	try and join requested server
	//	if success
	//		return to main, which'll then call the client
	//	else
	//		fork and start server running seperately
	//		p_id = fork();
	//		if(p_id == 0) {
	//			//be the server
	//		} else {
	//			//be the client
	//		}
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
