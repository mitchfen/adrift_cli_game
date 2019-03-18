/*
 * Tasks required to complete the game:
 *  Repair secondary reactor (need wrench)
 *  Replace CO2 filter in hydroponics (need filter)
 *  Reset the AI (need all three fuses)
 *  Correct course on navigation computer in the bridge (requires all other goals be complete)
 *  
 * Inventory array indices:
 *  0 leaflet (galley)
 *  1 wrench (observation deck)
 *  2 15A fuse (Engine room)
 *  3 20A fuse (Storage)
 *  4 50A fuse (Primary reactor)
 *  5 CO2 filter (Storage)
 * 
 * 
 * TODO
 * 	2) update cryo terminal depending on whether things fixed or not (used player booleans)
 *  3) elseCatcher(input) - plz god save before doing this
*/
#include "player.cpp"
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <thread>
using namespace std;

// Function prototypes
void printwelcome();
string getFileContents(ifstream&);
void helper();
void terminal1();
void terminal2(player& p1);
void terminal3(player& p1);
void inventoryChecker(player& p1);
void idkWhatYouMean(string input);
void leafletReader(player& p1);

// Room function prototypes
void cryo(string input, player& p1);
void corridor(string input, player& p1);
void mainCorridor(string input, player& p1);
void galley(string input, player& p1);
void engineRoom(string input, player& p1);
void hydroponics(string input, player& p1);
void AIcore(string input, player& p1);
void storage(string input, player& p1);
void primaryReactor(string input, player& p1);
void bridge(string input, player& p1);
void observationDeck(string input, player& p1);
void secondaryReactor(string input, player& p1);




// Global variables
string input = "";
bool firstTimeCryo = true;
bool storageFuseTaken = 0;
bool storageFilterTaken = 0;
bool engineRoomFuseTaken = 0;
bool primaryReactorFuseTaken = 0;
bool leafletTaken = 0;

int main () {

	player p1;
	printwelcome();
	cout << endl;
	cout << "You are standing in the cryo bay.\n";
	cout << "The door on your left leads to the aft corridor.\n";
	cout << "There are four cryo pods and a terminal here.\n";
	cout << endl;
	while (p1.keepGoing) {
		switch (p1.location) {

			// Cryo
			case 'C':
				cryo(input, p1);
				break;
			// Aft corridor - changed functionality but not name
			case 'c':
				corridor(input, p1);
				break;
			case 'g':
				galley(input, p1);
				break;
			case 'e':
				engineRoom(input, p1);
				break;
			case 'h':
				hydroponics(input, p1);
				break;
			case 'a':
				AIcore(input, p1);
				break;
			case 's':
				storage(input, p1);
				break;
			case 'R':
				primaryReactor(input, p1);
				break;
			case 'b':
				bridge(input, p1);
				break;
			case 'o':
				observationDeck(input, p1);
				break;
			// Main corridor
			case 'm':
				mainCorridor(input, p1);
				break;
			// Secondary reactor
			case 'z':
				secondaryReactor(input, p1);
				break;
			// switch to blank room to trigger win
			case 'w':
				break;
		}

	}
	cout << endl; 
	cout << "###########################" << endl;
	cout << "#                         #" << endl;
	cout << "#         YOU WIN!        #" << endl;
	cout << "#  Thank you for playing  #" << endl;
	cout << "#                         #" << endl;
	cout << "###########################" << endl;
}

void printwelcome() {
	// Print text in authorinfo.txt
	ifstream reed ("authorinfo.txt");
	string printy = getFileContents(reed);
	cout << endl << printy << endl;
	reed.close ();

	// Feed down and print ASCII art after 5 seconds
	this_thread::sleep_for(std::chrono::seconds(5));
	cout << "\n\n\n\n\n\n\n\n\n";
    ifstream Reader ("ascii.txt");
	string Art = getFileContents(Reader);
	cout << endl << Art << endl;
	Reader.close ();

	// print from welcome.txt
	ifstream ready ("welcome.txt");
	string printyplease = getFileContents(ready);
	cout << endl << printyplease;
	ready.close ();
}

