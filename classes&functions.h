#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <vector>
#include <sstream>
#include <cstdio>
#include <ctime>
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

// //Function to perform operations on strings, returns a string
// string update(string& value, int amount) {
//     //Convert string to integer
//     stringstream ss(value);
//     int num;
//     ss >> num;
//     //Change value
//     num += amount;
//     //Convert back to string
//     stringstream  holder;
//     holder << num;
//     value = holder.str();
//     return value;
// }

//Function to get the current date (Used in addGuest function)
string getCurrentDate() {
    // Get the current time
    time_t now = time(nullptr);
    // Create a buffer to store the formatted date
    char buffer[80];
    // Format the current time as a string with the desired format
    strftime(buffer, sizeof(buffer), "%d-%m-%Y", localtime(&now));
    // Convert the buffer to a string and return it
    return std::string(buffer);
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
        string id, type, price, status,occupant_count;
    public:
        Room(vector<string> room_data) {
            id = room_data[0];
            type = room_data[1];
            price = room_data[2];
            occupant_count = room_data[3];
            status = room_data[4];
        }
        void displayRoomData() {
            cout << "\n----------------------------\n"
                << "Room Id: " << id << endl
                << "Room Type: " << type << endl
                << "Room Price: " << price << endl
                << "Occupant Count: " << occupant_count << endl
                << "Status: " << status << endl;
        }
        friend class Admin;
};

//GUEST CLASS, constructor to create a guest object the admin can use, display guest details
class Guest {
    private:
        string name, id, contact_info,room_id, arrival_date;
    public:
        Guest(vector<string> guest_data) {
            id = guest_data[0];
            name = guest_data[1];
            contact_info = guest_data[2];
            room_id = guest_data[3];
            arrival_date = guest_data[4];
        };
        Guest() {};
        void getDetails() {
            cout << "\n----------------------------\n"
            << "\nGuest Id: " << id
            << "\nGuest Name: " << name
            << "\nContact " << contact_info
            << "\nRoom Id: " << room_id
            << "\nArrival Date: " << arrival_date << endl;
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
        // else cout << "Welcome " << admin_id;
        return login_status;
    }

