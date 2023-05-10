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
    cout << "\tThe amount you need to pay is : RM " << pay << endl << endl;
    cout << "\n\tCash          : " << "RM ";
    //cin >> cash;
//    while (cash < pay){
//        cout << "\n\tSorry! Your cash is insufficient, please pay the sufficient amount of cash! " << endl;
//        cout << "\n\tCash : " << "RM ";
//        cin >> cash;
//    }

    while(true){
        //cout << "\n\tCash          : " << "RM ";
        cin >> cash;

        if(cin.fail()){
            cout<<endl;
            cout << "\tInvalid input!"<<endl;
            cout<<"\tPlease enter a valid cash: RM ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        else if(cash < pay){
            cout << "\tInvalid input!"<<endl;
            cout<<"\tPlease enter a valid cash: RM ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        break;
    }

    double remaining = cash - pay;
    cout<< setprecision(2) << "\n\tThe change is RM " << remaining << ", Thank you!" << endl;

}

void Reservation::add_reserve(){
    Court c;

    time_t now = time(0);
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

	while(response != 'a' && response != 'b'){
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

	else{
		system("CLS");

        r->setName();
		r->setPhonenumber();
	}

    int order_id_num = (rand() % 99999) + 10000;
    order_id = to_string(order_id_num);
	system("CLS");

    c.displayAllCourt();
    Court foundCourt;


    while(true){
        cout << "\t\t\tChoose your preferred court id: ";
        cin >> selection_court;
        // Change Court ID to uppercase
        for (char& c : selection_court) {
            c = toupper(c);
        }

        cout << endl;

        if (c.searchCourt(selection_court, foundCourt)) {
            if(foundCourt.getCourtAvail() == 1){
                cout << "\t\t\tCourt Selected!!! " << endl;
                cout << "\t\t\tCourt ID: " << foundCourt.getCourtId() << endl;
                cout << "\t\t\tStart Time: " << foundCourt.getStartTime() << endl;
                cout << "\t\t\tEnd Time: " << foundCourt.getEndTime() << endl;
                cout << "\t\t\tPrice: " << foundCourt.getCourtPrice() << endl << endl;
                break;
            }else{
                cout << "\t\t\tSorry, the court is not available. Please input an available court ID." << endl;
                continue;
            }
        }else{
            cout << "\t\t\tInvalid court id! Please enter a valid court id." << endl;
            continue;
        }
    }

        system("pause");
        system("CLS");

        cout<<endl
            << "\t=========================================================\n"
            << "\t=                         RECEIPT                       =\n"
            << "\t---------------------------------------------------------\n"
            << "\t=                      COURT INVOICE                    =\n"
            << "\t=========================================================\n\n"
            <<endl
            << "\n\tOrder ID : " << order_id << endl
            << "\n\tTo Mr/Ms " << r->getName() << ",\n"
            << "\n\tYou have reserved " << foundCourt.getCourtId() << " from " << foundCourt.getStartTime() << " to " << foundCourt.getEndTime();


        cout << "\n\tPrice of court : " << "RM " << foundCourt.getCourtPrice() << endl << endl;
        cout << "\t---------------------------------------------------------" << endl
            << left << setw(15) << "\n\tAmount to PAY : RM " << foundCourt.getCourtPrice() << endl;

        payment(foundCourt.getCourtPrice());

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
        foundCourt.changeAvailability(foundCourt.getCourtId(), foundCourt.getCourtAvail());

        /*}catch(const exception& e){
            // print an error message
            cerr << e.what() << endl;
        }*/
}

void Reservation::cancel_sales(string cancel_id){


    unordered_map<string, Reservation> sales;
    unordered_map<string, Reservation>:: iterator it;
    unordered_map<string, Reservation>:: iterator i;
    fstream Sale;
    Reservation curSale;

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
            getline(Sale, price_string, '|');
            stringstream(price_string) >> price;

            string file_type_string;
            getline(Sale, file_type_string);
            stringstream(file_type_string) >> file_type;

            curSale.year = year;
            curSale.month = month;
            curSale.day = day;
            curSale.order_id = order_id;
            curSale.price = price;
            curSale.file_type = file_type;

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
                Sale << sale.year << '|'<< sale.month << '|'<< sale.day<< '|' << sale.order_id << '|' << sale.price<< '|' << sale.file_type << endl;
            }
            Sale.close();
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

    cout << "\t\t\tEnter Order ID: ";
    cin >> search_id;

    it = reservation.find(search_id);

    if(it != reservation.end()){
        // If exist, prompt message to confirm remove court
        cout << "\t\t\tOrder " << search_id << " found." << endl;
        char ch;
        do{
            cout << "\n\t\t\tAre you sure you want to remove this reservation? [Y/n]: ";
            cin >> ch;
            ch = tolower(ch);
        }while(ch!='y' && ch !='n');

        if(ch=='y'){
            // Remove the selected court from Hash Table
            reservation.erase(search_id);

            // Store current contents in Hash Table to .txt file
           reserve.open("reservation.txt", ios::out);
            for (i = reservation.begin(); i != reservation.end(); i++){
                const Reservation& reserv = i->second;
                reserve << reserv.order_id << '|' << reserv.court_id << '|' << reserv.start_time << '|' << reserv.end_time << '|' << reserv.name << '|'<< reserv.phone_number <<'|' << reserv.price << '|'<< reserv.year << '|'<< reserv.month << '|'<< reserv.day <<endl;
            }
            reserve.close();
            cancel_sales(search_id);

            cout << "\n\t\t\t" << search_id << " is removed successfully."  << endl;

        }else{
            cout << "\n\t\t\tOrder " << search_id << " is not removed.\n" << endl;
        }
    }else{
        cout << "\n\t\t\tOrder " << search_id << " does not exist. Try again!" << endl;
    }
        }catch(const exception& e){
                // print an error message
                cerr << e.what() << endl;
        }
}

