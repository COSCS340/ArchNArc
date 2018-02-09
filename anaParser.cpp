#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <cctype>
#include "fields.h"

int action();
void synonyms(char*);
void actionUse(IS);
void actionCheck(IS);
void actionTry(IS);
void actionHelp();
void badInput();

int main () {
	using namespace std;
	int j = 1;
	while (j){
		cout << "What would you like to do?" << endl;
		j = action();
	}
}

int action () {
	using namespace std;
	/* We had talked about using the fields library and Ron was working on porting it over here, so I'll set this up using that.
	string command;
	getline(cin, command);
	string b;

	//Hey, Michaela here. This would be easier with strstr(), if you
	//wanted to simplify searching strings. It'd just need to be with
	//c_strings instead.

	size_t pos = command.find(" ");
	b = command.substr(0, pos);*/
	IS is = new_inputstruct();
	int j = get_line();
	if (j == -1)
		return 0;
	synonyms(is->fields[0]);
	if (b == "try")
		actionTry(is);
	else if (b == "check")
		actionCheck(is);
	else if (b == "help")
		actionHelp();
	else if (b == "use")
		actionUse(is);
	else
		badInput();
	jettison_inputstruct();
	return 1;
}

void actionUse(IS is) {
	if (is->NF == 2){
		
	}
	return;
}

void actionCheck(IS is) {
	return;
}

void actionTry(IS is) {
	return;
}

void actionHelp() {
	std::cout << "Try using an item, skill or spell." << endl
		 << "You can check on the status of enemies and allies or list skills and spells." << endl;
		 << "If you want to know what something will do, try an action." << endl;
}

void badInput() {
	using namespace std;
	cout << "Invalid input. Try again." << endl;
}

void synonyms(char* b) {
	b[0] = tolower(b[0]);
	if (command == "use")
		return;
	else if (b == "try")
		return;
	else if (b == "check")
		return;
	else if (b == "help")
		return;
	else if (command == "eat"){
		b = "use"
		return;
	}
	else if (command == "drink"){
		b = "use";
		return;
	}
	else if (command == "cast"){
		b = "use";
		return;
	}
}