string getFileContents (ifstream& File) {
	string Lines = "";

	if (File) {
		while (File.good()) {
			string TempLine;
			getline (File, TempLine);
			TempLine += "\n";
			Lines += TempLine;
		}
		return Lines;
	}

	else {
		return "Error";
	}
}

void helper() {
		cout << endl;
		cout << "You can type:\n";
		cout << "go... up, left, right, down, forward, back.\n";
		cout << "take, look, activate terminal, inventory.\n";
		cout << endl;
}

void idkWhatYouMean(string input) {
	if (input == "")
		cout << endl << "..." << endl << endl;
	else if (input.find("go") < 1000)
		cout << endl << "You can't go that way." << endl << endl;
	else
		cout << endl << "..." << endl << endl;

}

void terminal1() {
	string password = "";
	string terminalInput = "";
	cout << endl;
	cout << "\t ****** Welcome ******\n";
	cout << "\t Please enter your password: ";
	getline(cin, password);
			if (password == "z18") {
				cout << endl;
				cout << "\t Terminal unlocked.\n";
				cout << "\t Would you like to view the ship diagnostics? (y/n)";
				getline(cin, terminalInput);
				if (terminalInput == "y") {
					cout << endl;
					cout << "\t\t\t WARNING *** WARNING *** WARNING\n";
					cout << "\t Multiple critical system failures detected... Immediate action required.\n";
					cout << "\t System failures ranked in order of risk to crew:\n";
					cout << "\t [1] Secondary reactor temperature above safe levels.\n";
					cout << "\t [2] CO2 scrubber failure in hydroponics.\n";
					cout << "\t [3] AI nonfunctional.\n";
					cout << "\t [4] Navigation system offline, course correction required.\n";
					cout << "\t Exiting terminal\n";
					cout << endl;
				}
				else if (terminalInput == "n") {
					cout << "\t Exiting terminal.\n";
					cout << endl;
				}
				else {
					cout << "\t Invalid input, exiting terminal.\n";
					cout << endl;
				}
			}
			else {
				cout << "\t Password incorrect, exiting terminal.\n";
				cout << endl;
			}
}

void terminal2(player& p1) {
	string terminalInput = "";
	cout << endl << "\t ****** Welcome ******" << endl;
	cout << "\t Would you like to view the reactor diagnostics? (y/n)";
	getline(cin, terminalInput);
	while (p1.secondaryReactorFixed == 0) {
			if (terminalInput == "y") {
				cout << "\t 4/23/3174 - Warning - Cooling system failure detected.\n";
				cout << "\t 4/23/3174 - Update  - Reactor temperature above safe operating temperatures.\n";
				cout << "\t 4/25/3174 - WARNING - Reactor temperature above critical operating temperatures.\n";
				cout << "\t 4/25/3174 - WARNING - Reactor temperatures above shutdown threshhold. Reactor shutting down.\n";
				cout << "\t Exiting terminal\n";
				cout << endl;
				break;
			}
			else if (terminalInput == "n") {
				cout << "\t Exiting terminal.\n";
				cout << endl;
				break;
			}
			else {
				cout << "\t Invalid input, exiting terminal.\n";
				cout << endl;
				break;
			}
	}
	while (p1.secondaryReactorFixed == 1) {
		if (terminalInput == "y") {
			cout << endl;
			cout << "\t 4/23/3174 - Warning - Cooling system failure detected.\n";
			cout << "\t 4/23/3174 - Update  - Reactor temperature above safe operating temperatures.\n";
			cout << "\t 4/25/3174 - WARNING - Reactor temperature above critical operating temperatures.\n";
			cout << "\t 4/25/3174 - WARNING - Reactor temperatures above shutdown threshhold. Reactor shutting down.\n";
			cout << "\t 6/03/3174 - Update  - Cooling system reboot initiated. Bringing reactor online.\n";
			cout << "\t 6/03/3174 - Update  - Reactor online, operating normally.\n";
			cout << "\t Exiting terminal\n";
			cout << endl;
			break;
		}
		else if (terminalInput == "n") {
			cout << "Exiting terminal.\n";
			cout << endl;
			break;
		}
		else {
			cout << "\t Invalid input, exiting terminal.\n";
			cout << endl;
			break;
		}
	}
}

