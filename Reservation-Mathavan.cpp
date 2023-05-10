#include <cstdlib>
#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <exception>


#include "Reservation.hpp"
#include "Court.hpp"
#include "Membership.hpp"
#include "Equipment.hpp"


using namespace std;


Reservation::Reservation(){
    order_id = "";
    court_id = "";
    start_time = "";
    end_time = "";
    name = "";
    phone_number = "";
    price = 0.00;
    year = 0;
    month = 0;
    day = 0;
}

Reservation::~Reservation(){};

    /*Member *member = new Member;
    login(member);*/ //function for when the user is member


void Reservation::setName(){
            cout<< "\n\t\t\t\n"
            <<"\t\t\tEnter your name : ";
            cin.ignore();
            getline(cin, name);
            cout << endl;
        }

void Reservation::setPhonenumber(){
            cout << "\t\t\tEnter your phone number : ";
            cin >> phone_number;

            int phone_length = phone_number.length();

            while (phone_length != 10){
               cout << endl;
               cout << "\t\t\tEnter a valid phone number: ";
               cin >> phone_number;
               phone_length = phone_number.length();
            }

            cout << endl;
        }

string Reservation::getName(){
            return name;
        }

string Reservation::getPhonenumber(){
            return phone_number;
        }

void Reservation::payment(double pay){

    double cash;
    cout << " The amount you need to pay is : RM " << pay << endl << endl;
    cout << "\nCash          : " << "RM ";
    cin >> cash;
    while (cash < pay)
        {
            cout << "\nSorry! Your cash is insufficient, please pay the sufficient amount of cash! " << endl;
            cout << "\nCash : " << "RM ";
            cin >> cash;
        }
        double remaining = cash - pay;
        cout<< setprecision(2) << "\nThe change is RM " << remaining << ", Thank you!" << endl;


}

