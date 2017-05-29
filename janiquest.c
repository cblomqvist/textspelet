/*
	Welcome programmer!
	
	This is a simple text-based game where the goal is to find a person in as few steps as possible. The amount of steps required are a bit luck-based but also based on how well you know him.
	
	The game was made as a school-project by Hugo Blomqvist in the spring of 2017
*/


/*
	TODO
	-Replay function
	-Infinity-loop prevention for non-numerical user inputs
	-Add more variants of titles/room descriptions
	-Solve the bug which changes the name of the teachers' room to something random
	
	Bonus
	-Highscore tracking
	-Menu with help and settings
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
	int debugConstant = 0;						//Preventation of error during debug
	debug("init()...", debugConstant); 			//Debug code. logs that initalization of main has begun
	
	//Initialization of variables
	int userInput; 								//Variable for tracking the user's input
	int steps = -1; 							//Variable for tracking steps. Starts at -1 to compensate for start of the game
	Location* goalRoom;
	

	Location startRoom, cafeteria, lobby, restroom, staircase, floor2, lunchroom, wCorridor, nCorridor, eCorridor, garden, classA, classB, classC, copyroom, lab, printer, itOffice, teacher; //Struct names
	
	
	//startRoom - Special room with info
	startRoom.name = "School entrance";
	startRoom.description = "You are outside the school entrance and you urgently need to find Jani, your economics teacher,\nbefore he magically disappears.\nTime is of the essence!\n\nMake your choices by entering a number between 1 and 5.\nThe numbers corresponds to different actions which are presented to you below the description in each room\n";
	startRoom.destinations[0] = &staircase;
	startRoom.options[0] = "Press 1 to enter the staircase at school and start the game";
	startRoom.numOptions = 1;

	
	//Lobby
	lobby.name = "Lobby";
	lobby.description = "You enter the lobby. No sign of Jani. Where do you do now?";
	lobby.destinations[0] = &staircase;
	lobby.destinations[1] =	&wCorridor;
	lobby.destinations[2] = &nCorridor;
	lobby.destinations[3] = &eCorridor;
	lobby.destinations[4] = &restroom;
	lobby.options[0] = "Go to the staircase";
	lobby.options[1] = "Go to the west corrior";
	lobby.options[2] = "Go to the north corridor";
	lobby.options[3] = "Go to the east corridor";
	lobby.options[4] = "Check the restrooms";
	lobby.numOptions = 5;

	
	//Lunchroom
	lunchroom.name = "Lunchroom";
	lunchroom.description = "You check the lunchroom. He is not there";
	lunchroom.destinations[0] = &floor2;
	lunchroom.options[0] = "Go back to the 2nd floor mainroom";
	lunchroom.numOptions = 1;
	
	
	//Cafeteria
	cafeteria.name = "Cafeteria";
	cafeteria.description = "You check the cafeteria. He is not there.";
	cafeteria.destinations[0] = &floor2;
	cafeteria.options[0] = "go back to the 2nd floor mainroom";
	cafeteria.numOptions = 1;
	
	
	//Restroom
	restroom.name = "Restroom";
	restroom.description = "You check the restroom. He is not there.";
	restroom.destinations[0] = &lobby;;
	restroom.options[0] = "Go back to the lobby";
	restroom.numOptions = 1;
	
	
	//Floor 2
	floor2.name = "2nd Floor mainroom";
	floor2.description = "This is the 2nd floor mainroom. Jani is not here";
	floor2.destinations[0] = &cafeteria;
	floor2.destinations[1] = &lunchroom;
	floor2.destinations[2] = &staircase;
	floor2.options[0] = "Check the cafeteria";
	floor2.options[1] = "Check the lunchroom";
	floor2.options[2] = "Go down the staircase";
	floor2.numOptions = 3;


	//The staircase
	staircase.name = "Staircase";
	staircase.description = "You are in the staircase. From here you can go out, go up a floor or enter the 1st floor lobby.";
	staircase.destinations[0] = &garden;
	staircase.destinations[1] = &floor2;
	staircase.destinations[2] = &lobby;
	staircase.options[0] = "Go look outside";
	staircase.options[1] = "Go up to the 2nd floor";
	staircase.options[2] = "Enter the lobby";
	staircase.numOptions = 3;
	
	
	//The garden
	garden.name = "The garden";
	garden.description = "You go out to the garden. He is not here. What do you do now?";
	garden.destinations[0] = &teacher;
	garden.destinations[1] = &staircase;
	garden.destinations[2] = &wCorridor;
	garden.options[0] = "Check the teachers' room";
	garden.options[1] = "Enter the staircase";
	garden.options[2] = "Enter the west corridor";
	garden.numOptions = 3;
	
	
	//The north corridor
	nCorridor.name = "the north corridor";
	nCorridor.description = "You entered the north corridor";
	nCorridor.destinations[0] = &itOffice;
	nCorridor.destinations[1] = &printer;
	nCorridor.destinations[2] = &lab;
	nCorridor.destinations[3] = &lobby;
	nCorridor.options[0] = "Search the IT-room";
	nCorridor.options[1] = "Search the 3D-printing room";
	nCorridor.options[2] = "Search the computer-lab";
	nCorridor.options[3] = "Go back to the lobby";
	nCorridor.numOptions = 4;
	
	
	//The east corridor
	eCorridor.name = "The east corridor";
	eCorridor.description = "You entered the east corridor";
	eCorridor.destinations[0] = &classB;
	eCorridor.destinations[1] = &classC;
	eCorridor.destinations[2] = &lobby;
	eCorridor.options[0] = "Check the classroom called Bunnyostrich";
	eCorridor.options[1] = "Check the classroom called Torbjorn";
	eCorridor.options[2] = "Go back to the lobby";
	eCorridor.numOptions = 3;
	
	
	//The west corridor
	wCorridor.name = "The west corridor";
	wCorridor.description = "You have entered the west corridor.";
	wCorridor.destinations[0] = &teacher;
	wCorridor.destinations[1] = &classA;
	wCorridor.destinations[2] = &copyroom;
	wCorridor.destinations[3] = &lobby;
	wCorridor.options[0] = "Enter the teachers' room";
	wCorridor.options[1] = "Search the classroom known as dubble-classroom";
	wCorridor.options[2] = "Search the copyroom";
	wCorridor.options[3] = "Go back to the lobby";
	wCorridor.numOptions = 4;
	
	
	//teachers' room
	teacher.name = "The teachers' room";
	teacher.description = "You entered the teachers' room. There are pleanty of teachers there but Jani isn't one of them.";
	teacher.destinations[0] = &garden;
	teacher.destinations[1] = &wCorridor;
	teacher.options[0] = "Go out to the garden";
	teacher.options[1] = "Go into the west corridor";
	teacher.numOptions = 2;
	
	
	//Copyroom
	copyroom.name = "Copyroom";
	copyroom.description = "You search the copyroom. Inside you find Reynaldo and Clas taking turns in copying papers.\nThey seem busy so you leave them alone.";
	copyroom.destinations[0] = &wCorridor;
	copyroom.options[0] = "Go back out in the corridor";
	copyroom.numOptions = 1;
	
	
	//IT-office
	itOffice.name = "The IT-office";
	itOffice.description = "You try to enter, but as usual the IT-office is empty";
	itOffice.destinations[0] = &nCorridor;
	itOffice.options[0] = "Try another location";
	itOffice.numOptions = 1;
	
	//3D-printing room
	printer.name = "3D-printing room";
	printer.description = "You entered the 3D-printing room. There you find Hugo and Christian working on the printer. You dare not disturb";
	printer.destinations[0] = &nCorridor;
	printer.options[0] = "Quickly return to the north corridor";
	printer.numOptions = 1;
	
	
	//Lab
	lab.name = "The computer-lab";
	lab.description = "Inside the computer-lab there seems to be a party. You safely assume that there's no teacher in there.";
	lab.destinations[0] = &nCorridor;
	lab.options[0] = "Move along";
	lab.numOptions = 1;
	
	
	//Classroom 1
	classA.name = "The double-classroom";
	classA.description = "The double-classroom was filled to the edges with students.\nThere are no teachers inside, although this is where Jani should have been.";
	classA.destinations[0] = &wCorridor;
	classA.options[0] = "Move along";
	classA.numOptions = 1;
	
	
	//Classroom 2
	classB.name = "The classroom Bunnyostrich";
	classB.description = "You look in through the window and see a bunch of students taking a math test.";
	classB.destinations[0] = &eCorridor;
	classB.options[0] = "Silently move along";
	classB.numOptions = 1;
	
	
	//Classrom 3
	classC.name = "The classroom Torbjorn";
	classC.description = "The classroom is locked and empty";
	classC.destinations[0] = &eCorridor;
	classC.options[0] = "Try somewhere else";
	classC.numOptions = 1;
	
	
	
/*	format of locations
	
	.name = "";
	.description = "";
	.destinations[0] = &;
	.destinations[1] = &;
	.destinations[2] = &;
	.options[0] = "";
	.options[1] = "";
	.options[2] = "";
	.numOptions = 3; 

*/
	
	// Start of the game
	Location* room = &startRoom;									//Sets the first struct to be printed to startRoom
	Location* hideouts[3]; 											//Sets the maximum amount of locations Jani can be in.
	hideouts[0] = &restroom;										//Location 1
	hideouts[1] = &cafeteria;										//Location 2
	hideouts[2] = &classC;											//Location 3
	hideouts[3] = &printer;											//Location 4
	
	//Makes Jani hide in different rooms on each play-through
	goalRoom = hideouts[hideJani(4)];								//Sets the goalRoom to one of the rooms Jani is hiding in
	debug("roomInfo()...", debugConstant);
	roomInfo(*room);												//Prints startRoom
	
	//Loop for checking win condition
	while(room != goalRoom){
		
		scanf("%d", &userInput);
		
		if (userInput > 0 && userInput <= room->numOptions){
			debug("userInput-1", userInput);
			userInput--;											//Reduces userInput by 1 to make it work properly with arrays
			steps++;												//Counts steps taken to find Jani
			debug("Steps taken: ", steps);
			room = room->destinations[userInput];					//Assigns room to a new location
			roomInfo(*room);										//Changes to the new location
		} else {
			printf("Whoops! Please make your choice by entering one of the listed numbers\nTry again: ");
		}
	}
	
	//If he is found, asks the user for replay and shows score
	system("cls");
	printf("You found him at last. He was hiding in the %s\n", room->name);
	printf("It took you %d steps to find him. Can you beat it?\n\n", steps);

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
	printf("Current Room: %s\n\n", info.name);
	printf("%s\n\n", info.description);
	for (i = 0; i < info.numOptions; i++){
		printf("%d: %s\n", i+1, info.options[i]);
	}
	printf("\n\nEnter alternative: ");
}

//Function for randomizing Jani's hidingspot
int hideJani(int numberOfHideouts){
	time_t t;
	srand((unsigned) time(&t));
	int random = rand() % numberOfHideouts;
	return random;
}

//Debug function. Uncomment the lines within to enable
void debug(char* msg, int value){
	printf("DEBUG: %s: %d\n", msg, value);
	sleep(1);
}