void terminal3(player& p1) {
	cout << endl << "\t ****** Welcome To Nav-E.Z.******" << endl;
	
	if (p1.hydropaunicsFixed == 1 && p1.AIreset == 1 && p1.hydropaunicsFixed == 1 && p1.secondaryReactorFixed == 1 ) {
		cout << "\t Pinging ship systems...\n";
		cout << "\t All ship systems operational. Nav-E.Z. coming online...\n";
		cout << "\t Correcting course for Alpha Centauri B.\n";
		cout << endl;
		p1.keepGoing = 0;
		p1.location = 'w';
	}
	else {
		cout << "\t Navigation cannot be reset until other ship functions fully restored.\n";
		cout << "\t Please see the terminal in the cryo chamber for details.\n";
		cout << endl;
	}
}

void inventoryChecker(player& p1) {

		bool goForPrint;
		// Check if inventory array empty
		for (int i = 0; i < 10; i++)
			if (p1.inventory[i] != "")
				goForPrint = true;
		// If not empty, print contents
		if (goForPrint) {
			cout << endl;
			cout << "You are carrying: " << endl;
			for (int i = 0; i < 10; i++)
				if (p1.inventory[i] != "")
					cout << "   " << p1.inventory[i] << endl;
		}
		else
			cout << endl << "Inventory is empty!" << endl << endl;
		cout << endl;
}

void leafletReader(player& p1) {
	if (p1.inventory[0] == "leaflet") {
		cout << endl;
		cout << "\t Looking more closely at the leaflet you see it's just a page torn\n";
		cout << "\t from a technical manual about cryopod maintainence. You don't see how it can help you.\n";
		cout << "\t You are about to dispose of it when you see someone has scrawled \"z18\" near the bottom of the page.\n";
		cout << endl;
	}
	else
		cout << endl << "What are you talking about? You don't have a leaflet to read.\n" << endl;
}

void cryo(string input, player& p1) {

	//This block makes it so that "You are in..." does not print on game start
	if (firstTimeCryo )
		cout << "";
	else if (firstTimeCryo == false) {
	cout << endl;
	cout << "You are now in the cryo bay.\n";
	cout << endl;
	}
	firstTimeCryo = false;

	while (p1.location == 'C'){
		getline(cin, input);
		if (input == "help") {
			helper();
		}
		else if (input == "look") {
			cout << endl;
			cout << "You are standing in the cryo bay.\n";
			cout << "The door on your left leads to the aft corridor.\n";
			cout << "There are four cryo pods and a terminal here.\n";
			cout << endl;
		}
		else if (input == "activate terminal"){
			terminal1();
		}

		else if (input == "go left"){
			p1.location = 'c';
		}
		
		else if (input == "read leaflet"){
			leafletReader(p1);
		}

		else if (input == "inventory"){
			inventoryChecker(p1);
		}
		else {
			idkWhatYouMean(input);
		}
	}
}

void mainCorridor(string input, player& p1) {
	cout << endl;
	cout << "You are now in the main corridor.\n";
	cout << endl;
	while (p1.location == 'm'){
		getline(cin, input);
		if (input == "help") {
			helper();
		}
		else if (input == "look") {
			cout << endl;
			cout << "You are standing in the main corridor.\n";
			cout << "The storage room is to your right.\n";
			cout << "The hydroponics lab is to your left.\n";
			cout << "The aft corridor is behind you.\n";
			cout << "The galley is ahead.\n";
			cout << endl;
		}
		else if (input == "go right") {
			p1.location = 's';
		}
		else if (input == "go left") {
			p1.location = 'h';
		}
		else if (input == "go back") {
			p1.location = 'c';
		}
		else if (input == "go forward") {
			p1.location = 'g';
		}
		else if (input == "read leaflet"){
			leafletReader(p1);
		}
		else if (input == "inventory") {
			inventoryChecker(p1);
		}
		else {
			idkWhatYouMean(input);
		}
	}

}