void Reservation::add_reserve(){
    Court c;

    time_t now = time(0);
    //char* dt = ctime(&now);
    tm *ltime = localtime(&now);

    srand(time(0)); //getting random no.

	string selection_court;
	Reservation* r = new Reservation;

    system("cls");
    char response;
    	cout <<"\n"
    	<< "\n\t\t\t\t\t\t*************************\n"
		<< "\t\t\t\t\t\t*    (A) MEMBER LOGIN   * \n"
		<< "\t\t\t\t\t\t************************* \n\n\n"
		<< "\t\t\t\t\t\t************************* \n"
		<< "\t\t\t\t\t\t*    (B) GUEST LOGIN    * \n"
		<< "\t\t\t\t\t\t************************* \n\n\n";

    cout << "\t\t\tSELECT AN OPTION: ";
    cin >> response;
    response = tolower(response);

	while(response != 'a' && response != 'b')
	{
		cout << "\t\t\tYou have entered a wrong selection. Try again: ";
		cin.ignore(10000, '\n');
		cin >> response;
		response = tolower(response);
	}

	if (response == 'a') {
		system("CLS");
		Membership member;
        member.login(member.members);

        string fullname = member.members -> fname + " " + member.members -> lname;
        r -> name = fullname;
        r -> phone_number = member.members -> phone_number;
	}

	else
	{
		system("CLS");

        r->setName();
		r->setPhonenumber();
	}



    int order_id_num = (rand() % 99999) + 10000;
    order_id = to_string(order_id_num);
	system("CLS");

    c.displayAllCourt();
    cout<<"Choose ur preferred court id: ";
    cin>>selection_court;
    cout<<endl;
    Court foundCourt;


    try{
        Court foundCourt;
        if (!c.searchCourt(selection_court, foundCourt)) {
            if(foundCourt.getCourtAvail()== 0){
                throw runtime_error("Invalid court id!");
            }else{
                cout << "Court found: " << endl;
                cout << "ID: " << foundCourt.getCourtId() << endl;
                cout << "Start Time: " << foundCourt.getStartTime() << endl;
                cout << "End Time: " << foundCourt.getEndTime() << endl;
                cout << "Price: " << foundCourt.getCourtPrice() << endl;
                cout << "Availability: " << foundCourt.getCourtAvail() << endl;
            }

        }else{
                cout<<"Please input an available court: ";
                cin>>selection_court;
                cout<<endl;
                cout << "Court not found." << endl;
        }

    //Court foundCourt; //foundcourt is another obj
    /*if(c.searchCourt(selection_court, foundCourt)){
            if(foundCourt.getCourtAvail()== 1){
                cout << "Court found: " << endl;
                cout << "ID: " << foundCourt.getCourtId() << endl;
                cout << "Start Time: " << foundCourt.getStartTime() << endl;
                cout << "End Time: " << foundCourt.getEndTime() << endl;
                cout << "Price: " << foundCourt.getCourtPrice() << endl;
                cout << "Availability: " << foundCourt.getCourtAvail() << endl;
            }else{
                cout<<"Please input an available court: ";
                cin>>selection_court;
                cout<<endl;
                cout << "Court not found." << endl;
            }
    }else{
        cout<<"Please input an available court: ";
        cin>>selection_court;
        cout<<endl;
        cout << "Court not found." << endl;
    }*/

    system("pause");


        system("CLS");
        cout<<endl
            << "\t=========================================================\n"
            << "\t=                         RECEIPT                       =\n"
            << "\t---------------------------------------------------------\n"
            << "\t=                      COURT INVOICE                    =\n"
            << "\t=========================================================\n\n"
            <<endl
            << "\t\nOrder ID : " << r->order_id << endl
            << "\t\nTo Mr/Ms " << r->getName() << ",\n"
            << "\t\nYou have reserved " << foundCourt.getCourtId() << " from " << foundCourt.getStartTime() << " to " << foundCourt.getEndTime();


        cout << "\nPrice of court : " << "RM " << foundCourt.getCourtPrice() << endl << endl;
        cout << "---------------------------------------------------------" << endl
            << left << setw(15) << "\nAmount to PAY : RM " << foundCourt.getCourtPrice() << endl;

        payment(foundCourt.getCourtPrice());


        /*double num = foundCourt.getCourtPrice();
        int price = int(num);*/


    fstream reservation;

    reservation.open("reservation.txt", ios::app);
    reservation << order_id << '|' << foundCourt.getCourtId() << '|' << foundCourt.getStartTime() << '|' <<  foundCourt.getEndTime()
        << '|'<< r->getName() << '|'<< r->getPhonenumber() <<'|'<<  foundCourt.getCourtPrice() << '|'
        <<1900+ltime->tm_year << '|' << 1+ltime->tm_mon << '|' << ltime->tm_mday <<endl;

    reservation.close();

    ofstream salesFile;
    salesFile.open("sales.txt", ios::app);
    salesFile << 1900+ltime->tm_year << '|' << 1+ltime->tm_mon << '|' << ltime->tm_mday << '|' <<
                 order_id << '|' << foundCourt.getCourtPrice() << '|' << 1 << endl;
    salesFile.close();

    //Change availability in Court.txt file (added by ncl)
    foundCourt.changeAvailability(foundCourt.getCourtId(), foundCourt.getCourtAvail()); //, foundCourt.getCourtAvail()


    cout << "Court " << order_id << " is added successfully" << endl;

    }catch(const exception& e){
                // print an error message
                cerr << e.what() << endl;
        }
}

void Reservation::cancel_sales(string cancel_id){

    // Hash table for storing list of courts
    unordered_map<string, Reservation> sales;
    unordered_map<string, Reservation>:: iterator it;
    unordered_map<string, Reservation>:: iterator i;
    fstream Sale;
    Reservation curSale;

    // Note to self: create a function to load the file -> can be reuse in diff func (if have enof time)
    // Read Court.txt file and store the contents into the hash table
    Sale.open("sales.txt", ios::in);
    while(!Sale.eof()){

            string year_string;
            getline(Sale, year_string, '|');
            stringstream(year_string) >> year;

            string month_string;
            getline(Sale, month_string, '|');
            stringstream(month_string) >> month;

            string day_string;
            getline(Sale, day_string, '|');
            stringstream(day_string) >> day;

            getline(Sale, order_id, '|');

            string price_string;
            getline(Sale, price_string);
            stringstream(price_string) >> price;

            curSale.year = year;
            curSale.month = month;
            curSale.day = day;
            curSale.order_id = order_id;
            curSale.price = price;

            sales.insert(make_pair(curSale.order_id, curSale));
    }
    Sale.close();
    sales.erase("");

    it = sales.find(cancel_id);

    if(it != sales.end()){

            sales.erase(cancel_id);

            // Store current contents in Hash Table to .txt file
           Sale.open("sales.txt", ios::out);
            for (i = sales.begin(); i != sales.end(); i++){
                const Reservation& sale = i->second;
                Sale << sale.year << '|'<< sale.month << '|'<< sale.day<< '|' << sale.order_id << '|' << sale.price<<endl;
            }
            Sale.close();
            cout << cancel_id << " is removed successfully."  << endl;

        }else{
            cout << "Order " << cancel_id << " is not removed." << endl;
        }

}

