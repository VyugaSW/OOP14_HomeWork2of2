
#include <iostream>

using namespace std;

// Queue with Priority
class QueuePriority {
	char** Wait; 
	int* Priority;
	int MaxQueueLenght; 
	int QueueLenght; 
	int* Minutes; // How time (in minutes) all clients are waiting in queue 
public:
	// Constructor
	QueuePriority(int m);  

	// Destructor (Throws an exceptional error, 
	// because it can be empty,but we keep work with it)
 
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
	int max_pri = Priority[0];
	int pos_max_pri = 0;
	for (int i = 1; i < QueueLenght; i++) {
		if (Priority[i] < max_pri) {
			max_pri = Priority[i];
			pos_max_pri = i;
		}
	}
	return Wait[pos_max_pri];
}

void QueuePriority::updateTime(int m) {
	for (int i = 0; i < QueueLenght; i++) {
		Minutes[i] += m;
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
		cout << Wait[i] << " - " << Priority[i] << endl;
	}
	cout << endl;
}

QueuePriority::QueuePriority(int m) {
	MaxQueueLenght = m;
	Wait = new char*[MaxQueueLenght];
	Priority = new int[MaxQueueLenght];
	Minutes = new int[MaxQueueLenght];
	for (int i = 0; i < MaxQueueLenght; i++) {
		Wait[i] = new char[25];
		Minutes[i] = 0;
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
		Priority[QueueLenght] = p;
		QueueLenght++;
	}
}

int QueuePriority::extract() {
	if (!isEmpty()) {
		int max_pri = Priority[0];
		int pos_max_pri = 0;
		for (int i = 1; i < QueueLenght; i++) {
			if (Priority[i] < max_pri) {
				max_pri = Priority[i];
				pos_max_pri = i;
			}
		}

		for (int i = pos_max_pri; i < QueueLenght - 1; i++) {
			Wait[i] = Wait[i + 1];
			Priority[i] = Priority[i + 1];
			Minutes[i] = Minutes[i + 1];
		}

		int bufMinutes = Minutes[QueueLenght - 1];
		Minutes[QueueLenght - 1] = 0;
		QueueLenght--;
		return bufMinutes;
	}
	return -1;
}

void QueuePriority::clear() {
	QueueLenght = 0;
	delete[] Minutes;
	delete[] Priority;
	delete[] Wait;
}