void corridor(string input, player& p1) {
	cout << endl;
	cout << "You are now in the aft corridor.\n";
	cout << endl;
	while (p1.location == 'c'){
		getline(cin, input);
		if (input == "help") {
			helper();
		}
		else if (input == "look") {
			cout << endl;
			cout << "You are standing in the aft corridor.\n";
			cout << "The cryo chamber is to your right.\n";
			cout << "The AI-core is to your left.\n";
			cout << "The Engine room is behind you.\n";
			cout << "The main corridor is ahead.\n";
			cout << endl;
		}
		else if (input == "go right") {
			p1.location = 'C';
		}
		else if (input == "go left") {
			p1.location = 'a';
		}
		else if (input == "go back") {
			p1.location = 'e';
		}
		else if (input == "go forward") {
			p1.location = 'm';
		}
		else if (input == "read leaflet"){
			leafletReader(p1);
		}
		else if (input == "inventory") {
			inventoryChecker(p1);
		}
		else {
			idkWhatYouMean(input);
		}
	}

}

void galley(string input, player& p1) {
	cout << endl;
	cout << "You are now in the galley.\n";
	cout << endl;
	while (p1.location == 'g'){
		getline(cin, input);
		if (input == "help") {
			helper();
		}
		else if (input == "look") {
			cout << endl;
			cout << "You are standing in the galley.\n";
			cout << "The bridge is ahead, the main corridor is behind you.\n";
			if ( leafletTaken == 0 ) {
				cout << "There are six tables here. One of them has a small leaflet on the seat.\n";
				cout << endl;
			}
			else if ( leafletTaken == 1 ) {
				cout << endl;
			}
		}
		else if (input == "go back") {
			p1.location = 'm';

		}
		else if (input == "take leaflet") {
			leafletTaken = 1;
			p1.inventory[0] = "leaflet";
			cout << endl;
			cout << "Taken.\nYou can read it with \"read leaflet\".\n";
			cout << endl;
		}
		else if (input == "go forward") {
			p1.location = 'b';
		}
		else if (input == "read leaflet"){
			leafletReader(p1);
		}
		else if (input == "inventory") {
			inventoryChecker(p1);
		}
		else {
			idkWhatYouMean(input);
		}
	}


}

void engineRoom(string input, player& p1) {
	cout << endl;
	cout << "You are now in the engine room.\n";
	cout << endl;
	while (p1.location == 'e'){
		getline(cin, input);
		if (input == "help") {
			helper();
		}
		else if (input == "look") {
			if (engineRoomFuseTaken == 0) {
				cout << endl;
				cout << "You are standing in the engine room.\n";
				cout << "The aft corridor is behind you.\n";
				cout << "The engine seems to be functional, needing only one reactor to operate normally.\n";
				cout << "You see a small fuse on the floor.\n";
				cout << endl;
			}
			else if (engineRoomFuseTaken == 1) {
				cout << endl;
				cout << "You are standing in the engine room.\n";
				cout << "The aft corridor is behind you.\n";
				cout << "The engine seems to be functional, needing only one reactor to operate normally.\n";
				cout << endl;
			}
		}
		else if (input == "go back") {
			p1.location = 'c';
		}
		else if (input == "take fuse") {
			p1.inventory[2] = "15A fuse";
			engineRoomFuseTaken = 1;
			cout << endl << "Taken.\n" << endl;
		}
		else if (input == "read leaflet"){
			leafletReader(p1);
		}
		else if (input == "inventory") {
			inventoryChecker(p1);
		}
		else {
			idkWhatYouMean(input);
		}
	}
}

