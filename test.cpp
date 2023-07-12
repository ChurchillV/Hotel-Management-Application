#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <vector>
using namespace std;

vector<string> split(string text, char delimiter);
string ROOM_DATA = "data/Room_Details.csv";
string GUEST_DATA = "data/Guest_Data.csv";
const int a = 97;
const int z = 122;
const int ESC = 27;

int main() {
    ifstream file;
    string data;
    vector<string> row;
    cout << "HOTEL MANAGEMENT APPLICATION";
    bool exit_program = false; // This will end the programme
    while(!exit_program) {
        bool back_to_menu = false; //This will take the user back to the main menu
        cout << "\n\na - Display all room data\n"
        << "z - Display all guest data\n"
        << "Esc - Exit program\n"
        << "Option: ";
        fflush(stdin);
        int option = getch();
        while(!back_to_menu) {
            switch (option) {
            case a:
                file.open(ROOM_DATA);
                while(getline(file, data)) {
                    row.push_back(data);
                }
                for (int i = 0; i < row.size(); i++) {
                    vector<string> data = split(row[i], ',');
                    cout << "\n--------------\n"
                        << "Room " << i+1 << endl
                        << "Room Id: " << data[0] << endl
                        << "Room Type: " << data[1] << endl
                        << "Room Price: " << data[2] << endl
                        << "Status: " << data[4] << endl
                        << "Occupant Count: " << data[3];
                }
                back_to_menu = true;
                file.close();
                break;
            
            case z:
                file.open(GUEST_DATA);
                while(getline(file,data)) {
                    row.push_back(data);
                }
                for (int i = 0; i < row.size(); i++) {
                    vector<string> data = split(row[i], ',');
                    cout << "\n--------------\n"
                        << "Guest Id: " << data[0] << endl
                        << "Guest Name: " << data[1] << endl
                        << "Contact: " << data[2] << endl
                        << "Residency Status: " << data[4] << endl
                        << "Room Id: " << data[3];
                }
                back_to_menu = true;
                file.close();
                break;

            case ESC:
                exit_program = true;
                back_to_menu = true;
                break;
            default:
                //There's actually no need for a default function
                break;
            }
        }
    }
return 0;
}

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