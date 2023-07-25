#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <vector>
#include <sstream>
#include <cstdio>
#include <ctime>
#include <windows.h>
#include <iomanip>
using namespace std;

//ASCII codes for letters used in program
const int a = 97;
const int g = 103;
const int ESC = 27;

//Function to change the colour of the console
void changeConsoleColor(int colorCode) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, colorCode);
}
//Displays at the start of the program
void intro() {
    changeConsoleColor(6);
    cout << R"( 
                                     _____________   
                                    |             |
                                    |     ________|       ____            ____
                                    |    |               |    |          |    |
                                    |    |           ____|    |____  ____|    |_____
                                    |    |          |              ||               |
                                    |    |          |____      ____||____      _____|
                                    |    |________       |    |          |    |
                                    |             |      |____|          |____|
                                    |_____________|
                                     _____      _____   _______________   ______________   _____________   _____
                                    |     |    |     | |               | |              | |             | |     |
                                    |     |    |     | |     _____     | |____      ____| |      _______| |     |
                                    |     |____|     | |    |     |    |      |    |      |     |_______  |     |
                                    |                | |    |     |    |      |    |      |             | |     |
                                    |                | |    |     |    |      |    |      |      _______| |     |
                                    |      ____      | |    |     |    |      |    |      |     |         |     |
                                    |     |    |     | |    |_____|    |      |    |      |     |_______  |     |_______
                                    |     |    |     | |               |      |    |      |             | |             |
                                    |_____|    |_____| |_______________|      |____|      |_____________| |_____________|
    )" << endl;
    cout << endl;
    cout << "\n\n\t\tBY: GROUP I";
    changeConsoleColor(7);
}
//Displays at the end of the program
void outro() {
    changeConsoleColor(6);
    cout << R"(
                                     ______________  ______     ______  _______________     _____
                                    |              | \     \   /     / |               |   |     |
                                    |     ____     |  \     \-/     /  |     __________|   |     |
                                    |    |    |    |   \           /   |    |              |     |  
                                    |    |____|    |    \         /    |    |__________    |     |
                                    |             /      \       /     |               |   |     |
                                    |     ____    \       |     |      |     __________|   |     |
                                    |    |    |    |      |     |      |    |              |     |
                                    |    |____|    |      |     |      |    |__________    |_____|
                                    |              |      |     |      |               |    _____ 
                                    |______________|      |_____|      |_______________|   |_____|
    )" << endl;
    changeConsoleColor(7);
}
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

//Function to get the current date (Used in addGuest function)
string getCurrentDate() {
    // Get the current time
    time_t now = time(nullptr);
    // Create a buffer to store the formatted date
    char buffer[80];
    // Format the current time as a string with the desired format
    strftime(buffer, sizeof(buffer), "%d-%m-%Y", localtime(&now));
    // Convert the buffer to a string and return it
    return string(buffer);
}