void hydroponics(string input, player& p1) {
	cout << endl;
	cout << "You are now in the hydroponics lab.\n";
	cout << endl;
	while (p1.location == 'h'){
		getline(cin, input);
		if (input == "help") {
			helper();
		}
		else if (input == "look") {
			if (p1.hydropaunicsFixed == 0) {
				cout << endl;
				cout << "You are standing in the hydroponics room.\n";
				cout << "There is a ladder here leading up to reactor 1.\n";
				cout << "The main corridor is behind you.\n";
				cout << "You see a blinking red light beneath above the CO2 filter.\n";
				cout << endl;
			}
			else if (p1.hydropaunicsFixed == 1 ) {
				cout << endl;
				cout << "You are standing in the hydroponics room.\n";
				cout << "There is a ladder here leading up to reactor 1.\n";
				cout << "The main corridor is behind you.\n";
				cout << "The light above the CO2 filter is now green.\n";
				cout << endl;
			}
		}
		else if (input == "go back") {
			p1.location = 'm';
		}
		else if (input == "go up") {
			p1.location = 'R';
		}
		else if ((input == "replace filter") || (input == "replace CO2 filter") || (input == "fix CO2 filter") || (input == "fix filter") ){
			if (p1.inventory[5] == "CO2 filter") {
				cout << endl << "You install the replacement filter. The red light stops blinking.\n" << endl;
				p1.hydropaunicsFixed = 1;
				p1.inventory[5] = "";
			}
			else
				cout << endl << "You need a replacement filter to do that.\n" << endl;
		}
		else if (input == "read leaflet"){
			leafletReader(p1);
		}
		else if (input == "inventory") {
			inventoryChecker(p1);
		}
		else {
			idkWhatYouMean(input);
		}
	} // end while
}

void AIcore(string input, player& p1) {
	cout << endl;
	cout << "You are now in the AI core.\n";
	cout << endl;
	while (p1.location == 'a'){
		getline(cin, input);
		if (input == "help") {
			helper();
		}
		else if (input == "look") {
			if (p1.AIreset == 0) {
				cout << endl;
				cout << "You are standing in the room housing the AI core.\n";
				cout << "The aft corridor is behind you.\n";
				cout << "Computers hum around you. A panel on the wall glows red. There are 3 broken fuses inside.\n";
				cout << "It needs a replacement 50A fuse, 20A fuse, and 15A fuse.\n";
				cout << endl;
			}
			else if (p1.AIreset == 1) {
				cout << endl;
				cout << "You are standing in the room housing the AI core.\n";
				cout << "The aft corridor is behind you.\n";
				cout << "The ship AI is fully operational now.\n";
				cout << endl;
			}
		}
		else if (input == "go back") {
			p1.location = 'c';
		}
		else if ((input == "replace fuses") || (input == "replace fuse") || (input == "fuses") || (input == "fix fuses")){
			if ((p1.inventory[2] == "") || (p1.inventory[3] == "") || (p1.inventory[4] == "")) {
				cout << endl << "You need all 3 fuses to fix the AI core.\n" << endl;
			}
			else {
				cout << endl;
				cout << "You place all three fuses in their place. The AI core grows louder as more computers power up.\n";
				cout << "A synthetic voice comes over the speaker in the ceiling. \"AI core reboot initiated\".\n";
				cout << endl;
				p1.AIreset = 1;
				p1.inventory[2] = ""; p1.inventory[3] = ""; p1.inventory[4] = "";
			}
		}
		else if (input == "read leaflet"){
			leafletReader(p1);
		}
		else if (input == "inventory") {
			inventoryChecker(p1);
		}
		else {
			idkWhatYouMean(input);
		}
	} // end while
}

