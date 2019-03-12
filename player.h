#ifndef PLAYER_H
#define PLAYER_H
#endif
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

struct player {
	
		player();
		char location;
		string inventory[10];
		bool keepGoing;
		bool secondaryReactorFixed;
		bool hydropaunicsFixed;
		bool AIreset;
		bool navigationFixed;	
		
};
