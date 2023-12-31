#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <vector>
#include <string>   

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
    vector<int> seatsPerRow;

public:
    Location() {
        Util::copyString(name, "", sizeof(name));
        maxSeats = numRows = numZones = 0;
    }

    Location(const char* name, int maxSeats, int numRows, int numZones, const vector<int>& seatsPerRow) {
        Util::copyString(this->name, name, sizeof(this->name));
        this->maxSeats = maxSeats;
        this->numRows = numRows;
        this->numZones = numZones;
        this->seatsPerRow = seatsPerRow;
    }

    const char* getName() const { return name; }
    int getMaxSeats() const { return maxSeats; }
    int getNumRows() const { return numRows; }
    int getNumZones() const { return numZones; }
    const vector<int>& getSeatsPerRow() const { return seatsPerRow; }

    void setName(const char* name) { Util::copyString(this->name, name, sizeof(this->name)); }
    void setMaxSeats(int maxSeats) { this->maxSeats = maxSeats; }
    void setNumRows(int numRows) { this->numRows = numRows; }
    void setNumZones(int numZones) { this->numZones = numZones; }
    void setSeatsPerRow(const vector<int>& seatsPerRow) {
        this->seatsPerRow = seatsPerRow;
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
    int nextUniqueID;

public:
    Ticket() : uniqueID(generateUniqueID()) {
        Util::copyString(ticketType, "", sizeof(ticketType));
    }

    Ticket(const char* ticketType) : uniqueID(generateUniqueID()) {
        Util::copyString(this->ticketType, ticketType, sizeof(this->ticketType));
    }

    const char* getTicketType() const { return this->ticketType; }
    int getUniqueID() const { return this->uniqueID; }
    void setTicketType(const char* ticketType) { Util::copyString(this->ticketType, ticketType, sizeof(this->ticketType)); }

    void displayTicket() const {
        cout << "Ticket type: " << ticketType << endl;
        cout << "Unique id: " << uniqueID << endl;
    }


    int generateUniqueID() {
        return nextUniqueID++;
    }
};

class TicketManager {
public:
    void generateTickets(const Location& location, const Event& event, const char* ticketType, int numTickets) {
        for (int i = 0; i < numTickets; ++i) {
            Ticket ticket(ticketType);
            tickets.push_back(ticket);
        }

        cout << numTickets << " tickets of type " << ticketType << " generated successfully.\n";
    }

    void validateTicket() {
        int uniqueID;
        cout << "Enter the unique ID of the ticket to validate: ";
        cin >> uniqueID;

        for (const auto& ticket : tickets) {
            if (ticket.getUniqueID() == uniqueID) {
                cout << "Ticket is valid.\n";
                return;
            }
        }

        cout << "Invalid ticket ID.\n";
    }

    void saveTicketsToFile(const char* fileName) const {
        ofstream outFile(fileName, ios::binary | ios::out);
        if (!outFile.is_open()) {
            cerr << "Error opening file for writing.\n";
            return;
        }

        for (const auto& ticket : tickets) {
            outFile.write(reinterpret_cast<const char*>(&ticket), sizeof(Ticket));
        }

        cout << "Tickets saved to file: " << fileName << "\n";
        outFile.close();
    }

    void loadTicketsFromFile(const char* fileName) {
        ifstream inFile(fileName, ios::binary | ios::in);
        if (!inFile.is_open()) {
            cerr << "Error opening file for reading.\n";
            return;
        }

        Ticket ticket;
        while (inFile.read(reinterpret_cast<char*>(&ticket), sizeof(Ticket))) {
            tickets.push_back(ticket);
        }

        cout << "Tickets loaded from file: " << fileName << "\n";
        inFile.close();
    }

private:
    vector<Ticket> tickets;
};

int main() {
    srand(static_cast<unsigned int>(time(0)));

    Event footballEvent("Football Match", "01.12.2023", "18:00");

    vector<int> seatsPerRow = { 25, 30, 25 };
    Location stadium("Stadium", 5000, 3, 3, seatsPerRow);

    TicketManager ticketManager;

    int choice;
    do {
        cout << "Options:\n";
        cout << "1. Generate Tickets\n";
        cout << "2. Validate Ticket\n";
        cout << "3. Save Tickets to File\n";
        cout << "4. Load Tickets from File\n";
        cout << "5. Display Event and Location\n";
        cout << "6. Exit\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            int numTickets;
            cout << "Enter the number of tickets to generate: ";
            cin >> numTickets;

            char ticketType[20];
            cout << "Enter the ticket type: ";
            cin >> ticketType;

            ticketManager.generateTickets(stadium, footballEvent, ticketType, numTickets);
            break;
        }
        case 2: {
            ticketManager.validateTicket();
            break;
        }
        case 3: {
            char fileName[100];
            cout << "Enter the file name to save tickets: ";
            cin >> fileName;

            ticketManager.saveTicketsToFile(fileName);
            break;
        }
        case 4: {
            char fileName[100];
            cout << "Enter the file name to load tickets: ";
            cin >> fileName;

            ticketManager.loadTicketsFromFile(fileName);
            break;
        }
        case 5: {
            footballEvent.displayEvent();
            stadium.displayLocation();
            break;
        }
        case 6:
            cout << "Exiting program.\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 6);

    return 0;
}
