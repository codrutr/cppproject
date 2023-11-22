#include <iostream>
#include <string>

using namespace std;

class Location {
private:
	string name;
	int maxSeats;
	int numRows;
	int numZones;
	int* seatsPerRow;
};

class Event {
private:
	string name;
};

class Ticket {
private:
	string ticketType;
	int uniqueID;
};

int main() {
	return 0;
}