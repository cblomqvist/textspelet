#include <stdio.h>
#include <string.h> 
#include <windows.h>
#include <unistd.h>

typedef struct Locations {
	char* name;
	char* description;
	char* options[3];
	struct Locations* destinations[3];
} Location;


Location locations[16];

Location init();
void roomInfo(Location info);

int main(void){
	printf("init()...");
	Location a = init();
	printf("roomInfo()...");
	roomInfo(a);
}

Location init(){
	Location office, cafeteria, lobby, restroom;

	//Office
	office.name = "Office";
	office.description = "You make your way to the door outside the office. What do you do now?";
    // office.destinations[0] = &cafeteria;
	// office.destinations[1] = &lobby;
	// office.destinations[2] = &restroom;
	office.options[0] = "Go to the cafeteria";
	office.options[1] = "Go to the lobby";
	office.options[2] = "Go to the restroom";
	
/*
	//Cafeteria
	cafeteria.name = "Cafeteria";
	strcpy(cafeteria.description, "You make your way to the cafeteria. What do you do now?");
	cafeteria.destinations[0] = &office;
	cafeteria.destinations[1] =	&lobby;
	cafeteria.destinations[2] = &restroom;
	

	//Lobby
	cafeteria.name = "Lobby";
	strcpy(cafeteria.description, "You make your way to the lobby. What do you do now?");
	lobby.destinations[0] = &office;
	lobby.destinations[1] =	&cafeteria;
	lobby.destinations[2] = &restroom;
	
	//Restroom
	cafeteria.name = "Restroom";
	strcpy(cafeteria.description, "You make your way to the restroom. What do you do now?");
	restroom.destinations[0] = &office;
	restroom.destinations[1] = &cafeteria;
	restroom.destinations[2] = &lobby;
*/

	return office;
} 

void roomInfo(Location info){
	int i = 0;
	system("cls");
	printf("Current currentRoomNr: %s\n", info.name);
	printf("%s\n", info.description);
	for (i = 0; i < 3; i++){
		printf("%d: %s\n", i+1, info.options[i]);
	}
	printf("Enter alternative: ");
}