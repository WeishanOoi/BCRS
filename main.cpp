/* Developed By:
 *
 * Ooi Weishan
 * Nicole Ha Yah Yie
 * Mathavan Krishnan
 * Sofea Athirah
 * Hun Wei Jie
 *
 */
#include <iostream>
#include <ctime>
#include <conio.h>
#include "Court.hpp"
#include "Membership.hpp"
#include "Reservation.hpp"
#include "Equipment.hpp"
#include "Reservation.hpp"
using namespace std;

void court_reservation();
void ticket_cancellation();
void equipments();
void membership();
void employees();
void welcomeScreen();
void mainMenu();
void title();
void adminLogin();
void adminMenu();
void reservation_info();

int main(){
    system("title Badminton Court Reservation System");
    system("COLOR 70");

    system("cls");
    welcomeScreen();
    mainMenu();

    return 0;
}

void welcomeScreen()
{
    system("cls");

    cout << "\n\n\n\n"
         << "\t\t\t\t================================================\n"
         << "\t\t\t\t||                  WELCOME TO                ||\n"
         << "\t\t\t\t||                                            ||\n"
         << "\t\t\t\t||     BADMINTON COURT RESERVATION SYSTEM     ||\n"
         << "\t\t\t\t||                                            ||\n"
         << "\t\t\t\t================================================\n\n\n"

         << "\t\t\t\t-------------------------------------------------\n"
         << "\t\t\t\t\t\t  Developed By:-                             \t\n"
         << "\t\t\t\t\t\t                                             \t\n"
         << "\t\t\t\t\t\t  Group 4                                    \t\n"
         << "\t\t\t\t-------------------------------------------------\n\n";

    system("pause");
    mainMenu();
}

void mainMenu(){
    char choice;
    time_t now = time(0);
    char* dt = ctime(&now);

    while (1){
        system("cls");

        // MENU ITEMS
        title();

        cout << "                  The local date and time is: " << dt << endl;
        cout <<
        "                                                                                                            \n"
        "                  ==========================        ==========================        ======================\n"
        "                  * (A)  COURT RESERVATION *        * (B) CANCEL RESERVATION *        * (C)   EQUIPMENTS  *\n"
        "                  ==========================        ==========================        ======================\n\n"
        "                  ==========================        ==========================        ======================\n"
        "                  * (D)    MEMBERSHIP      *        * (E)       ADMIN        *        * (F)     QUIT       *\n"
        "                  *=========================        ==========================        ======================\n\n"
        "                                                                                                            \n";

        cout << "\n\t\t\t\t\tEnter your choice:-> ";
        cin >> choice;
        choice = toupper(choice);

        switch (choice)
        {
            case 'A':
                system("cls");
                court_reservation();
                break;
            case 'B':
                reservation_info();
                break;
            case 'C':
                equipments();
                break;
            case 'D':
                membership();
                break;
            case 'E':
                adminLogin();
                break;
            case 'F':
                system("cls");
                cout << "\n\n\n\n\t\t\t  Thanks for using our system...!!! \t\t\t\n";
                cout << "\n\n\t\t\t          Have a nice day...!!!      \t\t\t\n\n";
                exit(0);
            default:
                cout << "\n\t\t\t\t\tChoose valid option!!! \t\t\t\n";
                system("pause");
                mainMenu();
        }
    }
}

void title()
{
    const int WIDTH = 88;
    const int WIDTH1 = 18;
    const string heading =  "BADMINTON COURT RESERVATION SYSTEM (BCRS)" ;
    cout << "\n\n ";
         for(int i = 0; i < WIDTH1; i++){
                    cout << ' ';
            }
         for(int i = 0; i < WIDTH; i++){
                cout << '*';
            }
    cout << "\n\n";
    cout << "                                            " << heading;
    cout << "\n\n ";
         for(int i = 0; i < WIDTH1; i++){
                    cout << ' ';
            }
         for(int i = 0; i < WIDTH; i++){
                cout << '*';
            }
    cout << "\n\n";
}

void court_reservation(){
    Reservation r;
    system("CLS");
    title();
    r.add_reserve();
    system("pause");
    mainMenu();
}

void reservation_info(){
    system("CLS");
    title();
    Reservation r;
    r.cancel_reservation();
    system("pause");
    mainMenu();
}

void equipments(){
    system("CLS");
    title();
    Equipment e;
    e.viewEquip();
    e.buyEquip();
    system("pause");
}

