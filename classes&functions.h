#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <vector>
#include <sstream>
using namespace std;

//FUNCTION DEFINITIONS
//Function to separate the data obtained from each row
vector<string> split(string& text, char delimiter){
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
        else token += text[i];  //If no delimiter is found, add character to the token
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

//Function to perform operations on strings, returns a string
string update(string& value, int amount) {
    //Convert string to integer
    stringstream ss(value);
    int num;
    ss >> num;
    //Change value
    num += amount;
    //Convert back to string
    stringstream  holder;
    holder << num;
    value = holder.str();
    return value;
}

//FILE PATH FOR ROOM DATA CSV FILE
string ROOM_DATA = "data/Room_Details.csv";
//FILE PATH FOR GUEST DATA CSV FILE
string GUEST_DATA = "data/Guest_Data.csv";
//FILE PATH FOR ADMIN DATA CSV FILE
string ADMIN_DATA = "data/Admin_data.csv";

//CLASSES
//ROOM CLASS, constructor to create a Room object that the admin can use, Display Room data
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
        Guest() {
            id = "guest_data[0]";
            name = "guest_data[1]";
            contact_info = "guest_data[2]";
            residency_status = "guest_data[3]";
            room_id = "guest_data[4]";
        };
        void getDetails() {
            cout << "\n----------------------------\n"
            << "\nGuest Id: " << id
            << "\nGuest Name: " << name
            << "\nContact " << contact_info
            << "\nResidency Status: " << residency_status
            << "\nRoom Id: " << room_id << endl;
        }
        //Function to log the guest into the application
        bool guestLogin() {
            bool login_status = false;
            cout << "\nEnter name: ";
            string guest_name, guest_id;
            getline(cin, guest_name);
            cout << "\nEnter ID: ";
            cin >> guest_id;
            vector<string> guest_database = getCSVData(GUEST_DATA);
            for(int i = 0; i < guest_database.size(); i++) {
                vector<string> guest_data = split(guest_database[i], ',');
                if (guest_data[0] == guest_id && guest_data[1] == guest_name) {
                    login_status = true;
                    break;
                }
            }
            if(!login_status) cout << "Invalid Login! Please try again\n";
            else cout << "Welcome " << guest_name;
            return login_status;
        }
        friend class Admin;
};