void Reservation::cancel_reservation(){

    string search_id;

    // Hash table for storing list of courts
    unordered_map<string, Reservation> reservation;
    unordered_map<string, Reservation>:: iterator it;
    unordered_map<string, Reservation>:: iterator i;
    fstream reserve;
    Reservation curReserve;

    try{
        reserve.open("reservation.txt", ios::in);
        if (!reserve.is_open()) {
            throw runtime_error("Error opening reservation.txt file");
        }

    while(!reserve.eof()){
        getline(reserve, order_id, '|');
        getline(reserve, court_id, '|');
        getline(reserve, start_time, '|');
        getline(reserve, end_time, '|');
        getline(reserve, name, '|');
        getline(reserve, phone_number, '|');

        string price_string;
        getline(reserve, price_string, '|');
        stringstream(price_string) >> price;

        /*string dt_string;
        getline(reserve, dt_string);
        stringstream(dt_string) >> dt;*/
        string year_string;
        getline(reserve, year_string, '|');
        stringstream(year_string) >> year;

        string month_string;
        getline(reserve, month_string, '|');
        stringstream(month_string) >> month;

        string day_string;
        getline(reserve, day_string);
        stringstream(day_string) >> day;

        curReserve.order_id = order_id;
        curReserve.court_id = court_id;
        curReserve.start_time = start_time;
        curReserve.end_time = end_time;
        curReserve.name = name;
        curReserve.phone_number = phone_number;
        curReserve.price = price;
        curReserve.year = year;
        curReserve.month = month;
        curReserve.day = day;
        reservation.insert(make_pair(curReserve.order_id, curReserve));
    }
    reserve.close();
    reservation.erase("");

    cout << "Enter Order ID: ";
    cin >> search_id;

    it = reservation.find(search_id);

    if(it != reservation.end()){
        // If exist, prompt message to confirm remove court
        cout << "Order " << search_id << " found." << endl;
        char ch;
        do{
            cout << "\t\tAre you sure you want to remove this reservation? [Y/n]: ";
            cin >> ch;
            ch = tolower(ch);
        }while(ch!='y' && ch !='n');

        if(ch=='y'){
            // Remove the selected court from Hash Table
            reservation.erase(search_id);
            //cancel_sales(search_id);

            // Store current contents in Hash Table to .txt file
           reserve.open("reservation.txt", ios::out);
            for (i = reservation.begin(); i != reservation.end(); i++){
                const Reservation& reserv = i->second;
                reserve << reserv.order_id << '|' << reserv.court_id << '|' << reserv.start_time << '|' << reserv.end_time << '|' << reserv.name << '|'<< reserv.phone_number <<'|' << reserv.price << '|'<< reserv.year << '|'<< reserv.month << '|'<< reserv.day <<endl;
            }
            reserve.close();
            cancel_sales(search_id);

            cout << search_id << " is removed successfully."  << endl;

        }else{
            cout << "Order " << search_id << " is not removed." << endl;
        }
    }else{
        cout << "Order " << search_id << " does not exist. Try again!" << endl;
    }
        }catch(const exception& e){
                // print an error message
                cerr << e.what() << endl;
        }
}

struct Sale {
    int year1;
    int month1;
    int day1;
    int order_id1;
    int price1;
    int file_type;
};

bool compareYMD(Sale a, Sale b) {
    if (a.year1 != b.year1) {
        return a.year1 < b.year1;
    } else if (a.month1 != b.month1) {
        return a.month1 < b.month1;
    } else {
        return a.day1 < b.day1;
    }
}

