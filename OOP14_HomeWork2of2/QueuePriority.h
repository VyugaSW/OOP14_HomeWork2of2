
#include <iostream>

using namespace std;

// Queue with Priority
class QueuePriority {
	char** Wait; 
	int* Pri;
	int MaxQueueLenght; 
	int QueueLenght; 
	int* minutes; // How time (in minutes) all clients are waiting in queue 
public:
	// Constructor
	QueuePriority(int m);  
	// Destructor (Throws an exceptional error)
	//~QueuePriority(); 
	// Add new client
	void add(char* c, int p); 
	// Extract client (return his waiting time)
	int extract(); 
	// Clear queue
	void clear(); 
	// Check if queue is empty
	bool isEmpty(); 
	// Check if queue is full
	bool isFull(); 
	// Check if client with name "char* c" is existing
	bool isExist(char* c);
	// Show queue
	void show(); 
	// Update waiting time for all clients in queue
	void updateTime(int m);
	// Return name with max priority
	char* getNameMaxPriority();
};


char* QueuePriority::getNameMaxPriority() {
	int max_pri = Pri[0];
	int pos_max_pri = 0;
	for (int i = 1; i < QueueLenght; i++) {
		if (Pri[i] < max_pri) {
			max_pri = Pri[i];
			pos_max_pri = i;
		}
	}
	return Wait[pos_max_pri];
}

void QueuePriority::updateTime(int m) {
	for (int i = 0; i < QueueLenght; i++) {
		minutes[i] += m;
	}
}

bool QueuePriority::isExist(char* c) {
	for (int i = 0; i < QueueLenght; i++) {
		if (strcmp(Wait[i],c) == 0)
			return 1;
	}
	return 0;
}

void QueuePriority::show() {
	for (int i = 0; i < QueueLenght; i++) {
		cout << Wait[i] << " - " << Pri[i] << endl;
	}
	cout << endl;
}

/*
QueuePriority::~QueuePriority() {
	delete[] Wait;
	delete[] Pri;
}
*/

QueuePriority::QueuePriority(int m) {
	MaxQueueLenght = m;
	Wait = new char*[MaxQueueLenght];
	Pri = new int[MaxQueueLenght];
	minutes = new int[MaxQueueLenght];
	for (int i = 0; i < MaxQueueLenght; i++) {
		Wait[i] = new char[25];
		minutes[i] = 0;
	}
}

bool QueuePriority::isEmpty() {
	return QueueLenght == 0;
}

bool QueuePriority::isFull() {
	return QueueLenght == MaxQueueLenght;
}

void QueuePriority::add(char *c, int p) {
	if (!isFull()) {
		strcpy_s(Wait[QueueLenght], 26, c);
		Pri[QueueLenght] = p;
		QueueLenght++;
	}
}

int QueuePriority::extract() {
	if (!isEmpty()) {
		int max_pri = Pri[0];
		int pos_max_pri = 0;
		for (int i = 1; i < QueueLenght; i++) {
			if (Pri[i] < max_pri) {
				max_pri = Pri[i];
				pos_max_pri = i;
			}
		}

		for (int i = pos_max_pri; i < QueueLenght - 1; i++) {
			Wait[i] = Wait[i + 1];
			Pri[i] = Pri[i + 1];
		}

		int bufMinutes = minutes[pos_max_pri];
		minutes[pos_max_pri] = 0;
		QueueLenght--;
		return bufMinutes;
	}
	return -1;
}

void QueuePriority::clear() {
	QueueLenght = 0;
}


// Class which keep data of clients
class TimeData {
	char** names;
	int* minutes;
	int size;
	int lenght;
public:
	TimeData(int s);
	// check if have already this name
	bool isExist(char* c);
	// add new name
	void add(char* c);
	// update minutes of waiting by name
	void update(int m, char* c);
	// show all data
	void show();
};

TimeData::TimeData(int s) {
	size = s;
	names = new char* [size];
	minutes = new int[size];
	for (int i = 0; i < size; i++) {
		names[i] = new char[25];
	}
}

bool TimeData::isExist(char* c) {
	for (int i = 0; i <= lenght; i++) {
		if (strcmp(names[i],c) == 0)
			return 1;
	}
	return 0;
}

void TimeData::add(char* c) {
	if (lenght < size && !isExist(c)) {
		strcpy_s(names[lenght],strlen(c)+1, c);
		minutes[lenght] = 0;
		cout << names[lenght] << endl;
		lenght++;
	}
}

void TimeData::update(int m, char* c) {
	for (int i = 0; i < lenght; i++) {
		if (strcmp(names[i],c) == 0)
			minutes[i] += m;
	}
}

void TimeData::show() {
	for (int i = 0; i < lenght; i++) {
		cout << "Name: " << names[i] << endl;
		cout << "Time spend(minutes): " << minutes[i] << endl << endl;
	}
}