//ADMIN CLASS, displays all rooms and guests, searches for rooms and guests, adds and removes rooms and guests
class Admin {
    private:
        string name, password;
    public:
    Admin() {}
    bool adminLogin() {
        bool login_status = false;
        cout << "\nEnter Admin ID: ";
        string admin_id, admin_password;
        getline(cin, admin_id);
        cout << "\nEnter password: ";
        cin >> admin_password;
        vector<string> admin_database = getCSVData(ADMIN_DATA);
        for(int i = 0; i < admin_database.size(); i++) {
            vector<string> admin_data = split(admin_database[i], ',');
            if (admin_data[0] == admin_id && admin_data[1] == admin_password) {
                login_status = true;
                break;
            }
        }
        if(!login_status) cout << "Invalid Login! Please try again\n";
        else cout << "Welcome " << admin_id;
        return login_status;
    }
    //Display all rooms in the database(Guest_Data.csv)
    void showAllRooms() {
       vector<string> row = getCSVData(ROOM_DATA);
       cout << "\nDisplaying all Rooms...\n";
        for (int i = 0; i < row.size(); i++) {
            Room room(split(row[i], ','));
            room.displayRoomData();
        }
    }
    //Search for a particular room by id
    void searchForRoom() {
        string room_id;
        cout << "\nEnter Room ID: ";
        cin >> room_id;
        vector<string> row = getCSVData(ROOM_DATA);
        bool isRoomFound = false;
        for (int i = 0; i < row.size(); i++) {
            if (split(row[i], ',')[0] == room_id) {
                isRoomFound = true;
                Room room(split(row[i], ','));
                room.displayRoomData();
                break;
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
    void addRoom() {
        string id, type, status, price, occupant_count, capacity;
        cout << "\nEnter Room ID: ";
        cin >> id;
        cout << "\nSelect Room Type: \n1 - 1 in 1\n2 - 2 in 1\n3 - 3 in 1\n4 - 4 in 1";
        int choice = getch();
        switch (choice)
        {
        case 1:
            type = "1 in 1";
            capacity = "1";
            price = "6000";
            break;
        case 2:
            type = "2 in 1";
            capacity = "2";
            price = "4500";
            break;
        case 3:
            type = "3 in 1";
            capacity = "3";
            price = "3000";
            break;
        case 4:
            type = "4 in 1";
            capacity = "4";
            price = "2000";
            break;
        default:
            break;
        }
        occupant_count = "0";
        vector <string> row = getCSVData(ROOM_DATA);
        string new_room_data = id + "," + type+ ","  + price+ ","  + occupant_count + "," + status + "," + capacity;
        bool doesRoomExist = false;
        //Check if the room already exists
        for (int i = 0; i < row.size(); i++) {
            vector<string> data = split(row[i], ',');
            if(data[0] == id) doesRoomExist = true;
            break;
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
    void removeRoom() {
        string room_id;
        cout << "\nEnter room ID: ";
        cin >> room_id;
        vector<string> row = getCSVData(ROOM_DATA);
        bool isRoomFound = false;
        for(int i = 0; i < row.size(); i++) {
            vector<string> data = split(row[i], ',');
            if(data[0] == room_id) {
                isRoomFound = true;
                deleteRow(row, room_id);
                break;
            }
        }
        if(!isRoomFound) cout << "\nERROR!!\nRoom not found. Kindly make sure you entered the right ID\n";
        else { //Update the room database
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
                break;
            }
        }
        if (!isGuestFound) cout << "\nGuest not found. Please try again\n";
    }
    //Add a guest to the database
    void addGuest() {
        string name, id, contact_info, residency_status, room_id;
        cout << "\nEnter Guest Name: ";
        cin >> name;
        cout << "Enter Guest contact info: ";
        cin >> contact_info;
        cout << "Enter Guest ID: ";
        cin >> id;
        cout << "Enter Room ID: ";
        cin >> room_id;
        residency_status = "Resident";
        vector <string> room_data = getCSVData(ROOM_DATA);
        string new_guest_data = id + "," + name + ","  + contact_info + ","  + residency_status + "," + room_id;
        bool isRoomFound = false, isRoomFull = false;
        for (int i = 0; i < room_data.size(); i++) {
            vector<string> data = split(room_data[i], ',');
            if(data[0] == room_id) {
                isRoomFound = true; 
                room_id = data[0];
                //Check if the room has reached its capacity
                if(stoi(data[3]) == stoi(data[5])) {isRoomFull = true;}
                break;
            }
        }
        if(!isRoomFound) cout << "ERROR!!\nRoom not found. Kindly make sure you entered the right ID\n";
        else if(isRoomFull) cout << "\nRoom is currently full. Please check another room";
        else {
            vector<string> guest_details = getCSVData(GUEST_DATA);
            guest_details.push_back(new_guest_data);
            ofstream outStream(GUEST_DATA);
            //Add the new guest to the guest database
            for (int i = 0; i < guest_details.size(); i++) outStream << guest_details[i] << endl;
            outStream.close();
            //Update Room database
            room_data = getCSVData(ROOM_DATA);
            string updatedRoomInfo, updated_occupant_count, updated_status;
            for(int i = 0; i < room_data.size(); i++) {
                vector<string> data = split(room_data[i], ',');
                if(data[0] == room_id) {
                    updated_occupant_count = update(data[3], 1);
                    updatedRoomInfo = data[0] + "," + data[1] + "," + data[2] + "," + updated_occupant_count + ",";
                    updated_status = "Occupied";
                    updatedRoomInfo += updated_status + "," + data[5];
                    deleteRow(room_data,room_id);
                    room_data.push_back(updatedRoomInfo);
                    break;
                }
            }
            //Update Room database
            ofstream room_file(ROOM_DATA);
            for(int i = 0; i < room_data.size(); i++) room_file << room_data[i] << endl;
            room_file.close();
            cout << "\nGuest successfully Added\n";
        }
    }
    //Remove a guest from the database
    void removeGuest(string guest_id) {
        vector<string> guest_data = getCSVData(GUEST_DATA);
        string roomID;
        bool isGuestFound = false;
        for(int i = 0; i < guest_data.size(); i++) {
            vector<string> data = split(guest_data[i], ',');
            if(data[0] == guest_id) {
                isGuestFound = true; 
                roomID = data[4]; 
                break;
            }
        }
        if(!isGuestFound) cout << "\nERROR!!\nGuest not found. Kindly make sure you entered the right ID\n";
        else {
            deleteRow(guest_data, guest_id);
            string updatedRoomInfo, updated_occupant_count, updated_status;
            ofstream guest_data_update(GUEST_DATA);
            for(int i = 0; i < guest_data.size(); i++) {guest_data_update << guest_data[i] << endl;}
            vector<string> room_data = getCSVData(ROOM_DATA);
            for(int i = 0; i < room_data.size(); i++) {
                vector<string> data = split(room_data[i], ',');
                if(data[0] == roomID) {
                    updated_occupant_count = update(data[3], -1);
                    updatedRoomInfo = data[0] + "," + data[1] + "," + data[2] + "," + updated_occupant_count + ",";
                    updated_status = (updated_occupant_count == "0") ? "Unoccupied" : "Occupied";
                    updatedRoomInfo += updated_status + "," + data[5];
                    deleteRow(room_data,roomID);
                    room_data.push_back(updatedRoomInfo);
                    break;
                }
            }
            //Update Room database
            ofstream room_file(ROOM_DATA);
            for(int i = 0; i < room_data.size(); i++) {room_file << room_data[i] << endl;}
            room_file.close();
            cout << "\nGuest removed successfully";
        }
    }
};