void membership(){
    Membership m;
    char choice;
    system("CLS");
    title();
    cout << "\n\t\t========================\t==========================\t==========================\t\t\n"
         << "\t\t* (A) NEW MEMBER  *\t\t*(B) RENEW MEMBERSHIP *\t\t*(C) MEMBER INFORMATION *\t\n"
         << "\t\t========================\t==========================\t==========================\n\n"
         << "\t\t\t\t\t\t\t Input :" ;
    cin >> choice;
    choice = tolower(choice);

    while(1){
        switch (choice){
            case 'a':
                m.newMember();
                system("pause");
                mainMenu();
                break;

            case 'b':
                m.renewMember();
                system("pause");
                mainMenu();
                break;

            case 'c':
                m.infoMember();
                system("pause");
                mainMenu();
                break;

            default:
                cout << "\n\t\t\t\t\t\t  Choose valid option!!! \t\t\t\n\n";
                system("pause");
                membership();
        }
    }

}

void adminLogin()
{
    string adminUname;
    char adminPass[50];

    system("cls");
    title();

    cout << "\n\t\t\t\tEnter AdminID:-> ";
    cin >> adminUname;
    cout << "\n\t\t\t\tEnter Password:-> ";

    int a = 0;
    while(adminPass[a - 1] != '\r'){
        adminPass[a] = getch();
        if(adminPass[a-1]!='\r'){
            cout << "*";
        }
        a++;
    }
    adminPass[a-1] = '\0';
    string pw = adminPass;

    if (adminUname == "admin" && pw == "pass"){
        adminMenu();
    }
    else{
        cout << "\n\t\t\t\tUsername or Password is wrong...!!! ";
        system("pause");
        cin.clear();
        adminLogin();
    }
}

void adminMenu(){
    Court c;
    Reservation r;
    Equipment e;
    int choice;

    while(1)
    {
        system("cls");
        title();

        cout << "\t\t\t\t\t-------------------------------------------------\n";
        cout << "\t\t\t\t\t 1. Add Court                                    \n";
        cout << "\t\t\t\t\t-------------------------------------------------\n";
        cout << "\t\t\t\t\t 2. View Court                                   \n";
        cout << "\t\t\t\t\t-------------------------------------------------\n";
        cout << "\t\t\t\t\t 3. Edit Court                                   \n";
        cout << "\t\t\t\t\t-------------------------------------------------\n";
        cout << "\t\t\t\t\t 4. Remove Court                                 \n";
        cout << "\t\t\t\t\t-------------------------------------------------\n";
        cout << "\t\t\t\t\t 5. Add New Equipments                           \n";
        cout << "\t\t\t\t\t-------------------------------------------------\n";
        cout << "\t\t\t\t\t 6. Edit Existing Equipments                     \n";
        cout << "\t\t\t\t\t-------------------------------------------------\n";
        cout << "\t\t\t\t\t 7. Remove Existing Equipments                   \n";
        cout << "\t\t\t\t\t-------------------------------------------------\n";
        cout << "\t\t\t\t\t 8. Display Total Sales                          \n";
        cout << "\t\t\t\t\t-------------------------------------------------\n";
        cout << "\t\t\t\t\t 9. Display Total Bookings                       \n";
        cout << "\t\t\t\t\t-------------------------------------------------\n";
        cout << "\t\t\t\t\t 10. BACK                                        \n";
        cout << "\t\t\t\t\t-------------------------------------------------\n\n";

        cout << "\n\t\t\t\t\tEnter your choice:-> ";
        cin >> choice;

        switch(choice){
            case 1:
                system("cls");
                title();
                c.addCourt();
                system("pause");
                break;

            case 2:
                system("cls");
                title();
                c.displayAllCourt();
                system("pause");
                break;

            case 3:
                system("cls");
                title();
                c.displayAllCourt();
                c.editCourt();
                system("pause");
                break;

            case 4:
                system("cls");
                title();
                c.displayAllCourt();
                c.removeCourt();
                system("pause");
                break;

            case 5:
                system("cls");
                title();
                e.addEquip();
                system("pause");
                break;

            case 6:
                system("cls");
                title();
                e.editEquip();
                system("pause");
                break;

            case 7:
                system("cls");
                title();
                e.removeEquip();
                system("pause");
                break;

            case 8:
                system("cls");
                title();
                r.displayTotal();
                system("pause");
                break;

            case 9:
                system("cls");
                title();
                r.displayDetails();
                system("pause");
                break;

            case 10:
                system("cls");
                mainMenu();
                break;

            default:
                cout << "\n\t\t\t\t\tChoose valid option!!! \t\t\t\n";
                cin.clear();
                cin.ignore();
                system("pause");
                adminMenu();
        }
    }
}
