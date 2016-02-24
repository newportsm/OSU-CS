// CS340 - Program 2
// Sarah Newport
// 01/08/2016
// Adventure Game


#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

char* filepaths[7];
char* selectedNames[7];
int connections[7][7] = {0};                    
char* roomtypenames[3] = {"START_ROOM", "MID_ROOM", "END_ROOM"};
char* names[10] = {"Living Room", "Bedroom", "Bathroom", "Kitchen", "Garage", "Family Room", "Dining Room", "Backyard", "Hallway", "Basement"};

void SelectRooms(int array[]);              
void RoomCreation();                        
void Connections();
void RoomTypes();
void AdventureGame();

int main() {                              //main adventure game function
	int i, j;

	srand(time(NULL));                    //needed for random variables
    RoomCreation();
    Connections();
    RoomTypes();

	AdventureGame();

	return 0;
}


void RoomCreation() {                               //function to create rooms for game

	FILE* roomFiles[10];
	enum roomtype {START_ROOM, MID_ROOM, END_ROOM}; //different room types
	
	int selectedRooms[7] = {-1};                    // array to hold 7 rooms to be used

	SelectRooms(selectedRooms);                     //call to SelectRooms function to pick random rooms
	int n;
	for(n = 0; n < 7; n++){
		selectedRooms[n];
	}

	int processId;                                  //creation of process IDs for room files
	processId = getpid();
	char buffer [10];
	sprintf(buffer, "%d", processId);
	char dir[40];                                 
	strcpy(dir, "./newports.rooms.");	            // newports.rooms.(processID) as assignment required
	strcat(dir, buffer);
	mkdir(dir, 0777);                               //creation of directory to hold files

	int first = rand() % 10;                        //random selection for first and last rooms
	int last = 0;
 
	int i;                                          //array to hold filepaths
	for(i =0; i < 7; i++) {
		filepaths[i] = (char*) malloc(50);
		selectedNames[i] = (char*) malloc(20);
	}

	for(i =0; i < 7; i++) {
		strcpy(filepaths[i], dir);
		strcat(filepaths[i], "/");
		strcat(filepaths[i], names[selectedRooms[i]]);
		strcpy(selectedNames[i], names[selectedRooms[i]]);
		strcat(filepaths[i], ".txt");
		filepaths[i];
	}

	FILE* temp;

	for(i =0; i < 7; i++) {                          //writing of the room files
		int firstTaken = 0;
		int lastTaken = 0;
		temp = fopen(filepaths[i], "w");
		fprintf(temp,"ROOM NAME: %s\n", names[selectedRooms[i]]);
		fclose(temp);
	}
}

void SelectRooms(int array[]) {                     //function used to select the 7 rooms used in the game

	int i=0;
	int j;
	int randNum;

	while(i<7){
		randNum = rand() % 10;                      //random number generator 
		for(j = 0; j < i; j++) {
			if(array[j] == randNum) {
				break;
			}
		}
		if(i == j) {
			array[i++] = randNum;
		}
	}
}

void Connections() {                             //function used to create room connections
	int i;                                       //create matrix to link rooms together
	int j;
	int k;
	FILE* temp;

	for(i = 0; i < 7; i++) {
		connections[i][i] = 1;
	}
    
	for(i = 0; i < 7; i++) {
		for(j = 0; j < 7; j++) {
			connections[i][j];
		}
	}

	for(i = 0; i < 7; i++) {                      //rooms require a connection to 3 to 6 rooms
		int random;
		random = (rand() % 4) + 3;

		int curConn = 0;
		for(k = 0; k < 7; k++)  {
			curConn += connections[i][k];
		}

		while(curConn <= random) {                // fill in the matrix
			int randRoom;
			randRoom = rand() % 7;

			while(randRoom == i) {
				randRoom = rand() % 7;
			}
            
			connections[i][randRoom] = 1;
			connections[randRoom][i] = 1;
			curConn++;
		}	
	}

	for(i =0; i < 7; i++) {                            //apphend the connections to the files
		int counter = 1;
		temp = fopen(filepaths[i], "a");
		for(j = 0; j < 7; j++) {
			if(connections[i][j] == 1 && (i != j)) {
				fprintf(temp,"CONNECTION %d: %s\n", counter, selectedNames[j]);
				counter++;
			}
		}
		fclose(temp);
	}

}

void RoomTypes() {                                      //function use to apphend room types to files
	int i;
	FILE* temp;
	for(i = 0; i < 7; i++) {
		temp = fopen(filepaths[i], "a");
		if(i == 0) {
			fprintf(temp, "ROOM TYPE: %s\n", roomtypenames[0]);
		}
		else if(i == 6) {
			fprintf(temp, "ROOM TYPE: %s\n", roomtypenames[2]);
		}
		else {
			fprintf(temp, "ROOM TYPE: %s\n", roomtypenames[1]);
		}
		
	}
}

void AdventureGame() {                              //function of actual game decisions and play
	
	int i, j;
	int roomPath[50] = {-1};
	bool End = false;                           //variable to return false when end room is found
	int numSteps = 0;                                //variable used to calculate number of steps a player makes
	int curRoom = 0;
    
	while(!End) {                               //loop to run until end room is selected
		
		bool validSelection = false;        
		while(!validSelection) {

			printf("CURRENT LOCATION: %s\n", selectedNames[curRoom]);        //shows current location
			printf("POSSIBLE CONNECTIONS: ");                                //shows possible rooms to pick
			for(i = 0; i < 7; i++) {
				if(connections[curRoom][i] == 1 && (i != curRoom)) {
					printf("%s, ", selectedNames[i]);
				}
			}
			printf("\n");
			
			char userSelection[25];                          //variable to hold user selection
			printf("WHERE TO? >");                           //ask user what room they would like to go to
			fgets(userSelection, 25, stdin);                 //read in user selection
			strtok(userSelection, "\n");

			for(i = 0; i < 7; i ++) {                       //check to ensure that room is valid
				if(strcmp(userSelection, selectedNames[i]) == 0 && connections[curRoom][i] == 1) {
					validSelection = true;              
					curRoom = i;
					roomPath[numSteps] = curRoom;
					numSteps++;
					if(i == 6) {
						End = true;
					}
				}
			}
			if(!validSelection) {                        //error message for wrong input
				printf("HUH? I DON'T UNDERSTAND THAT ROOM. TRY AGAIN\n\n");
			}
			else {
				printf("\n\n\n");                            //line break, then repeat loop
			}
		}
	}
    
	if(End) {                                                                 //if selected room is end room
		printf("YOU HAVE FOUND THE END ROOM. CONGRATULATIONS!\n");
		printf("YOU TOOK %d STEPS. YOUR PATH TO VICTORY WAS:\n", numSteps);   //print out number of steps it took player
		for(i = 0; i < numSteps; i++) {
			printf("%s\n", selectedNames[roomPath[i]]);
		}
	}
}