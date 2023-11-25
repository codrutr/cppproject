#include <iostream>
#include <string>
#include <string.h>

using namespace std;

class Util {
public:
	static void copyString(char* dest, const char* source, size_t size) {
		strncpy(dest, source, size);
		dest[size - 1] = '\0';
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

private:
	int generateUniqueID() const {
		return rand();
	}
};

int main() {
	Event footballEvent("Football Match", "01.12.2023", "18:00");
}