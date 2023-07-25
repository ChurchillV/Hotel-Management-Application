#include <iostream>
#include "classes&functions.h"
#include <conio.h>

/*
  ```````#############################   GROUP I   ############################# 

                        1  - ANKRAH Vince Churchill          - 7092021
                        2  - OCHIR Uncle Jojo                - 7104821
                        3  - MUSTAPHA Iddriss Hamidu         - 7103921
                        4  - ESSIEN Ernest Kojo              - 7098521
                        5  - TIJANI Hassan Cissey            - 7110021
                        6  - ESSIEDU Daniel                  - 7098421
                        7  - OFORI Isaac Nana Kwabena Nyame  - 7105621
                        8  - OFORI Twum Michael              - 7105821
                        9  - TAMAKLOE Mark Sivan             - 7109421
                        10 - AYOMAH Richard Arthur           - 7093921
                        11 - GAWU-MENSAH Sidney Selorm Kofi  - 7098821
                        12 - AWUKU Samuel Akoto              - 7093721
*/

int main() {
    bool isProgramRunning, adminMenu, guestMenu;
    do {
        intro();
        std::cout << "\nHOTEL MANAGEMENT APPLICATION"
            << "\n---------------------------------"
            << "\nADMIN LOGIN - Press a"
            << "\nGUEST LOGIN - Press g"
            << "\nEXIT PROGRAM - Press ESC\n\n";
            int  option = getch();
            Guest guest1;
            Admin admin1;
        if (option == a) {
            bool login_success = admin1.adminLogin();
            if(login_success) {
            do {
                adminMenu = false;
                char choice;
                std::cout << "\nPlease enter an option"
                << "\n---------------------------------"
                    << "\n1.  Show all rooms"
                    << "\n2.  Search for a particular room"
                    << "\n3.  Search for available rooms"
                    << "\n4.  Add room"
                    << "\n5.  Remove a room"
                    << "\n6.  Show all guests"
                    << "\n7.  Search for Guest"
                    << "\n8.  Add Guest"
                    << "\n9.  Remove Guest"
                    << "\nb.  Back to main menu"
                    << "\ne.  Exit\n";
                // << "\nEnter 0 to go back\n\n";
                std::cout << "> > ";
                std::cin >> choice;

                switch (choice) {
                case '1':
                    admin1.showAllRooms();
                    std::cout << "\nPerform another task? (y/n[Back to main menu])\n> >";
                    choice = getch();
                    if(choice == 'n') isProgramRunning = true;
                    else if (choice == 'y') adminMenu = true;
                    break;

                case '2':
                    admin1.searchForRoom();
                    std::cout << "\nPerform another task? (y/n[Back to main menu])\n> >";
                    choice = getch();
                    if(choice == 'n') isProgramRunning = true;
                    else if (choice == 'y') adminMenu = true;
                    break;

                case '3':
                    admin1.searchAvailableRooms();
                    std::cout << "\nPerform another task? (y/n[Back to main menu])\n> >";
                    choice = getch();
                    if(choice == 'n') isProgramRunning = true;
                    else if (choice == 'y') adminMenu = true;
                    break;

                case '4':
                    admin1.addRoom();
                    std::cout << "\nPerform another task? (y/n[Back to main menu])\n> >";
                    choice = getch();
                    if(choice == 'n') isProgramRunning = true;
                    else if (choice == 'y') adminMenu = true;
                    break;

                case '5':
                    admin1.removeRoom();
                    std::cout << "\nPerform another task? (y/n[Back to main menu])\n> >";
                    choice = getch();
                    if(choice == 'n') isProgramRunning = true;
                    else if (choice == 'y') adminMenu = true;
                    break;

                case '6':
                    admin1.showAllGuests();
                    std::cout << "\nPerform another task? (y/n[Back to main menu])\n> >";
                    choice = getch();
                    if(choice == 'n') isProgramRunning = true;
                    else if (choice == 'y') adminMenu = true;
                    break;

                case '7':
                    admin1.searchForGuest();
                    std::cout << "\nPerform another task? (y/n[Back to main menu])\n> >";
                    choice = getch();
                    if(choice == 'n') isProgramRunning = true;
                    else if (choice == 'y') adminMenu = true;
                    break;

                case '8':
                    admin1.addGuest();
                    std::cout << "\nPerform another task? (y/n[Back to main menu])\n> >";
                    choice = getch();
                    if(choice == 'n') isProgramRunning = true;
                    else if (choice == 'y') adminMenu = true;
                    break;

                case '9':
                    admin1.removeGuest();
                    std::cout << "\nPerform another task? (y/n[Back to main menu])\n> >";
                    choice = getch();
                    if(choice == 'n') isProgramRunning = true;
                    else if (choice == 'y') adminMenu = true;
                    break;

                case 'b':
                    isProgramRunning = true;
                    break;

                case 'e':
                    isProgramRunning = false;
                    break;
                default:
                    std::cout<< "\nYou entered an invalid option, please try again."<< endl;
                    adminMenu = true;
                    break;
                }
            } while(adminMenu);

        }
    }
        else if (option == g) {
            char choice;
            do {
                guestMenu = false;
                std::cout << "\nPlease enter an option"
                << "\n----------------------------------"
                << "\n1.  Search for available rooms"
                << "\n2.  Check for personal details"
                << "\n3.  Leave room"
                << "\n4.  Back to Main Menu\n\n"
                << "\n5.  Exit\n\n";
                string name, f_name, l_name, ID;
                bool login_success;
                std::cin >> choice;
                switch (choice)
                {
                    case '1':
                        std::cout << "These are the rooms available:"
                        << "\n---------------------------------------\n";
                        admin1.searchAvailableRooms();
                        std::cout << "\nPerform another action?(y/n [Back to main menu])\n > >";
                        choice = getch();
                        if(choice == 'n') isProgramRunning = true;
                        else if (choice == 'y') guestMenu = true;
                        break;
                    case '2':
                        std::cout << "Enter your first name: ";
                        std::cin >> f_name;
                        std::cout << "Enter your last name: ";
                        std::cin >> l_name;
                        name = l_name + " " + f_name;
                        std::cout << "Enter you ID: ";
                        std::cin >> ID;
                        login_success = guest1.guestLogin(name, ID);
                        if(login_success){
                        admin1.searchForGuest(name, ID);
                        std::cout << "\nPerform another action?(y/n [Back to main menu])\n > >";
                        choice = getch();
                        if(choice == 'n') isProgramRunning = true;
                        else if (choice == 'y') guestMenu = true;
                        }
                        else guestMenu = true;
                        break;
                    case '3':
                        std::cout << "Enter your first name: ";
                        std::cin >> f_name;
                        std::cout << "Enter your last name: ";
                        std::cin >> l_name;
                        name = l_name + " " + f_name;
                        std::cout << "Enter you ID: ";
                        std::cin >> ID;
                        login_success = guest1.guestLogin(name, ID);
                        if(login_success){
                        admin1.removeGuest(name, ID);
                        std::cout << "\nPerform another action?(y/n [Back to main menu])\n > >";
                        choice = getch();
                        if(choice == 'n') isProgramRunning = true;
                        else if (choice == 'y') guestMenu = true;
                        } else guestMenu = true;
                        break;
                    case '4':
                        isProgramRunning = true;
                        break;
                    case '5':
                        isProgramRunning = false;
                        break;
                    case 'y':
                        guestMenu = true;
                        break;
                    case 'n' :
                        isProgramRunning = true;
                        break;
                    default:
                        std::cout<< "\nYou entered an invalid option, please try again.\n"<< endl;
                        guestMenu = true;
                        // if(choice == 'n') goto main_menu;
                        break;
                }
            } while(guestMenu);
        }
        else if (option == ESC) {
            isProgramRunning = false;
        }

    } while(isProgramRunning);
    outro();
    return 0;
}