#include <iostream>
#include "classes&functions.h"
using namespace std;

int main() {
    cout << "\nHOTEL MANAGEMENT APPLICATION"
        << "\n---------------------------------"
        << "\nADMIN LOGIN - Press a"
        << "\nGUEST LOGIN - Press g"
        << "\nEXIT PROGRAM - Press ESC";
    Admin admin1;
    vector<string> data = {"A675", "Yvonne Nartey", "321098", "Resident", "07"};
    // Guest guest1(data);
    // admin1.addGuest(data);
    Guest guest1;
    bool login_success = admin1.adminLogin();
    if(login_success) {
        admin1.removeGuest();
    }
    else cout << "Oops";
    return 0;
}