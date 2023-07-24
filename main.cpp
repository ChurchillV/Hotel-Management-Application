#include <iostream>
#include "classes&functions.h"
#include <conio.h>
using namespace std;

int main()
{
    intro();
    cout << "\nHOTEL MANAGEMENT APPLICATION"
        << "\n---------------------------------"
        << "\nADMIN LOGIN - Press a"
        << "\nGUEST LOGIN - Press g"
        << "\nEXIT PROGRAM - Press ESC\n\n";
        char option;
        cout << "> > ";
        cin >> option;
    Admin admin1;
    Guest guest1;

    if (option == 'a')
    {
        bool login_success = admin1.adminLogin();
        if(login_success) {

        int choice;
        char try_again = 'y';
        while(try_again == 'y') {
        cout << "\nPlease enter an option"
        << "\n---------------------------------"
            << "\n1.  Show all rooms"
            << "\n2.  Search for a particular room"
            << "\n3.  Search for unoccupied rooms"
            << "\n4.  Add room"
            << "\n5.  Remove a room"
            << "\n6.  Show all guests"
            << "\n7.  Search for Guest"
            << "\n8.  Add Guest"
            << "\n9.  Remove Guest"
            << "\n10. Exit\n";
           // << "\nEnter 0 to go back\n\n";
        cout << "> > ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            admin1.showAllRooms();
            break;

        case 2:
            admin1.searchForRoom();
            break;

        case 3:
            admin1.searchAvailableRooms();
            break;

        case 4:
            admin1.addRoom();
            break;

        case 5:
           admin1.removeRoom();
            break;

        case 6:
            admin1.showAllGuests();
            break;

        case 7:
            admin1.searchForGuest();
            break;

        case 8:
            admin1.addRoom();
            break;

        case 9:
            admin1.removeGuest();
            break;

        case 10:
            return 0;

        default:
            cout<< "You entered an invalid option, please try again. y/n: "<< endl;
            cin >> try_again;
            break;
        }
      }

    }
}
    else if (option == 'g')
    {
        char choice;
        do{
            cout << "\nPlease enter an option"
            << "\n----------------------------------"
            << "\n1.  Search for available rooms"
            << "\n2.  Check for personal details"
            << "\n3.  Leave room"
            << "\n4.  Exit\n\n";
            string name, f_name, l_name, ID;
            bool login_success;
            cin >> choice;
            switch (choice)
            {
                case '1':
                    cout << "These are the list of rooms available"
                        << "\n---------------------------------------";
                    admin1.searchAvailableRooms();
                    cout << "Perform another action?(y/n)\n > >";
                    cin >> choice;
                    break;
                case '2':
                    cout << "Enter your first name: ";
                    cin >> f_name;
                    cout << "Enter your last name: ";
                    cin >> l_name;
                    name = l_name + " " + f_name;
                    cout << "Enter you ID: ";
                    cin >> ID;
                    login_success = guest1.guestLogin(name, ID);
                    if(login_success){
                    admin1.searchForGuest(name, ID);
                    cout << "Perform another action?(y/n)\n > >";
                    cin >> choice;
                    }
                    break;
                case '3':
                    cout << "Enter your first name: ";
                    cin >> f_name;
                    cout << "Enter your last name: ";
                    cin >> l_name;
                    name = l_name + " " + f_name;
                    cout << "Enter you ID: ";
                    cin >> ID;
                    login_success = guest1.guestLogin(name, ID);
                    if(login_success){
                    admin1.removeGuest(name, ID);
                    cout << "Perform another action?(y/n)\n > >";
                    cin >> choice;
                    }
                    break;
                case '4':
                    return 0;

                default:
                    cout<< "You entered an invalid option, please try again."<< endl;
                    cout << "Perform another action?(y/n)\n > >";
                    cin >> choice;
                    break;
            }
        } while(choice == 'y');
    }
    return 0;
    }