//Loading Bar animation 
void loadingBarAnimation() {
    const int totalProgress = 100; // Total progress value (e.g., 100%)
    const int barWidth = 50; // Width of the loading bar in characters

    for (int progress = 0; progress <= totalProgress; ++progress) {
        int completedWidth = barWidth * progress / totalProgress;

        cout << "\r[";
        for (int i = 0; i < barWidth; ++i) {
            if (i < completedWidth) {
                cout << "=";
            } else {
                cout << " ";
            }
        }
        cout << "] " << progress << "%";
        cout.flush();

        // Add a small delay to control the speed of the animation
        Sleep(5);
    }

    std::cout << std::endl;
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
            price = room_data[2] + "/night";
            occupant_count = room_data[3];
            status = room_data[4];
        }
        void displayRoomData() {
            string border = "+--------------+-----------------------------------+";
            Sleep(900);
            cout << left; // Set left alignment for the data
            cout << border << endl;
            cout << "| Room Id      | " << setw(34) << id << "|" << endl;
            // Set the console text color based on the room type
            if (type == "Single") {
                changeConsoleColor(8); // Gray color
            } else if (type == "Double") {
                changeConsoleColor(3); // Cyan color
            }else if (type == "Triple") {
                changeConsoleColor(13); // Light Purple color
            }else {
                changeConsoleColor(6); // Yellow color
            }
            cout << border << endl;
            cout << "| Room Type    | " << setw(34) << type << "|" << endl;
            cout << border << endl;
            // Reset the console text color to the default (white)
            changeConsoleColor(15);
            cout << "| Price        | " << setw(34) << price << "|" << endl;
            cout << border << endl;
            cout << "| Occupant No. | " << setw(34) << occupant_count << "|" << endl;
            cout << border << endl;
             // Set the console text color based on the status
            if (status == "Unavailable") {
                changeConsoleColor(12); // Red color
            } else if (status == "Available") {
                changeConsoleColor(10); // Green color
            }
            cout << border << endl;
            cout << "| Status       | " << setw(34) << status << "|" << endl;
            cout << border << endl << endl;
            // Reset the console text color to the default (white)
            changeConsoleColor(15);
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
            Sleep(900);
            cout << left; // Set left alignment for the data
            cout << "+---------------+-----------------------------------+" << endl;
            cout << "| Guest Id      | " << setw(34) << id << "|" << endl;
            changeConsoleColor(14);
            cout << "+---------------+-----------------------------------+" << endl;
            cout << "| Guest Name    | " << setw(34) << name << "|" << endl;
            cout << "+---------------+-----------------------------------+" << endl;
            changeConsoleColor(15);
            cout << "| Contact Info  | " << setw(34) << contact_info << "|" << endl;
            cout << "+---------------+-----------------------------------+" << endl;
            cout << "| Room Id       | " << setw(34) << room_id << "|" << endl;
            cout << "+---------------+-----------------------------------+" << endl;
            cout << "| Arrival Date  | " << setw(34) << arrival_date << "|" << endl;
            cout << "+---------------+-----------------------------------+" << endl << endl;
        }

        
        //Function to log the guest into the application
        bool guestLogin() {
            bool login_status = false;
            cout << "\nEnter First name: ";
            string guest_name,f_name, l_name, guest_id;
            cin >> f_name;
            cout << "\nEnter Last name: ";
            cin >> l_name;
            cout << "\nEnter ID: ";
            cin >> guest_id;
            guest_name = l_name + " " + f_name;
            vector<string> guest_database = getCSVData(GUEST_DATA);
            for(int i = 0; i < guest_database.size(); i++) {
                vector<string> guest_data = split(guest_database[i], ',');
                if (guest_data[0] == guest_id && guest_data[1] == guest_name) {
                    login_status = true;
                    break;
                }
            }
            if(!login_status) {
                changeConsoleColor(12); // Red color
                cout << "Invalid Login! Please try again\n";
            }
            else {
                changeConsoleColor(10); // Green color
                cout << "Welcome " << guest_name;
            }
            // Reset the console text color to the default (white)
            changeConsoleColor(15);
            return login_status;
        }
        bool guestLogin(string name, string ID) {
            bool login_status = false;
            vector<string> guest_database = getCSVData(GUEST_DATA);
            for(int i = 0; i < guest_database.size(); i++) {
                vector<string> guest_data = split(guest_database[i], ',');
                if (guest_data[0] == ID && guest_data[1] == name) {
                    changeConsoleColor(10);
                    cout << "Welcome " << name;
                    login_status = true;
                    changeConsoleColor(7);
                    break;
                }
            }
            if(!login_status) {
                changeConsoleColor(12); // Red color
                cout << "Invalid Login! Please try again\n";
            }
            else {
                changeConsoleColor(10); // Green color
                cout << "Welcome " << name;
            }
            // Reset the console text color to the default (white)
            changeConsoleColor(15);
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
        cin >> admin_id;
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
       loadingBarAnimation();
        for (int i = 0; i < row.size(); i++) {
            Room room(split(row[i], ','));
            room.displayRoomData();
        }
    }
    //Search for a particular room by id
    void searchForRoom() {
        bool success;
        do {
            success = true;
            string room_id;
            cout << "\nEnter Room ID: ";
            cin >> room_id;
            vector<string> row = getCSVData(ROOM_DATA);
            bool isRoomFound = false;
            cout << "\nSearching for Room " << room_id << " ...\n";
            loadingBarAnimation();
            for (int i = 0; i < row.size(); i++) {
                if (split(row[i], ',')[0] == room_id) {
                    isRoomFound = true;
                    Room room(split(row[i], ','));
                    room.displayRoomData();
                    success = true;
                    break;
                }
            }
            if(!isRoomFound) {
                cout << "\nRoom not found. Please try again\n";
                success = false;
            }
        } while(!success);
    }
    //Search for rooms with a status of "Available"
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
        bool success, error;
        string id, type, status, price, occupant_count;
        do {
            success = true;
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
            if(doesRoomExist) {
                cout << "\nERROR!!\nRoom already exists. Enter another ID\n";
                success = false; 
            }
            else {
                int choice;
                do {
                    cout << "\nSelect Room Type: \n1 - Single\n2 - Double\n3 - Triple\n4 - Quadruple\nYour Choice: ";
                    cin >> choice;
                    switch (choice) {
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
                        error = true;
                        break;
                    } 
                }  while(error);
                occupant_count = "0", status = "Available";
                string new_room_data = id + "," + type+ ","  + price+ ","  + occupant_count + "," + status;
                vector<string> room_details = getCSVData(ROOM_DATA);
                room_details.push_back(new_room_data);
                ofstream outStream(ROOM_DATA);
                //Add the new room to the database
                for (int i = 0; i < room_details.size(); i++) outStream << room_details[i] << endl;
                outStream.close();
                cout << "\nRoom successfully Added\n";
                success = true;
            }
        } while (!success);
}
//Function to get the guest's preferred room type
    void getRoomByType() {
        int choice;
        bool isValidChoice;
        string room_type;
        do {
        isValidChoice = true;
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
        cout << "\nSearching for Available Rooms...\n";
        loadingBarAnimation();
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
        bool success;
        do {
            success = true;
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
            if(!isRoomFound) {
                cout << "\nERROR!!\nRoom not found. Kindly make sure you entered the right ID\n";
                success = false;
            }
            else { //Update the room database
                ofstream outStream(ROOM_DATA);
                for(int i = 0; i < row.size(); i++) outStream << row[i] << endl;
                outStream.close();
                changeConsoleColor(10);
                cout << "\nRoom removed successfully";
                changeConsoleColor(7);
            }
        } while (!success);
    }

    //Admin Methods for Guests
    //Display all guests in the database (Guest_Data.csv)
    void showAllGuests() {
        vector<string> row = getCSVData(GUEST_DATA);
        cout << "Retrieving Guest Data...\n\n";
        for (int i = 0; i < row.size(); i++) {
            Guest guest(split(row[i], ','));
            guest.getDetails();
        }
    }
    //Search for a guest based on their Id and Name
    void searchForGuest(string name, string ID) {
        vector<string> row = getCSVData(GUEST_DATA);
        bool isGuestFound = false;
        for (int i = 0; i < row.size(); i++) {
            vector<string> data = split(row[i], ',');
            if (data[0] == ID && data[1] == name) {
                isGuestFound = true;
                loadingBarAnimation();
                Guest guest(data);
                guest.getDetails();
                break;
            }
        }
        if (!isGuestFound) {
            changeConsoleColor(12);
            cout << "\nGuest not found. Please try again\n";
            changeConsoleColor(7);
            }
    }

    void searchForGuest() {
        string name,f_name, l_name, id;
        bool success;
        do {
            success = true;
            cout << "\nEnter Guest's first name: ";
            cin >> f_name;
            cout << "Enter Guest's last name: ";
            cin>> l_name;
            name = l_name + " " + f_name;
            // fflush(stdin);
            // cin.ignore();
            cout << "Enter Guest ID: ";
            cin >> id;
            cout << "\nSearching for Guest...";
            // fflush(stdin);
            vector<string> row = getCSVData(GUEST_DATA);
            bool isGuestFound = false;
            for (int i = 0; i < row.size(); i++) {
                vector<string> data = split(row[i], ',');
                if (data[0] == id && data[1] == name) {
                    isGuestFound = true;
                    loadingBarAnimation();
                    Guest guest(data);
                    guest.getDetails();
                    success = true;
                    break;
                }
            }
            if (!isGuestFound) {
                changeConsoleColor(12);
                cout << "\nGuest not found. Please try again\n";
                changeConsoleColor(7);
                success = false;
            }
        } while (!success);
    }
    //Add a guest to the database
    void addGuest() {
        string f_name, l_name, name, id, contact_info, arrival_date, room_id, occupant_no;
        vector<string> guest_info;
        bool success;
        do {
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
            guest_info.push_back(id);
            guest_info.push_back(name);
            guest_info.push_back(contact_info);
            guest_info.push_back(room_id);
            guest_info.push_back(arrival_date);
            Guest new_guest(guest_info);
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
            if(!isRoomFound) {
                changeConsoleColor(12);
                cout << "ERROR!!\nRoom not found. Kindly make sure you entered the right ID\n";
                success = false;
                changeConsoleColor(7);
            }
            else if(isRoomFull) {
                changeConsoleColor(6);
                cout << "\nRoom is currently Full. Please try another room\n";
                success = false;
                changeConsoleColor(7);
            }
            else {
                vector<string> guest_details = getCSVData(GUEST_DATA);
                guest_details.push_back(new_guest_data);
                ofstream outStream(GUEST_DATA);
                //Add the new guest to the guest database
                for (int i = 0; i < guest_details.size(); i++) {
                    outStream << guest_details[i] << endl;
                }
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
                cout << "\nRegistering New Guest...\n";
                loadingBarAnimation();
                new_guest.getDetails();
                changeConsoleColor(10);
                cout << "\nGuest successfully Added\n";
                success = true;
                changeConsoleColor(7);
            }
        } while (!success);
    }
    //Remove a guest from the database
    void removeGuest() {
        string guest_name, f_name, l_name, guest_id;
        bool success;
        do {
            cout << "Enter Guest's First name: ";
            cin >> f_name;
            cout << "Enter Guest's Last name: ";
            cin >> l_name;
            guest_name = l_name + " " + f_name;
            cout << "Enter Guest ID: ";
            cin >> guest_id;
            vector<string> guest_data = getCSVData(GUEST_DATA);
            string roomID;
            bool isGuestFound = false;
            loadingBarAnimation();
            for(int i = 0; i < guest_data.size(); i++) {
                vector<string> data = split(guest_data[i], ',');
                if(data[0] == guest_id && data[1] == guest_name) {
                    Guest guest(data);
                    isGuestFound = true; 
                    roomID = data[3]; 
                    changeConsoleColor(10);
                    cout << "Guest Identified" << endl;
                    changeConsoleColor(7);
                    guest.getDetails();
                    break;
                }
            }
            if(!isGuestFound){
                changeConsoleColor(12);
                cout << "\nERROR!!\nGuest not found. Kindly make sure you entered the right details\n";
                success = false;
                changeConsoleColor(7);
            }
            else {
                cout << "\nPress any key to delete Guest\n" << endl;
                int pause = getch();
                loadingBarAnimation();
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
                changeConsoleColor(10);
                cout << "\nGuest removed successfully";
                changeConsoleColor(7);
            }

        } while (!success);
    }
    void removeGuest(string name, string ID) {
        vector<string> guest_data = getCSVData(GUEST_DATA);
        string roomID;
        bool isGuestFound = false;
        loadingBarAnimation();
        for(int i = 0; i < guest_data.size(); i++) {
            vector<string> data = split(guest_data[i], ',');
            if(data[0] == ID && data[1] == name) {
                Guest guest(data);
                isGuestFound = true; 
                roomID = data[3]; 
                changeConsoleColor(10);
                cout << "Guest Identified" << endl;
                changeConsoleColor(7);
                guest.getDetails();
                break;
            }
        }
        if(!isGuestFound){
            changeConsoleColor(12);
            cout << "\nERROR!!\nGuest not found. Kindly make sure you entered the right ID\n";
            changeConsoleColor(7);
        }
        else {
            cout << "\nPress any key to delete Guest\n" << endl;
            int pause = getch();
            loadingBarAnimation();
            deleteRow(guest_data, ID);
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
            changeConsoleColor(10);
            cout << "\nGuest removed successfully";
            changeConsoleColor(7);
        }
    }
};