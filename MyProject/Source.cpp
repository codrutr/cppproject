#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

class Util {
public:
	static void copyString(char* dest, const char* source, size_t size) {
		strncpy(dest, source, size);
		dest[size - 1] = '\0';
	}

	static char* copyDynamicString(const char* source) {
		char* copy = new char[strlen(source) + 1];
		copyString(copy, source, strlen(source) + 1);
		return copy;
	}
};

class Event {
private:
	char name[100];
	char date[11];
	char time[6];

public:
	Event() {
		Util::copyString(name, "", sizeof(name));
		Util::copyString(date, "", sizeof(date));
		Util::copyString(time, "", sizeof(time));
	}
	Event(const char* name, const char* date, const char* time) {
		Util::copyString(this->name, name, sizeof(this->name));
		Util::copyString(this->date, date, sizeof(this->date));
		Util::copyString(this->time, time, sizeof(this->time));
	}

	const char* getName() const { return name; }
	const char* getDate() const { return date; }
	const char* getTime() const { return time; }

	void setName(const char* name) { Util::copyString(this->name, name, sizeof(this->name)); }
	void setDate(const char* date) { Util::copyString(this->date, date, sizeof(this->date)); }
	void setTime(const char* time) { Util::copyString(this->time, time, sizeof(this->time)); }
	
	void displayEvent() const {
		cout << "Event: " << name << endl;
		cout << "Date: " << date << endl;
		cout << "Time: " << time << endl;
	}
};

class Location {
private:
	char name[100];
	int maxSeats;
	int numRows;
	int numZones;
	int seatsPerRow[10];

public:
	Location() {
		Util::copyString(name, "", sizeof(name));
		maxSeats = numRows = numZones = 0;
		for (int i = 0; i < sizeof(seatsPerRow) / sizeof(seatsPerRow[0]); i++) {
			seatsPerRow[i] = 0;
		}
	}

	Location(const char* name, int maxSeats, int numRows, int numZones, const int* seatsPerRow) {
		Util::copyString(this->name, name, sizeof(this->name));
		this->maxSeats = maxSeats;
		this->numRows = numRows;
		this->numZones = numZones;
		for (int i = 0; i < this->numRows; i++) {
			this->seatsPerRow[i] = seatsPerRow[i];
		}
	}

	const char* getName() const { return name; }
	int getMaxSeats() const { return maxSeats; }
	int getNumRows() const { return numRows; }
	int getNumZones() const { return numZones; }
	const int* getSeatsPerRow() const { return seatsPerRow; }

	void setName(const char* name) { Util::copyString(this->name, name, sizeof(this->name)); }
	void setMaxSeats(int maxSeats) { this->maxSeats = maxSeats; }
	void setNumRows(int numRows) { this->numRows = numRows; }
	void setNumZones(int numZones) { this->numZones = numZones; }
	void setSeatsPerRow(const int* seatsPerRow) {
		for (int i = 0; i < this->numRows; i++) {
			this->seatsPerRow[i] = seatsPerRow[i];
		}
	}
	void displayLocation() const {
		cout << "Location: " << name << endl;
		cout << "Maximum seats: " << maxSeats << endl;
		cout << "Number of rows: " << numRows << endl;
		cout << "Number of zones: " << numZones << endl;
		cout << "Seats per row: ";
		for (int i = 0; i < numRows; i++) {
			cout << seatsPerRow[i] << " ";
		}
		cout << endl;
	}
};



class Ticket {
private:
	char ticketType[20];
	int uniqueID;
public:
	Ticket() : uniqueID(generateUniqueID()) {
		Util::copyString(ticketType, "", sizeof(ticketType));
	}

	Ticket(const char* ticketType) : uniqueID(generateUniqueID()) {
		Util::copyString(this->ticketType, ticketType, sizeof(this->ticketType));
	}

	const char* getTicketTyoe() const { return ticketType; }
	int getUniqueID() const { return uniqueID; }
	void setTicketType(const char* ticketType) { Util::copyString(this->ticketType, ticketType, sizeof(this->ticketType)); }

	void displayTicket() const {
		cout << "Ticket type: " << ticketType << endl;
		cout << "Unique id: " << uniqueID << endl;
	}

private:
	int generateUniqueID() const {
		return rand();
	}
};

int main() {

	Event footballEvent("Football Match", "01.12.2023", "18:00");
	
	int seatsPerRow[] = { 25, 30, 25 };
	Location stadium("Stadium", 5000, 3, 3, seatsPerRow);

	footballEvent.displayEvent();
	stadium.displayLocation();

	return 0;
}