struct Sale{
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

void Reservation::totalSalesFrame(){
        cout << "\t\t\t";
        for(int i=0; i<50; i++){
            cout << "-";
        }

        cout << "\n\t\t\t" << setw(12) << "Receipt ID" << setw(13) << "Price" << setw(25) << "Date (yy/mm/dd)" << endl;
        cout << "\t\t\t";
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

    cout << "\t\t\tDisplay Total Sales for Year/ Month/ Day (Y/M/D): ";
    cin >> ts_input;

    ts_input = tolower(ts_input);

    while (ts_input != 'y' && ts_input != 'm' && ts_input != 'd'){
        cout << "\t\t\tEnter a valid input: ";
        cin >> ts_input;
    }

    bool year_avail = 0, month_avail = 0, day_avail = 0;



    while(true){
        cout << "\t\t\tEnter year: ";
        cin >> year_input;

        if(!cin){
            cout << "Invalid input. Please enter a number for the year." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if(ts_input == 'm' || ts_input == 'd'){
            while(true){
                cout << "\t\t\tEnter month: ";
                cin >> month_input;

                if(!cin){
                    cout << "Invalid input. Please enter a number for the month." << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }

                if(ts_input == 'd'){
                    while(true){
                        cout << "\t\t\tEnter day: ";
                        cin >> day_input;

                        if(!cin){
                            cout << "Invalid input. Please enter a number for the day." << endl;
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            continue;
                        }

                        for (int i=0; i<numSale; i++){
                            if(sales[i].year1==year_input && sales[i].month1==month_input && sales[i].day1==day_input){
                                day_avail = 1;
                            }
                        }
                        goto display;
                    }
                }

                for (int i=0; i<numSale; i++){
                    if(sales[i].year1==year_input && sales[i].month1==month_input){
                        month_avail = 1;
                    }
                }
                goto display;
            }
        }

        for (int i=0; i<numSale; i++){
            if(sales[i].year1 == year_input){
                year_avail = 1;
            }
        }

        break;
    }

    display:
    if (year_avail || month_avail || day_avail){
        for (int j = 1; j <=3; j++){
            if (j == 1){
                cout << "\n\t\t\tSales for Court : " << endl;
            }
            if (j == 2){
                cout << "\n\t\t\tSales for Equipment : " << endl;
            }
            if (j == 3){
                cout << "\n\t\t\tSales for Membership Renewal : " << endl;
            }

            totalSalesFrame();
            for(int i=0; i<numSale; i++){
                if(year_avail){
                    if(sales[i].year1 == year_input && sales[i].file_type == j){
                    cout << "  \t\t\t  " << sales[i].order_id1 << "\t\t" << "RM " << sales[i].price1 << ".00"
                        << "\t\t" << sales[i].year1 << '/' << sales[i].month1 << '/' << sales[i].day1 << endl;
                    total = total + sales[i].price1;
                    }
                }

                else if(month_avail){
                    if(sales[i].year1==year_input && sales[i].month1==month_input && sales[i].file_type == j){
                    cout << "  \t\t\t  " << sales[i].order_id1 << "\t\t" << "RM " << sales[i].price1 << ".00"
                        << setw(14) << sales[i].year1 << '/' << sales[i].month1 << '/' << sales[i].day1 << endl;
                    total = total + sales[i].price1;
                    }
                }

                else if(day_avail){
                    if(sales[i].year1==year_input && sales[i].month1==month_input && sales[i].day1 == day_input && sales[i].file_type == j){
                    cout << "  \t\t\t  " << sales[i].order_id1 << "\t\t" << "RM " << sales[i].price1 << ".00"
                        << "\t\t" << sales[i].year1 << '/' << sales[i].month1 << '/' << sales[i].day1 << endl;
                    total = total + sales[i].price1;
                    }
                }
            }

            cout << "\t\t\t";
            for(int i=0; i<50; i++){
                cout << "-";
            }
            cout << endl;
        }
        cout << endl;
        cout << "\t\t\tTotal sales for " << year_input << ": RM " << total << "\n" << endl;
    }

    else{
        cout << "\nData for this year does not exist" << endl;
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
