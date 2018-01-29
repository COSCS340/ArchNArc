#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
int action();
bool useSynonyms(std::string);
void actionUse(std::string, size_t);
void actionCheck(std::string, size_t);
void actionTry(std::string, size_t);
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
	string command;
	getline(cin, command);
	string b;
	size_t pos = command.find(" ");
	b = command.substr(0, pos);
	if (b == "try" || b == "Try")
		actionTry(command, pos+1);
	else if (b == "check" || b == "Check")
		actionCheck(command, pos+1);
	else if (b == "help" || b == "Help")
		actionHelp();
	else if (useSynonyms(b))
		actionUse(command, pos+1);
	else
		badInput();
	return 1;
}

void actionUse(std::string in, size_t pos) {
	return;
}

void actionCheck(std::string in, size_t pos) {
	return;
}

void actionTry(std::string in, size_t pos) {
	return;
}

void actionHelp() {
	cout << "Try using an item, skill or spell." << endl
		 << "You can check on the status of enemies and allies or list skills and spells." << endl;
		 << "If you want to know what something will do, try an action." << endl;
}

void badInput() {
	using namespace std;
	cout << "Invalid input. Try again." << endl;
}

bool useSynonyms(std::string command) {
	if (command == "use" || command == "Use")
		return true;
	else if (command == "eat" || command == "Eat")
		return true;
	else if (command == "drink" || command == "Drink")
		return true;
	else if (command == "cast" || command == "Cast")
		return true;
	else 
		return false;
}