void storage(string input, player& p1) {
	cout << endl;
	cout << "You are now in the storage room.\n";
	cout << endl;
	while (p1.location == 's'){
		getline(cin, input);
		if (input == "help") {
			helper();
		}
		else if (input == "look") {
			if (storageFilterTaken == 0 && storageFuseTaken == 0) {
				cout << endl;
				cout << "You are standing in the storage room.\n";
				cout << "The main corridor is behind you.\n";
				cout << "There is a ladder here leading up to the secondary reactor.\n";
				cout << "Shelves line the room, the metal boxes are free of dust and shine in the light.\n";
				cout << "One of the boxes is open, there is a fuse and a CO2 filter inside.\n";
				cout << endl;
			}
			else if (storageFilterTaken == 0 && storageFuseTaken == 1) {
				cout << endl;
				cout << "You are standing in the storage room.\n";
				cout << "The main corridor is behind you.\n";
				cout << "There is a ladder here leading up to the secondary reactor.\n";
				cout << "Shelves line the room, the metal boxes are free of dust and shine in the light.\n";
				cout << "One of the boxes is open, there is a CO2 filter inside.\n";
				cout << endl;
			}
			else if (storageFilterTaken == 1 && storageFuseTaken == 0) {
				cout << endl;
				cout << "You are standing in the storage room.\n";
				cout << "The main corridor is behind you.\n";
				cout << "There is a ladder here leading up to the secondary reactor.\n";
				cout << "Shelves line the room, the metal boxes are free of dust and shine in the light.\n";
				cout << "One of the boxes is open, there is a fuse inside.\n";
				cout << endl;
			}
			else if (storageFilterTaken == 1 && storageFuseTaken == 1) {
				cout << endl;
				cout << "You are standing in the storage room.\n";
				cout << "The main corridor is behind you.\n";
				cout << "There is a ladder here leading up to the secondary reactor.\n";
				cout << "Shelves line the room, the metal boxes are free of dust and shine in the light.\n";
				cout << "One of the boxes is open, there is nothing inside it.\n";
				cout << endl;
			}
		}
		else if (input == "go back") {
			p1.location = 'm';
		}
		else if (input == "go up") {
			p1.location = 'z';
		}
		else if ((input == "take filter") || (input == "take co2 filter") || (input == "take CO2 filter")) {
			p1.inventory[5] = "CO2 filter";
			storageFilterTaken = 1;
			cout << endl << "Taken.\n" << endl;

		}
		else if (input == "take fuse") {
			p1.inventory[3] = "20A fuse";
			storageFuseTaken = 1;
			cout << endl << "Taken.\n" << endl;
		}
		else if (input == "read leaflet"){
			leafletReader(p1);
		}
		else if (input == "inventory") {
			inventoryChecker(p1);
		}
		else {
			idkWhatYouMean(input);
		}
	}
}

void primaryReactor(string input, player& p1) {
	cout << endl;
	cout << "You are now in the primary reactor room.\n";
	cout << endl;
	while (p1.location == 'R'){
		getline(cin, input);
		if (input == "help") {
			helper();
		}
		else if (input == "look") {
			if (primaryReactorFuseTaken == 0) {
				cout << endl;
				cout << "You are standing next to the primary reactor.\n";
				cout << "There is a ladder leading down to hydroponics.\n";
				cout << "The wall terminal reports power production and temperature nominal.\n";
				cout << "You see a small fuse on the floor.\n";
				cout << endl;
			}
			else if (primaryReactorFuseTaken == 1) {
				cout << endl;
				cout << "You are standing next to the primary reactor.\n";
				cout << "There is a ladder leading down to hydroponics.\n";
				cout << "The wall terminal reports power production and temperature nominal.\n";
				cout << endl;
			}
		}
		else if (input == "take fuse") {
			p1.inventory[4] = "50A fuse";
			primaryReactorFuseTaken = 1;
			cout << endl << "Taken.\n" << endl;
		}
		else if (input == "go down") {
			p1.location = 'h';
		}
		else if (input == "read leaflet"){
			leafletReader(p1);
		}
		else if (input == "inventory") {
			inventoryChecker(p1);
		}
		else {
			idkWhatYouMean(input);
		}
	} // end while
}

void bridge(string input, player& p1) {
	cout << endl;
	cout << "You are now in the ships bridge.\n";
	cout << endl;
	while (p1.location == 'b'){
		getline(cin, input);
		if (input == "help") {
			helper();
		}
		else if (input == "look") {
			cout << endl;
			cout << "You are standing on the ships bridge.\n";
			cout << "The galley is behind you.\n";
			cout << "There is a ladder leading up to the observation deck here.\n";
			cout << "Four crash couches line the front of the room, facing a row of computers.\n";
			cout << "There are no windows here. Large monitors show various diagnostic screens and the view outside the ship.\n";
			cout << "One of the computers has the words \"Navigation Terminal\" embossed on its plastic.\n";
			cout << endl;
		}
		else if (input == "go back") {
			p1.location = 'g';
		}
		else if (input == "go up") {
			p1.location = 'o';

		}
		else if ((input == "activate terminal") || (input == "activate navigation terminal") || (input == "navigation terminal")) {
			terminal3(p1);
		}
		else if (input == "read leaflet"){
			leafletReader(p1);
		}
		else if (input == "inventory") {
			inventoryChecker(p1);
		}
		else {
			idkWhatYouMean(input);
		}
		// else if (input == "activate terminal" || "activate navigation terminal")
	}
}

