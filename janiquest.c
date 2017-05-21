#include <stdio.h>
#include <string.h> 
#include <windows.h>
#include <unistd.h>

typedef struct Locations {
	char* name;
	char* description;
	char* options[10];
	struct Locations* destinations[10];
	int numOptions;
} Location;


Location locations[17];

//Declaration of functions
void roomInfo(Location info);

int main(void){
	int userInput;
	Location* goalRoom;
	
	printf("init()...");

	Location startRoom, office, cafeteria, lobby, restroom;
	
	//startRoom
	startRoom.name = "Outside";
	startRoom.description = "You are outside the school building. It is of utmost importance that you find Jani.";
	startRoom.destinations[0] = &lobby;
	startRoom.options[0] = "Enter school";
	startRoom.numOptions = 1;

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
	Location* room = &startRoom;
	goalRoom = &restroom;
	printf("roomInfo()...");
	roomInfo(*room);
	
	while(room != goalRoom){
		scanf("%d", &userInput);
		userInput--;
		printf("userInput: %d\n", userInput);
		room = room->destinations[userInput];
		roomInfo(*room);
	}
	
} 

void roomInfo(Location info){
	int i = 0;
	// system("cls");
	printf("Current Room: %s\n", info.name);
	printf("%s\n", info.description);
	for (i = 0; i < info.numOptions; i++){
		printf("%d: %s\n", i+1, info.options[i]);
	}
	printf("Enter alternative: ");
}