void quickSort(Sale* arr, int low, int high) {
    if (low < high) {
        int pivot = arr[high].year1;
        int x = low - 1;

        for (int y=low; y<high; y++) {
            if (compareYMD(arr[y], arr[high])) {
                x++;
                swap(arr[x], arr[y]);
            }
        }

        swap(arr[x + 1], arr[high]);

        int pi = x + 1;
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void totalSalesFrame(){
        for(int i=0; i<50; i++){
            cout << "-";
        }

        cout << "\n" << setw(12) << "Receipt ID" << setw(13) << "Price" << setw(25) << "Date (yy/mm/dd)" << endl;
        for(int i=0; i<50; i++){
            cout << "-";
        }
        cout << endl;
}

void Reservation::displayTotal(){
    ifstream salesFile;
    ofstream tempFile;
    salesFile.open("sales.txt", ios::app);

    string line1;
    Sale sales[3000];
    int numSale = 0;

    int year, month, day, order_id, price, file_type;
    while (getline(salesFile, line1)){
        sscanf(line1.c_str(), "%d|%d|%d|%d|%d|%d", &year, &month, &day, &order_id, &price, &file_type);
        sales[numSale] = {year, month, day, order_id, price, file_type};
        numSale++;
    }

    quickSort(sales, 0, numSale-1);
    salesFile.close();

    char ts_input;
    int year_input, month_input, day_input, total = 0;

    cout << "Display Total Sales for Year/ Month/ Day (Y/M/D): ";
    cin >> ts_input;

    ts_input = tolower(ts_input);

    while (ts_input != 'y' && ts_input != 'm' && ts_input != 'd'){
        cout << "Enter a valid input: ";
        cin >> ts_input;
    }

    bool year_avail = 0, month_avail = 0, day_avail = 0;
    if(ts_input == 'y'){
        cout << "Enter year: ";
        cin >> year_input;

        for (int i=0; i<numSale; i++){
            if(sales[i].year1 == year_input){
                year_avail = 1;
            }
        }
    }

    else if(ts_input == 'm'){
        cout << "Enter year: ";
        cin >> year_input;
        cout << "Enter month: ";
        cin >> month_input;

        for (int i=0; i<numSale; i++){
            if(sales[i].year1==year_input && sales[i].month1==month_input){
                month_avail = 1;
            }
        }
    }

    else{
        cout << "Enter year: ";
        cin >> year_input;
        cout << "Enter month: ";
        cin >> month_input;
        cout << "Enter day: ";
        cin >> day_input;

       for (int i=0; i<numSale; i++){
            if(sales[i].year1==year_input && sales[i].month1==month_input && sales[i].day1==day_input){
                day_avail = 1;
            }
        }
    }

    if (year_avail || month_avail || day_avail){
        for (int j = 1; j <=3; j++){
            if (j == 1){
                cout << "\nSales for Court : " << endl;
            }
            if (j == 2){
                cout << "\nSales for Equipment : " << endl;
            }
            if (j == 3){
                cout << "\nSales for Membership Renewal : " << endl;
            }

            totalSalesFrame();
            for(int i=0; i<numSale; i++){
                if(year_avail){
                    if(sales[i].year1 == year_input && sales[i].file_type == j){
                    cout << setw(10) << sales[i].order_id1 << setw(12) << "RM " << sales[i].price1 << ".00"
                        << setw(14) << sales[i].year1 << '/' << sales[i].month1 << '/' << sales[i].day1 << endl;
                    total = total + sales[i].price1;
                    }
                }

                else if(month_avail){
                    if(sales[i].year1==year_input && sales[i].month1==month_input && sales[i].file_type == j){
                    cout << setw(10) << sales[i].order_id1 << setw(12) << "RM " << sales[i].price1 << ".00"
                        << setw(14) << sales[i].year1 << '/' << sales[i].month1 << '/' << sales[i].day1 << endl;
                    total = total + sales[i].price1;
                    }
                }

                else if(day_avail){
                    if(sales[i].year1==year_input && sales[i].month1==month_input && sales[i].file_type == j){
                    cout << setw(10) << sales[i].order_id1 << setw(12) << "RM " << sales[i].price1 << ".00"
                        << setw(14) << sales[i].year1 << '/' << sales[i].month1 << '/' << sales[i].day1 << endl;
                    total = total + sales[i].price1;
                    }
                }
            }

            for(int i=0; i<50; i++){
                cout << "-";
            }
            cout << endl;
        }
        cout << endl;
        cout << "\nTotal sales for " << year << ": RM " << total << "\n" << endl;
    }

    else{
        cout << "\nData
         does not exist" << endl;
    }
}

struct ReserveDet{
    int order_id;
    string court_id;
    string startTime;
    string endTime;
    string name;
    string phoneNum;
    string courtPrice;
    int year;
    int month;
    int day;
};

ReserveDet* merge(ReserveDet* arr1, int s1, ReserveDet* arr2, int s2){
    ReserveDet* result = new ReserveDet[s1 + s2];
    int x=0, y=0, z=0;

    while(x<s1 && y<s2){
        if(arr1[x].order_id < arr2[y].order_id){
            result[z] = arr1[x];
            x++;
        }
        else{
            result[z] = arr2[y];
            y++;
        }
        z++;
    }

    while(x<s1){
        result[z] = arr1[x];
        x++;
        z++;
    }
    while (y<s2){
        result[z] = arr2[y];
        y++;
        z++;
    }
    return result;
}

void mergeSort(ReserveDet* arr, int size) {
    if(size < 2){
        return;
   }

    int middle = size / 2;
    ReserveDet* left = new ReserveDet[middle];
    ReserveDet* right = new ReserveDet[size - middle];

    for (int i=0; i<middle; i++) {
        left[i] = arr[i];
    }
    for (int i=0; i< size-middle; i++) {
        right[i] = arr[middle + i];
    }

    mergeSort(left, middle);
    mergeSort(right, size-middle);

    ReserveDet* result = merge(left, middle, right, size-middle);

    for (int i=0; i<size; i++) {
        arr[i] = result[i];
    }

    delete[] left;
    delete[] right;
    delete[] result;
}

void Reservation::displayDetails(){
    ifstream reserveFile;
    reserveFile.open("reservation.txt", ios::app);

    ReserveDet details[6000];
    int numDet = 0;

    string line;
    while (getline(reserveFile, line)) {
        // Split the line on the '|' character
        stringstream ss(line);
        string item;
        getline(ss, item, '|');
        details[numDet].order_id = stoi(item);
        getline(ss, details[numDet].court_id, '|');
        getline(ss, details[numDet].startTime, '|');
        getline(ss, details[numDet].endTime, '|');
        getline(ss, details[numDet].name, '|');
        getline(ss, details[numDet].phoneNum, '|');
        getline(ss, details[numDet].courtPrice, '|');
        getline(ss, item, '|');
        details[numDet].year = stoi(item);
        getline(ss, item, '|');
        details[numDet].month = stoi(item);
        getline(ss, item, '|');
        details[numDet].day = stoi(item);
        numDet++;
    }
    reserveFile.close();

    // Sort the details array using merge sort
    mergeSort(details, numDet);

    // Write the sorted data to the tempReserve.txt file
    ofstream tempFile;
    tempFile.open("tempReserve.txt", ios::out);
    for (int i = 0; i < numDet; i++) {
        tempFile << details[i].order_id << "|" << details[i].court_id << "|" << details[i].startTime << "|" << details[i].endTime << "|" << details[i].name << "|" << details[i].phoneNum << "|" << details[i].courtPrice << "|" << details[i].year << "|" << details[i].month << "|" << details[i].day << endl;

    }

    // print the screen
    cout << endl;
    for(int i=0; i<110; i++){
        cout << "-";
    }

    cout << "\n" << setw(10) << "Order ID" << setw(14) << "Court ID" << setw(12) << "Time" << setw(16)
        << "Name" << setw(22) << "Phone Number" << setw(15) << "Court Price" << setw(20)
        << "Date (yy/mm/dd)" << endl;

    for(int i=0; i<110; i++){
        cout << "-";
    }

    for (int i = 0; i < numDet; i++) {
        cout << "\n" << setw(8) << details[i].order_id << setw(13) << details[i].court_id << setw(11)
            << details[i].startTime << " - " << details[i].endTime << setw(16) << details[i].name << setw(19)
            << details[i].phoneNum << setw(9) << "RM " << details[i].courtPrice << ".00" << setw(12)
            << details[i].year << '/' << details[i].month << '/' << details[i].day << endl;
    }

    for(int i=0; i<110; i++){
        cout << "-";
    }
    cout << endl;



    tempFile.close();

    ifstream tempF;
    ofstream reserveF;
    tempF.open("tempReserve.txt");
    reserveF.open("reservation.txt", ios::trunc);

    string line2;
    while(getline(tempF, line2)){
        reserveF << line2 << endl;
    }

    tempF.close();
    reserveF.close();
    remove("tempReserve.txt");
}
