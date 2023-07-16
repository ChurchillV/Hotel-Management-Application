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

//Function to delete a row of data from the database
void deleteRow(vector<string> &row, string searchItem) {
    for (int i = 0; i < row.size(); i++) {
        if(row[i].find(searchItem) != string::npos) {
            row.erase(row.begin() + i);
            i--;
        }
    }
}
//FILE PATH FOR ROOM DATA CSV FILE
string ROOM_DATA = "data/Room_Details.csv";
//FILE PATH FOR GUEST DATA CSV FILE
string GUEST_DATA = "data/Guest_Data.csv";

//CLASSES
//ROOM CLASS, constructor to create a Room object that the admin can usee, Display Room data
class Room {
    private:
        string id, type, status, price, occupant_count, capacity;
    public:
        Room(vector<string> room_data) {
            id = room_data[0];
            type = room_data[1];
            price = room_data[2];
            status = room_data[3];
            occupant_count = room_data[4];
            capacity = room_data[5];
        }
        void displayRoomData() {
            cout << "\n----------------------------\n"
                << "Room Id: " << id << endl
                << "Room Type: " << type << endl
                << "Room Price: " << price << endl
                << "Occupant Count: " << occupant_count << endl
                << "Capacity: " << capacity << endl
                << "Status: " << status << endl;
        }
        friend class Admin;
};

//GUEST CLASS, constructor to create a guest object the admin can use, display guest details
class Guest {
    private:
        string name, id, contact_info, residency_status, room_id;
    public:
        Guest(vector<string> guest_data) {
            id = guest_data[0];
            name = guest_data[1];
            contact_info = guest_data[2];
            residency_status = guest_data[3];
            room_id = guest_data[4];
        };
        void getDetails() {
            cout << "\n----------------------------\n"
            << "\nGuest Id: " << id
            << "\nGuest Name: " << name
            << "\nContact " << contact_info
            << "\nResidency Status: " << residency_status
            << "\nRoom Id: " << room_id << endl;
        }
        friend class Admin;
};

//ADMIN CLASS, displays all rooms and guests, searches for rooms and guests, adds and removes rooms and guests
class Admin {
    public:
    //Display all rooms in the database(Guest_Data.csv)
    void showAllRooms() {
       vector<string> row = getCSVData(ROOM_DATA);
        for (int i = 0; i < row.size(); i++) {
            Room room(split(row[i], ','));
            room.displayRoomData();
        }
    }
    //Search for a particular room by id
    void searchForRoom(string room_id) {
        vector<string> row = getCSVData(ROOM_DATA);
        bool isRoomFound = false;
        for (int i = 0; i < row.size(); i++) {
            if (split(row[i], ',')[0] == room_id) {
                isRoomFound = true;
                Room room(split(row[i], ','));
                room.displayRoomData();
            }
        }
        if(!isRoomFound) cout << "\nRoom not found. Please try again\n";
    }
    //Search for rooms with a status of "Unoccupied"or not yet at full capacity
    void searchAvailableRooms() {
        vector<string> row = getCSVData(ROOM_DATA);
        bool areRoomsFound = false;
        for (int i = 0; i < row.size(); i++) {
            vector<string> data = split(row[i], ',');
            //If the room is unoccupied or hasn't reached it's limit
            if ((data[4] == "Unoccupied") || stoi(data[3]) < stoi(data[5])) {
                areRoomsFound = true;
                Room room(data);
                room.displayRoomData();
            }
        }
        if(!areRoomsFound) cout << "\nNo available Rooms. Check again later\n";
    }
    //Add a room to the database
    void addRoom(Room new_room) {
        vector <string> row = getCSVData(ROOM_DATA);
        string new_room_data = new_room.id + "," + new_room.type+ ","  + new_room.price+ ","  + new_room.occupant_count + "," + new_room.status + "," + new_room.capacity;
        bool doesRoomExist = false;
        //Check if the room already exists
        for (int i = 0; i < row.size(); i++) {
            vector<string> data = split(row[i], ',');
            if(data[0] == new_room.id) doesRoomExist = true;
        }
        if(doesRoomExist) cout << "\nERROR!!\nRoom already exists. Enter another ID\n";
        else {
            vector<string> room_details = getCSVData(ROOM_DATA);
            room_details.push_back(new_room_data);
            ofstream outStream(ROOM_DATA);
            //Add the new room to the database
            for (int i = 0; i < room_details.size(); i++) outStream << room_details[i] << endl;
            outStream.close();
            cout << "\nRoom successfully Added\n";
        }
    }
    //Remove a room from the database
    void removeRoom(string room_id) {
        vector<string> row = getCSVData(ROOM_DATA);
        bool isRoomFound = false;
        for(int i = 0; i < row.size(); i++) {
            vector<string> data = split(row[i], ',');
            if(data[0] == room_id) {
                isRoomFound = true;
                deleteRow(row, room_id);
            }
        }
        if(!isRoomFound) cout << "\nERROR!!\nRoom not found. Kindly make sure you entered the right ID\n";
        else {
            ofstream outStream(ROOM_DATA);
            for(int i = 0; i < row.size(); i++) outStream << row[i] << endl;
            outStream.close();
            cout << "\nRoom removed successfully";
        }
    }
    //Display all guests in the database (Guest_Data.csv)
    void showAllGuests() {
        vector<string> row = getCSVData(GUEST_DATA);
        for (int i = 0; i < row.size(); i++) {
            Guest guest(split(row[i], ','));
            guest.getDetails();
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
                Guest guest(data);
                guest.getDetails();
            }
        }
        if (!isGuestFound) cout << "\nGuest not found. Please try again\n";
    }
    //Add a guest to the database
    void addGuest(Guest new_guest) {
        vector <string> row = getCSVData(ROOM_DATA);
        string new_guest_data = new_guest.id + "," + new_guest.name+ ","  + new_guest.contact_info+ ","  + new_guest.residency_status + ",";
        bool isRoomFound = false, isRoomFull = false;
        string roomID;
        for (int i = 0; i < row.size(); i++) {
            vector<string> data = split(row[i], ',');
            if(data[0] == new_guest.room_id) isRoomFound = true; roomID = data[0];
                //Check if the room has reached its capacity
                if(data[3] >= data[5]) isRoomFull = true;
        }
        if(!isRoomFound) cout << "ERROR!!\nRoom not found. Kindly make sure you entered the right ID\n";
        else if(isRoomFull) cout << "Room is currently full. Please check another room";
        else {
            vector<string> guest_details = getCSVData(GUEST_DATA);
            guest_details.push_back(new_guest_data + roomID);
            ofstream outStream(GUEST_DATA);
            //Add the new guest to the guest database
            for (int i = 0; i < guest_details.size(); i++) outStream << guest_details[i] << endl;
            outStream.close();
            cout << "\nGuest successfully Added\n";
        }
    }
    //Remove a guest from the database
    void removeGuest(string guest_id) {
        vector<string> row = getCSVData(GUEST_DATA);
        bool isGuestFound = false;
        for(int i = 0; i < row.size(); i++) {
            vector<string> data = split(row[i], ',');
            if(data[0] == guest_id) isGuestFound = true; deleteRow(row, guest_id);
        }
        if(!isGuestFound) cout << "\nERROR!!\nGuest not found. Kindly make sure you entered the right ID\n";
        else {
            ofstream outStream(GUEST_DATA);
            for(int i = 0; i < row.size(); i++) outStream << row[i] << endl;
            outStream.close();
            cout << "\nGuest removed successfully";
        }
    }
};