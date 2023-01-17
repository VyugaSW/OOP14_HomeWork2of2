#include <iostream>

using namespace std;

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
		if (strcmp(names[i], c) == 0)
			return 1;
	}
	return 0;
}

void TimeData::add(char* c) {
	if (lenght < size && !isExist(c)) {
		strcpy_s(names[lenght], strlen(c) + 1, c);
		minutes[lenght] = 0;
		cout << names[lenght] << endl;
		lenght++;
	}
}

void TimeData::update(int m, char* c) {
	for (int i = 0; i < lenght; i++) {
		if (strcmp(names[i], c) == 0)
			minutes[i] += m;
	}
}

void TimeData::show() {
	for (int i = 0; i < lenght; i++) {
		cout << "Name: " << names[i] << endl;
		cout << "Time spend(minutes): " << minutes[i] << endl << endl;
	}
}