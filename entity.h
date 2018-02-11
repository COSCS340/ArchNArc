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
		lvl();
		str();
		sli();
		sta();
		sol();
		spi();
		ser();
		tick(); // Decrement actframes, and prompt for new action if action lock is over
		print();
	private:
		byte lvl,str,sli,sta,sol,spi,ser;
		short actframes; // The counter for how many "frames" of action lock are active
		string name;
		
};