    //Admin Methods for rooms
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
            if (data[4] == "Available") {
                areRoomsFound = true;
                Room room(data);
                room.displayRoomData();
            }
        }
        if(!areRoomsFound) cout << "\nNo available Rooms. Check again later\n";
    }
    //Add a room to the database
    void addRoom() {
        string id, type, status, price, occupant_count;
        cout << "\nEnter Room ID: ";
        cin >> id;
        bool doesRoomExist = false;
        //Check if the room already exists
        vector <string> row = getCSVData(ROOM_DATA);
        for (int i = 0; i < row.size(); i++) {
            vector<string> data = split(row[i], ',');
            if(data[0] == id) {
            doesRoomExist = true;
            break;
            }
        }
        if(doesRoomExist) {cout << "\nERROR!!\nRoom already exists. Enter another ID\n";}
        else {
            int choice;
            cout << "\nSelect Room Type: \n1 - Single\n2 - Double\n3 - Triple\n4 - Quadruple\nYour Choice: ";
            cin >> choice;
            switch (choice) {
            {
            case 1:
                type = "Single";
                price = "1000";
                break;
            case 2:
                type = "Double";
                price = "2000";
                break;
            case 3:
                type = "Triple";
                price = "3000";
                break;
            case 4:
                type = "Quadruple";
                price = "4000";
                break;
            default:
                cout << "Invalid Option";
                break;
            }
        }
            occupant_count = "0", status = "Available";
            string new_room_data = id + "," + type+ ","  + price+ ","  + occupant_count + "," + status;
            vector<string> room_details = getCSVData(ROOM_DATA);
            room_details.push_back(new_room_data);
            ofstream outStream(ROOM_DATA);
            //Add the new room to the database
            for (int i = 0; i < room_details.size(); i++) outStream << room_details[i] << endl;
            outStream.close();
            cout << "\nRoom successfully Added\n";
    }
}
//Function to get the guest's preferred room type
    void getRoomByType() {
        int choice;
        bool isValidChoice = true;
        string room_type;
        do {
        cout << "\nSelect preferred Room Type: \n1 - Single\n2 - Double\n3 - Triple\n4 - Quadruple\nYour Choice: ";
        cin >> choice;
        switch (choice) {
            {
            case 1:
                room_type = "Single";
                break;
            case 2:
                room_type = "Double";
                break;
            case 3:
                room_type = "Triple";
                break;
            case 4:
                room_type = "Quadruple";
                break;
            default:
                cout << "Invalid Option";
                isValidChoice = false;
                break;
            }
        }
        vector<string> row = getCSVData(ROOM_DATA);
        bool areRoomsFound = false;
        for (int i = 0; i < row.size(); i++) {
            vector<string> data = split(row[i], ',');
            //If the room is unoccupied or hasn't reached it's limit
            if (data[1] == room_type && data[4] == "Available") {
                areRoomsFound = true;
                Room room(data);
                room.displayRoomData();
            }
        }
        if(!areRoomsFound) {
            cout << "\nNo available rooms of this type. Check again later\n";
            isValidChoice = false;
        }
        } while(!isValidChoice);
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

    //Admin Methods for Guests
    //Display all guests in the database (Guest_Data.csv)
    void showAllGuests() {
        vector<string> row = getCSVData(GUEST_DATA);
        for (int i = 0; i < row.size(); i++) {
            Guest guest(split(row[i], ','));
            guest.getDetails();
        }
    }
    //Search for a guest based on their Id and Name
    void searchForGuest() {
        string name, id;
        cout << "Enter Guest name: ";
        getline(cin, name);
        fflush(stdin);
        cin.ignore();
        cout << "Enter Guest ID: ";
        cin >> id;
        fflush(stdin);
        vector<string> row = getCSVData(GUEST_DATA);
        bool isGuestFound = false;
        for (int i = 0; i < row.size(); i++) {
            vector<string> data = split(row[i], ',');
            if (data[0] == id && data[1] == name) {
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
        string f_name, l_name, name, id, contact_info, arrival_date, room_id, occupant_no;
        int rm_id;
        cout << "\nFirst name: ";
        cin >> f_name;
        fflush(stdin);
        cout << "\nLast name: ";
        cin >> l_name;
        fflush(stdin);
        name = l_name + " " + f_name;
        cout << "Enter Guest contact info: ";
        cin >> contact_info;
        fflush(stdin);
        cout << "Enter Guest ID: ";
        fflush(stdin);
        cin >> id;
        // cin.ignore();
        getRoomByType();
        cout << "Enter preferred Room ID: ";
        cin >> room_id;
        fflush(stdin);
        cout << "Enter occupant number: ";
        cin >> occupant_no;
        arrival_date = getCurrentDate();
        vector <string> room_data = getCSVData(ROOM_DATA);
        string new_guest_data = id + "," + name + ","  + contact_info + "," + room_id + "," + arrival_date;
        bool isRoomFound = false ,isRoomFull = false;
        for (int i = 0; i < room_data.size(); i++) {
            vector<string> data = split(room_data[i], ',');
            if(data[0] == room_id) {
                isRoomFound = true; 
                if (data[4] == "Unavailable") {
                    isRoomFull = true;
                }
                break;
            }
        }
        if(!isRoomFound) cout << "ERROR!!\nRoom not found. Kindly make sure you entered the right ID\n";
        else if(isRoomFull) cout << "\nRoom is currently Full. Please try again later\n";
        else {
            vector<string> guest_details = getCSVData(GUEST_DATA);
            guest_details.push_back(new_guest_data);
            ofstream outStream(GUEST_DATA);
            //Add the new guest to the guest database
            for (int i = 0; i < guest_details.size(); i++) outStream << guest_details[i] << endl;
            outStream.close();
            //Update Room database
            room_data = getCSVData(ROOM_DATA);
            string updatedRoomInfo;
            for(int i = 0; i < room_data.size(); i++) {
                vector<string> data = split(room_data[i], ',');
                if(data[0] == room_id) {
                    updatedRoomInfo = data[0] + "," + data[1] + "," + data[2] + "," + occupant_no + ",Unavailable";
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
    void removeGuest() {
        string guest_name, guest_id;
        cout << "Enter Guest Name: ";
        cin >> guest_name;
        cout << "Enter Guest ID: ";
        cin >> guest_id;
        vector<string> guest_data = getCSVData(GUEST_DATA);
        string roomID;
        bool isGuestFound = false;
        for(int i = 0; i < guest_data.size(); i++) {
            vector<string> data = split(guest_data[i], ',');
            if(data[0] == guest_id && data[1] == guest_name) {
                isGuestFound = true; 
                roomID = data[3]; 
                break;
            }
        }
        if(!isGuestFound) cout << "\nERROR!!\nGuest not found. Kindly make sure you entered the right ID\n";
        else {
            deleteRow(guest_data, guest_id);
            string updatedRoomInfo;
            ofstream guest_data_update(GUEST_DATA);
            for(int i = 0; i < guest_data.size(); i++) {guest_data_update << guest_data[i] << endl;}
            vector<string> room_data = getCSVData(ROOM_DATA);
            for(int i = 0; i < room_data.size(); i++) {
                vector<string> data = split(room_data[i], ',');
                if(data[0] == roomID) {
                    updatedRoomInfo = data[0] + "," + data[1] + "," + data[2] + "," + "0,Available";
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