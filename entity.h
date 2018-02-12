/*
 *
 */
#include <string>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <sys/types.h>

using namespace std;

class Entity {
	public:
		Entity();
		~Entity();
		unsigned char level();
		unsigned char serendipity();
		unsigned char might();
		unsigned char intelligence();
		unsigned char grace();
		unsigned char heart(); // Must make Captain Planet and Willard Wright jokes at some point!!!
		unsigned char tenacity();
		unsigned char tick(); // Decrement actframes, and prompt for new action if action lock is over
		unsigned char act(int argc,char** args);
		unsigned char print();
	private:
		unsigned char level,serendipity,might,intelligence,grace,heart,tenacity;
		short actframes; // The counter for how many "frames" of action lock are active
		char* name;
};
