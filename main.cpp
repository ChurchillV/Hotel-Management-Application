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
    admin1.showAllGuests();
    return 0;
}
