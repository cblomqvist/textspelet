/*
	Welcome programmer!
	
	This is a simple text-based game where the goal is to find a person in as few steps as possible. The amount of steps required are a bit luck-based but also based on how well you know him.
	
	The game was made as a school-project by Hugo Blomqvist in the spring of 2017
*/


/*
	TODO
	-Replay function
	-Infinity-loop prevention for non-numerical user inputs
	-Add more rooms
	-Add fancier menus and titles
	-Add more comments
	
	Bonus
	-Highscore tracking
*/

//Start of actual code
//Included libraries
#include <stdio.h>
#include <string.h> 
#include <windows.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

//Definition of struct for all rooms
typedef struct Locations {
	char* name;
	char* description;
	char* options[10];
	struct Locations* destinations[10];
	int numOptions;
} Location;

//Declaration of functions
void roomInfo(Location info);
int hideJani(int);
void debug(char*, int);

//Main function
int main(void){
	int debugConstant = 0;				//Preventation of error during debug
	debug("init()...", debugConstant); 	//Debug code. logs that initalization of main has begun
	
	//Initialization of variables
	int userInput; 				//Variable for tracking the user's input
	int steps = -1; 			//Variable for tracking steps. Starts at -1 to compensate for start of the game
	Location* goalRoom;
	

	Location startRoom, office, cafeteria, lobby, restroom; //Struct names
	
	//startRoom - Special room with info
	startRoom.name = "Outside";
	startRoom.description = "You are outside the school building. It is of utmost importance that you find Jani.";
	startRoom.destinations[0] = &lobby;
	startRoom.options[0] = "Enter school";
	startRoom.numOptions = 1;

	//Lobby
	lobby.name = "Lobby";
	lobby.description = "You went to the lobby. What do you do now?";
	lobby.destinations[0] = &cafeteria;
	lobby.destinations[1] =	&office;
	lobby.destinations[2] = &restroom;
	lobby.options[0] = "Go to the cafeteria";
	lobby.options[1] = "Go to the office";
	lobby.options[2] = "Go to the restroom";
	lobby.numOptions = 3;
	
	//Office
	office.name = "Office";
	office.description = "You make your way to the door outside the office. What do you do now?";
    office.destinations[0] = &cafeteria;
	office.destinations[1] = &lobby;
	office.destinations[2] = &restroom;
	office.options[0] = "Go to the cafeteria";
	office.options[1] = "Go to the lobby";
	office.options[2] = "Go to the restroom";
	office.numOptions = 3;
	
	//Cafeteria
	cafeteria.name = "Cafeteria";
	cafeteria.description = "You arrived at the cafeteria. What do you do now?";
	cafeteria.destinations[0] = &office;
	cafeteria.destinations[1] =	&lobby;
	cafeteria.destinations[2] = &restroom;
	cafeteria.options[0] = "Go to the office";
	cafeteria.options[1] = "Go to the lobby";
	cafeteria.options[2] = "Go to the restroom";
	cafeteria.numOptions = 3;
	
	//Restroom
	restroom.name = "Restroom";
	restroom.description = "You arrive at the restroom. What do you do now?";
	restroom.destinations[0] = &cafeteria;
	restroom.destinations[1] = &lobby;
	restroom.destinations[2] = &office;
	restroom.options[0] = "Go to the cafeteria";
	restroom.options[1] = "Go to the lobby";
	restroom.options[2] = "Go to the office";
	restroom.numOptions = 3;

	
	
	
	// Start of the game
	Location* room = &startRoom;			//Sets the first struct to be printed to startRoom
	Location* hideouts[2]; 					//Sets the maximum amout of locations Jani can be in.
	hideouts[0] = &restroom;				//Location A
	hideouts[1] = &cafeteria;				//Location B
	
	//Makes Jani hide in different rooms on each play-through
	goalRoom = hideouts[hideJani(2)];		//Sets the goalRoom to one of the rooms Jani is hiding in
	debug("roomInfo()...", debugConstant);
	roomInfo(*room);						//Prints startRoom
	
	//Loop for checking win condition
	while(room != goalRoom){
		
		scanf("%d", &userInput);
		
		if (userInput > 0 && userInput <= room->numOptions){
			debug("userInput-1", userInput);
			userInput--;											//Reduces userInput by 1 to make it work properly with arrays
			steps++;												//Counts steps taken to find Jani
			room = room->destinations[userInput];					//Assigns room to a new location
			roomInfo(*room);										//Changes to the new location
		} else {
			printf("Whoops! Please make your choice by entering one of the listed numbers\nTry again: ");
		}
	}
	
	//If he is found, asks the user for replay and shows score
	system("cls");
	printf("You found him at last. He was hiding in the %s\n", room->name);
	printf("It took you %d steps to find him. Can you beat it?\n", steps);

	/*	
	printf("Play again? Y/N\n\n:");		//Currently unfinished code for replay
	scanf("%c", replay);
		if (replay = "y" || "Y"){
			main();
		} else {
			exit(0);
		}
*/

	return 0;
} 


//Function for printing out the structs
void roomInfo(Location info){
	int i = 0;
	system("cls");
	printf("Current Room: %s\n", info.name);
	printf("%s\n", info.description);
	for (i = 0; i < info.numOptions; i++){
		printf("%d: %s\n", i+1, info.options[i]);
	}
	printf("Enter alternative: ");
}

//Function for randomizing Jani's hidingspot
int hideJani(int numberOfHideouts){
	time_t t;
	srand((unsigned) time(&t));
	int random = rand() % numberOfHideouts;
	return random;
}

//Debug function. Uncomment the line within to enable
void debug(char* msg, int value){
//	printf("DEBUG: %s: %d\n", msg, value);
}