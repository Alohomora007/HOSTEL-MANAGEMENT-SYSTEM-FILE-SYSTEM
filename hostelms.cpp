#include<bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Define data structures
struct Resident {
    string name;
    string usn; // University Serial Number
    int age;
    // Add more details as needed
};

struct Room {
    int number;
    bool occupied;
    Resident* resident;

    // Initialize room data in the constructor
    Room(int number) : number(number), occupied(false), resident(nullptr) {}
};

// Function prototypes
void addResident(vector<Resident>& residents, vector<Room>& rooms);
void addRoom(vector<Room>& rooms);
void deallocateRoom(vector<Room>& rooms);
void displayRoomStatus(const vector<Room>& rooms);

// Functions to read and write data to files
bool loadResidentsFromFile(vector<Resident>& residents, const string& filename);
bool saveResidentsToFile(const vector<Resident>& residents, const string& filename);
bool loadRoomsFromFile(vector<Room>& rooms, const string& filename);
bool saveRoomsToFile(const vector<Room>& rooms, const string& filename);

int main() {
    // File names for residents and rooms data
    const string residentsFilename = "residents.data";
    const string roomsFilename = "rooms.data";

    // Load data from files
    vector<Resident> residents;
    vector<Room> rooms;
    if (!loadResidentsFromFile(residents, residentsFilename) || !loadRoomsFromFile(rooms, roomsFilename)) {
        cout << "Error loading data from files." << endl;
    }

    int choice;
    do {
        // Main menu
        cout << "Hostel Management System" << endl;
        cout << "1. Add Resident" << endl;
        cout << "2. Add Room" << endl;
        cout << "3. Deallocate Room" << endl;
        cout << "4. Display Room Status" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addResident(residents, rooms);
                break;
            case 2:
                addRoom(rooms);
                break;
            case 3:
                deallocateRoom(rooms);
                break;
            case 4:
                displayRoomStatus(rooms);
                break;
            case 0:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 0);

    // Save data to files before exiting
    if (!saveResidentsToFile(residents, residentsFilename) || !saveRoomsToFile(rooms, roomsFilename)) {
        cout << "Error saving data to files." << endl;
    }

    return 0;
}

// Function to add a new resident
void addResident(vector<Resident>& residents, vector<Room>& rooms) {
    Resident newResident;
    cout << "Enter resident name: ";
    cin >> newResident.name;
    cout << "Enter resident USN: ";
    cin >> newResident.usn;
    cout << "Enter resident age: ";
    cin >> newResident.age;
    // Add more details as needed
    residents.push_back(newResident);

    // Allocate rooms based on some logic
    // For example, you can implement alphabetical allocation here
}

// Function to add a new room
void addRoom(vector<Room>& rooms) {
    int roomNumber;
    cout << "Enter room number: ";
    cin >> roomNumber;
    rooms.push_back(Room(roomNumber));
}

// Function to deallocate a room
void deallocateRoom(vector<Room>& rooms) {
    int roomNumber;
    cout << "Enter the room number to deallocate: ";
    cin >> roomNumber;

    // Find the room by its number
    for (Room& room : rooms) {
        if (room.number == roomNumber) {
            if (room.occupied) {
                // Free the room
                room.occupied = false;
                room.resident = nullptr;
                cout << "Room " << roomNumber << " deallocated successfully." << endl;
                return;
            } else {
                cout << "Room " << roomNumber << " is already vacant." << endl;
                return;
            }
        }
    }

    cout << "Room " << roomNumber << " not found." << endl;
}

// Function to display the status of each room (filled or vacant)
void displayRoomStatus(const vector<Room>& rooms) {
    cout << "Room Status:" << endl;
    for (const Room& room : rooms) {
        cout << "Room " << room.number << ": ";
        if (room.occupied) {
            cout << "Filled" << endl;
        } else {
            cout << "Vacant" << endl;
        }
    }
}

// Function to read residents from a file
bool loadResidentsFromFile(vector<Resident>& residents, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening " << filename << " for reading." << endl;
        return false;
    }

    string name, usn;
    int age;
    while (file >> name >> usn >> age) {
        residents.push_back({name, usn, age});
    }

    file.close();
    return true;
}

// Function to save residents to a file
bool saveResidentsToFile(const vector<Resident>& residents, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening " << filename << " for writing." << endl;
        return false;
    }

    for (const Resident& resident : residents) {
        file << resident.name << " " << resident.usn << " " << resident.age << endl;
    }

    file.close();
    return true;
}

// Function to read rooms from a file (similar to loadResidentsFromFile)
bool loadRoomsFromFile(vector<Room>& rooms, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening " << filename << " for reading." << endl;
        return false;
    }

    int number;
    bool occupied;
    while (file >> number >> occupied) {
        rooms.push_back({number, occupied, nullptr});
    }

    file.close();
    return true;
}

// Function to save rooms to a file (similar to saveResidentsToFile)
bool saveRoomsToFile(const vector<Room>& rooms, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening " << filename << " for writing." << endl;
        return false;
    }

    for (const Room& room : rooms) {
        file << room.number << " " << room.occupied << endl;
    }

    file.close();
    return true;
}
