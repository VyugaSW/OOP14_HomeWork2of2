
#include <Windows.h>
#include <iostream>
#include "QueuePriority.h"

using namespace std;

// All clients
const char ClientsName[13][25]{ "Mark","Tom","Aleksandr","Sandra","Tim","Went","Ivan",
							 "Adam","Fridrih","Immanuil","Ioggan","Ilya","Parke"};
// Their priority
const int ClientPriority[13]{ 1,5,4,2,3,6,1,4,3,1,5,4,8};


void NewClient (QueuePriority clients, TimeData clientsTimeWait) {
	if (!(rand() % 2)) {
		int randClient = rand() % 13; // Random client

		// If this client already exist in queue
		while (clients.isExist((char*)ClientsName[randClient])) {
			randClient = rand() % 13;
			if (clients.isFull()) break;
		}

		// Add client
		clients.add((char*)ClientsName[randClient], ClientPriority[randClient]);
		clientsTimeWait.add((char*)ClientsName[randClient]);
	}
}

//I made it so that the queueand client waits are added in a loop, 
//and the time is counted using a for loop with (one loop by default 5 minutes) 
//a random number of client pages.
void Process() {
	const int PagePrintingTime = 5; // One page time passes (minutes)

	srand(time(NULL));
	TimeData clientsTimeWait(13); // Data of client (time waiting and name)
	QueuePriority clients(13); // Queue with priority

	int randClient; // Random number, which determinate client
	int randCountOfPages; // Random number pages, which clients wanna print

	int timeRepeat = 15; // How much tiems repeat cycle

	// Process
	while (timeRepeat != 0) {

		timeRepeat--;
		// Determinate random client and count of pages to print
		randClient = rand() % 13;
		randCountOfPages = rand() % 5 + 1;

		// If this client already exist in queue
		while (clients.isExist((char*)ClientsName[randClient])) {
			randClient = rand() % 13;
			if (clients.isFull()) break;
		}

		// Add new clients (random number)
		for (int i = 0; i <= rand()% 3+1;i++){
			clients.add((char*)ClientsName[randClient], ClientPriority[randClient]);
			clientsTimeWait.add((char*)ClientsName[randClient]);
		}

		// 50% to appear new client
		NewClient(clients, clientsTimeWait);
		
		// Client is printing his pages
		for (int i = 0; i < randCountOfPages; i++) {
			clients.updateTime(PagePrintingTime);
		}

		// Extract client and save his information
		clientsTimeWait.update(clients.extract(), clients.getNameMaxPriority());

	}
	// Clear queue if there is any clients
	clients.clear();
	// Show clients' data
	clientsTimeWait.show();
}








int main(){
	// I sincerely do not know how it was right 
	// to complete this task, so I got out as best I could.
	Process(); // yes :)
}