void observationDeck(string input, player& p1) {
	cout << endl;
	cout << "You are now on the observation deck.\n";
	cout << endl;
	while (p1.location == 'o'){
		getline(cin, input);
		if (input == "help") {
			helper();
		}
		else if (input == "look") {
			if (p1.inventory[1] == "") {
				cout << endl;
				cout << "You are standing on the ships observation deck.\n";
				cout << "There is a ladder here leading down to the bridge.\n";
				cout << "You see a vast star field beyond the glass. All of the stars are distant. There is nothing near to the ship.\n";
				cout << "You are far out in interstellar space and quite alone.\n";
				cout << "You see a small hand wrench in the corner.\n";
				cout << endl;
			}
			else if (p1.inventory[1] == "wrench") {
				cout << endl;
				cout << "You are standing on the ships observation deck.\n";
				cout << "There is a ladder here leading down to the bridge.\n";
				cout << "You see a vast star field beyond the glass. All of the stars are distant. There is nothing near to the ship.\n";
				cout << "You are far out in interstellar space and quite alone.\n";
				cout << endl;
			}
		}
		else if (input == "go down") {
			p1.location = 'b';
		}
		else if (input == "inventory") {
			inventoryChecker(p1);
		}
		else if (input == "read leaflet"){
			leafletReader(p1);
		}
		else if ((input == "take wrench") || (input == "take hand wrench") || (input == "take small hand wrench")) {
			p1.inventory[1] = "wrench";
			cout << endl << "Taken.\n" << endl;
		}
		else {
			idkWhatYouMean(input);
		}
	}
}

void secondaryReactor(string input, player& p1) {
	cout << endl;
	cout << "You are now in the secondary reactor room.\n";
	cout << endl;
	while (p1.location == 'z'){
		getline(cin, input);
		if (input == "help") {
			helper();
		}
		else if (input == "look" && p1.secondaryReactorFixed != 1) {
			cout << endl;
			cout << "You are standing next to the secondary reactor.\n";
			cout << "There is a ladder here leading down to the storage room.\n";
			cout << "The reactor is quiet, clearly powered off. There is a small terminal next to it.\n";
			cout << "There is a crank on the wall below a sign reading \"Coolant system restart\"\n";
			cout << endl;
		}
		else if (input == "look" && p1.secondaryReactorFixed == 1) {
			cout << endl;
			cout << "You are standing next to the secondary reactor.\n";
			cout << "There is a ladder here leading down to the storage room.\n";
			cout << "The reactor is functional now. There is a small terminal next to it.\n";
			cout << "There is a crank on the wall below a sign reading \"Coolant system restart\"\n";
			cout << endl;
		}
		else if (input == "go down") {
			p1.location = 's';
		}
		else if (input == "activate terminal") {
			terminal2(p1);
		}
		else if (input == "inventory") {
			inventoryChecker(p1);
		}
		else if (input == "read leaflet"){
			leafletReader(p1);
		}
		else if ((input == "use wrench on crank") || (input == "crank") || (input == "wrench crank") || (input == "turn crank")) {
			if (p1.inventory[1] == "wrench") {
				cout << endl << "You use the wrench to turn the crank. The cooling system begins to power up.\n" << endl;
				p1.secondaryReactorFixed = true;
			}
			else if (p1.inventory[1] != "wrench")
				cout << endl << "You try to turn the crank with your hands but aren't strong enough. Maybe with some leverage?\n" << endl;
		}
		else {
			idkWhatYouMean(input);
		}
	}
}
