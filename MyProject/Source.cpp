#include <iostream>
#include <string>
#include <string.h>

using namespace std;

class Util {

};

class Event {
private:
	char name[100];
	char date[11];
	char time[6];

public:
};

class Location {
private:
	char name[100];
	int maxSeats;
	int numRows;
	int numZones;
	int seatsPerRow[10];

public:
};



class Ticket {
private:
	string ticketType;
	int uniqueID;
public:
};

int main() {
	//Event footballEvent("Football Match", "01.12.2023", "18:00");
}