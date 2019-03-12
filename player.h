#ifndef PLAYER_H
#define PLAYER_H
#endif
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

class player {
	public:
		
		//constructor
		player();
		
		//member variables
		
		char location = 'C';
		string inventory[10];
		bool keepGoing = 1;
		bool secondaryReactorFixed = 0;
		bool hydropaunicsFixed = 0;
		bool AIreset = 0;
		bool navigationFixed = 0;
		
		
		
		
};
