#include <string>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <map>
#include <sys/types.h>
using namespace std;

class Skill {
	string name;
	unsigned char maxlevel,currentlevel;
	vector<pair<string,unsigned char> >* prereqs;
	Skill(int);
	~Skill();
};

class Job {
	char* name;
	map<string,Skill> skills;
	unsigned char addSkillPoint(string);
};