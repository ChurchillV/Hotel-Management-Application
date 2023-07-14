#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <vector>
using namespace std;

//FUNCTION DEFINITIONS
//Function to separate the data obtained from each row
vector<string> split(string text, char delimiter){
    //Vector to store the individual data
    vector<string> tokens;
    string token;
    int i = 0;
    while (i < text.length()) {
        if(text[i] == delimiter) {
            //Add the token to the tokens vector when a delimiter is found
            tokens.push_back(token);
            token = ""; //Reset the token to an empty string
        }
        else token += text[i];
        i++;
    }
    //When we reach the end of a row, add the last value to the vector
    if(token.length() > 0) tokens.push_back(token);
    return tokens;
};

//Function to read data from csv files and return each row in a vector form
vector<string> getCSVData(string csv_filename) {
    ifstream file; //File object for reading from files
    string data; 
    vector<string> row; //Data from each row is stored in this vector
    file.open(csv_filename);
    while(getline(file, data)) {
        row.push_back(data);
    }
    file.close();
    return row;
}
//CSV FILE PATHS
string ROOM_DATA = "data/Room_Details.csv";
string GUEST_DATA = "data/Guest_Data.csv";

//CLASSES
//ROOM CLASS
class Room {
    private:
        string id, type, status, price, occupant_count, capacity;
    public:
        Room(string room_id, string room_type, string room_price , string room_occupant_count, string room_status, string room_capacity) {
            id = room_id;
            type = room_type;
            status = room_status;
            price = room_price;
            occupant_count = room_occupant_count;
            capacity = room_capacity;
        }
        void displayRoomData() {
            cout << "\n----------------------------\n"
                << "Room Id: " << id << endl
                << "Room Type: " << type << endl
                << "Room Price: " << price << endl
                << "Occupant Count: " << occupant_count << endl
                << "Capacity: " << capacity << endl;
        }
};

//GUEST CLASS
class Guest {
    private:
        string name, id, contact_info, residency_status, room_id;
    public:
        Guest(string guest_id, string guest_name, string contact, string residency, string room) {
            id = guest_id;
            name = guest_name;
            contact_info = contact;
            residency_status = residency;
            room_id = room;
        };
        void getDetails() {
            cout << "\n----------------------------\n"
            << "\nGuest Id: " << id
            << "\nGuest Name: " << name
            << "\nContact " << contact_info
            << "\nResidency Status: " << residency_status
            << "\nRoom Id: " << room_id << endl;
        }
};

//ADMIN CLASS
class Admin {
    public:
    //Display all rooms in the database(Guest_Data.csv)
    void showAllRooms() {
       vector<string> row = getCSVData(ROOM_DATA);
        for (int i = 0; i < row.size(); i++) {
            vector<string> data = split(row[i], ',');
            Room test_room(data[0], data[1], data[2], data[3], data[4], data[5]);
            test_room.displayRoomData();
        }
    }
    //Search for a particular room by id
    void searchForRoom(string room_id) {
        vector<string> row = getCSVData(ROOM_DATA);
        bool isRoomFound = false;
        for (int i = 0; i < row.size(); i++) {
            vector<string> data = split(row[i], ',');
            if (data[0] == room_id) {
                isRoomFound = true;
                Room test_room(data[0], data[1], data[2], data[3], data[4], data[5]);
                test_room.displayRoomData();
            }
        }
        if(!isRoomFound) cout << "\nRoom not found. Please try again\n";
    }
    //Search for rooms with a status of "Unoccupied"
    void searchAvailableRooms() {
        vector<string> row = getCSVData(ROOM_DATA);
        bool areRoomsFound = false;
        for (int i = 0; i < row.size(); i++) {
            vector<string> data = split(row[i], ',');
            if (data[4] == "Unoccupied") {
                areRoomsFound = true;
                Room test_room(data[0], data[1], data[2], data[3], data[4], data[5]);
                test_room.displayRoomData();
            }
        }
    }
    //Add a room to the database
    void addRoom() {

    }
    //Remove a room from the database
    void removeRoom(string room_id) {

    }
    //Display all guests in the database (Guest_Data.csv)
    void showAllGuests() {
        vector<string> row = getCSVData(GUEST_DATA);
        for (int i = 0; i < row.size(); i++) {
            vector<string> data = split(row[i], ',');
            Guest test_guest(data[0], data[1], data[2], data[3], data[4]);
            test_guest.getDetails();
        }
    }
    //Search for a guest based on their Id
    void searchForGuest(string guest_id) {
        vector<string> row = getCSVData(GUEST_DATA);
        bool isGuestFound = false;
        for (int i = 0; i < row.size(); i++) {
            vector<string> data = split(row[i], ',');
            if (data[0] == guest_id) {
                isGuestFound = true;
                Guest test_guest(data[0], data[1], data[2], data[3], data[4]);
                test_guest.getDetails();
            }
        }
        if (!isGuestFound) cout << "\nGuest not found. Please try again\n";
    }
    //Add a guest to the database
    void addGuest(string room_id, string guest_id) {
        
    }
    //Remove a guest from the database
    void removeGuest(string room_id, string guest_id) {

    }
};