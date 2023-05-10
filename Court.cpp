#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <limits>
#include <unordered_map>
#include <vector>
#include <stdexcept>
#include "Court.hpp"
using namespace std;


Court::Court(){
    court_id = "";
    start_time = "";
    end_time = "";
    court_price = 0.00;
    court_avail = 1;
}

Court::~Court(){};

/*
 * By default, court availability is set as available(1) when a new court is added
 */
void Court::addCourt(){
    string new_cid, new_stime, new_etime;
    double new_cprice;

    cout << "\n\t\t\t\t\tEnter Court ID: ";
    cin >> new_cid;
    // Change Court ID to uppercase
    for (char& c : new_cid) {
        c = toupper(c);
    }

    cout << "\t\t\t\t\tEnter Start Time: ";
    //cin >> new_stime;

    int istime, estime;
    //stringstream(new_stime) >> istime;
//    while(istime < 0 || istime > 2400){
//        cout << "error!" << endl;
//    }

    while(true){
        cin >> istime;

        if(cin.fail()){
            cout<<endl;
            cout << "\t\t\t\t\tInvalid input!"<<endl;
            cout<<"\t\t\t\t\tPlease enter a valid start time: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        else if(istime < 0 || istime > 2400){
            cout << "\t\t\t\t\tInvalid input!"<<endl;
            cout<<"\t\t\t\t\tPlease enter a valid start time: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        break;
    }

    new_stime = to_string(istime);

    cout << "\t\t\t\t\tEnter End Time: ";
    //cin >> new_etime;
    //stringstream(new_stime) >> istime;

    while(true){
        cin >> estime;

        if(cin.fail()){
            cout<<endl;
            cout << "\t\t\t\t\tInvalid input!"<<endl;
            cout<<"\t\t\t\t\tPlease enter a valid end time: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        else if(estime < 0 || estime > 2400){
            cout << "\t\t\t\t\tInvalid input!"<<endl;
            cout<<"\t\t\t\t\tPlease enter a valid end time: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        break;
    }

    new_etime = to_string(estime);

    cout << "\t\t\t\t\tEnter court price: ";
    while(!(cin >> new_cprice) || new_cprice < 1){
        cout << "\t\t\t\t\tInvalid input!!!";
        cout << "\n\t\t\t\t\tEnter a valid court price: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // Hash table for storing list of courts
    unordered_map<string, Court> courts;

    Court newCourt;

    fstream courtFile;
    try{
        // Read Court.txt file and store the contents into the hash table
        courtFile.open("Court.txt", ios::in);
        if (!courtFile.is_open()) {
            throw runtime_error("Error opening Court.txt file");
        }
        while(!courtFile.eof()){
            getline(courtFile, court_id, '|');
            getline(courtFile, start_time, '|');
            getline(courtFile, end_time, '|');

            // convert the string to a double before storing it in the court_price variable
            string court_price_string;
            getline(courtFile, court_price_string, '|');
            stringstream(court_price_string) >> court_price;

            // convert the string to a bool before storing it in the court_avail variable
            string court_avail_string;
            getline(courtFile, court_avail_string);
            stringstream(court_avail_string) >> court_avail;

            newCourt.court_id = court_id;
            newCourt.start_time = start_time;
            newCourt.end_time = end_time;
            newCourt.court_price = court_price;
            newCourt.court_avail = court_avail;
            courts.insert(make_pair(newCourt.court_id, newCourt));
        }

        courtFile.close();
        courts.erase("");

        // Check if the court id is existed in the record
        unordered_map<string, Court>:: iterator it;
        it = courts.find(new_cid);

        if(it != courts.end()){
            // If exist, prompt error message
            cout << "\n\t\t\t\t\tCourt ID " << new_cid << " is already existed in the record. Please try again" << endl;
        }else{
            // If not exist, add new court into Court.txt file
            courtFile.open("Court.txt", ios::app);
            if (!courtFile.is_open()) {
                throw runtime_error("Error opening Court.txt file");
            }
            courtFile << new_cid << '|' << new_stime << '|' << new_etime << '|' << new_cprice << '|'<< court_avail << "\n";
            courtFile.close();

            // Add new court into Hash Table
            newCourt.court_id = new_cid;
            newCourt.start_time = new_stime;
            newCourt.end_time = new_etime;
            newCourt.court_price = new_cprice;
            courts.insert(make_pair(newCourt.court_id, newCourt));

            cout << "\n\t\t\t\t\tCourt " << new_cid << " is added successfully" << endl;
        }
    }catch(const exception& e){
        // print an error message
        cerr << e.what() << endl;
    }
}

void Court::removeCourt(){

    string search_id;
    // Hash table for storing list of courts
    unordered_map<string, Court> courts;
    unordered_map<string, Court>:: iterator it;
    unordered_map<string, Court>:: iterator i;
    fstream courtFile;
    Court curCourt;

    try{
        // Note to self: create a function to load the file -> can be reuse in diff func (if have enof time)
        // Read Court.txt file and store the contents into the hash table
        courtFile.open("Court.txt", ios::in);
        if (!courtFile.is_open()) {
            throw runtime_error("Error opening Court.txt file");
        }
        while(!courtFile.eof()){
            getline(courtFile, court_id, '|');
            getline(courtFile, start_time, '|');
            getline(courtFile, end_time, '|');

            // convert the string to a double before storing it in the court_price variable
            string court_price_string;
            getline(courtFile, court_price_string, '|');
            stringstream(court_price_string) >> court_price;

            // convert the string to a bool before storing it in the court_avail variable
            string court_avail_string;
            getline(courtFile, court_avail_string);
            stringstream(court_avail_string) >> court_avail;

            curCourt.court_id = court_id;
            curCourt.start_time = start_time;
            curCourt.end_time = end_time;
            curCourt.court_price = court_price;
            curCourt.court_avail = court_avail;
            courts.insert(make_pair(curCourt.court_id, curCourt));
        }
        courtFile.close();
        courts.erase("");

        cout << "\n\t\t\t\t\tEnter Court ID: ";
        cin >> search_id;
        // Change Court ID to uppercase
        for (char& c : search_id) {
            c = toupper(c);
        }

        it = courts.find(search_id);

        if(it != courts.end()){
            // If exist, prompt message to confirm remove court
            cout << "\n\t\t\t\t\tCourt " << search_id << " found." << endl;
            char ch;
            do{
                cout << "\n\t\t\t\t\tAre you sure you want to remove this court? [Y/n]: ";
                cin >> ch;
                ch = tolower(ch);
            }while(ch!='y' && ch !='n');

            if(ch=='y'){
                // Remove the selected court from Hash Table
                courts.erase(search_id);

                // Store current contents in Hash Table to .txt file
                courtFile.open("Court.txt", ios::out);
                if (!courtFile.is_open()) {
                    throw runtime_error("Error opening Court.txt file");
                }
                for (i = courts.begin(); i != courts.end(); i++){
                    const Court& court = i->second;
                    courtFile << court.court_id << '|' << court.start_time << '|' << court.end_time << '|' << court.court_price << '|'<< court.court_avail << "\n";
                }
                courtFile.close();
                cout << "\n\t\t\t\t\t" << search_id << " is removed successfully."  << endl;

            }else{
                cout << "\n\t\t\t\t\tCourt " << search_id << " is not removed." << endl;
            }
        }else{
            cout << "\n\t\t\t\t\tCourt " << search_id << " does not exist. Try again!" << endl;
        }
    }catch(const exception& e){
        // print an error message
        cerr << e.what() << endl;
    }
}

void Court::editCourt(){
    string edit_id, edit_stime, edit_etime;
    double edit_cprice;
    bool edit_avail;
    // Hash table for storing list of courts
    unordered_map<string, Court> courts;
    unordered_map<string, Court>:: iterator it;
    unordered_map<string, Court>:: iterator i;
    fstream courtFile;
    Court curCourt;

    try{
        // Read Court.txt file and store the contents into the hash table
        courtFile.open("Court.txt", ios::in);
        if (!courtFile.is_open()) {
            throw runtime_error("Error opening Court.txt file");
        }
        while(!courtFile.eof()){
            getline(courtFile, court_id, '|');
            getline(courtFile, start_time, '|');
            getline(courtFile, end_time, '|');

            // convert the string to a double before storing it in the court_price variable
            string court_price_string;
            getline(courtFile, court_price_string, '|');
            stringstream(court_price_string) >> court_price;

            // convert the string to a bool before storing it in the court_avail variable
            string court_avail_string;
            getline(courtFile, court_avail_string);
            stringstream(court_avail_string) >> court_avail;

            curCourt.court_id = court_id;
            curCourt.start_time = start_time;
            curCourt.end_time = end_time;
            curCourt.court_price = court_price;
            curCourt.court_avail = court_avail;
            courts.insert(make_pair(curCourt.court_id, curCourt));
        }
        courtFile.close();
        courts.erase("");

        cout << "\n\t\t\t\t\tEnter Court ID: ";
        cin >> edit_id;
        // Change Court ID to uppercase
        for (char& c : edit_id) {
            c = toupper(c);
        }

        it = courts.find(edit_id);

        if(it != courts.end()){
            // If exist, prompt message to confirm edit court
            cout << "\n\t\t\t\t\tCourt " << edit_id << " found." << endl;
            char ch;
            do{
                cout << "\n\t\t\t\t\tAre you sure you want to edit this court? [Y/n]: ";
                cin >> ch;
                ch = tolower(ch);
            }while(ch!='y' && ch !='n');

            if(ch=='y'){
                // Edit the selected court
                const Court& court = it->second;

                cout << "\n\t\t\t\t\tEnter start time: ";
                cin >> edit_stime;

                cout << "\n\t\t\t\t\tEnter end time: ";
                cin >> edit_etime;

                cout << "\n\t\t\t\t\tEnter court price: ";
                cin >> edit_cprice;

                while(true){
                    cout << "\n\t\t\t\t\tEnter court price: ";
                    cin >> edit_cprice;

                    if(cin.fail()){
                        cout<<endl;
                        cout << "\t\t\t\t\tInvalid input!"<<endl;
                        cout<<"\t\t\t\t\tPlease enter a valid court price: ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        continue;
                    }
                    else if(edit_cprice < 1.00){
                        cout << "\t\t\t\t\tInvalid input!"<<endl;
                        cout<<"Court price must be at least $1.00. Please enter a valid court price: ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        continue;
                    }
                    break;
                }


                cout << "\n\t\t\t\t\tEnter court availability (0 - Not Available, 1 - Available): ";
                cin >> edit_avail;

                courts.at(edit_id).start_time = edit_stime;
                courts.at(edit_id).end_time = edit_etime;
                courts.at(edit_id).court_price = edit_cprice;
                courts.at(edit_id).court_avail = edit_avail;

                // Update edited contents in Hash Table to .txt file
                courtFile.open("Court.txt", ios::out);
                if (!courtFile.is_open()) {
                    throw runtime_error("Error opening Court.txt file");
                }
                for (i = courts.begin(); i != courts.end(); i++){
                    const Court& court = i->second;
                    courtFile << court.court_id << '|' << court.start_time << '|' << court.end_time << '|' << court.court_price << '|'<< court.court_avail << "\n";
                }
                courtFile.close();
                cout << "\n\t\t\t\t\t" << edit_id << " is edited successfully."  << endl;

            }else{
                cout << "\n\t\t\t\t\tCourt " << edit_id << " is not being edited." << endl;
            }
        }else{
            cout << "\n\t\t\t\t\tCourt " << edit_id << " does not exist. Try again!" << endl;
        }
    }catch(const exception& e){
        // print an error message and exit the program
        cerr << e.what() << endl;
    }
}

void Court::displayAllCourt(){

    fstream courtFile;
    try{
        courtFile.open("Court.txt", ios::in);
        if (!courtFile.is_open()) {
            throw runtime_error("Error opening Court.txt file");
        }else{
            //Display all the courts
            vector<Court> courts;
            cout << "\n\n\t\t\tCOURT ID" << "\t   TIME" << "\t\tPRICE (RM)" << "\t\tSTATUS" << endl;
            cout << "\t\t\t";
            for (int i=0; i<66; i++){
                cout << "-";
            }
            cout << endl;
            int line = 0;
            while(!courtFile.eof()){
                getline(courtFile, court_id, '|');
                getline(courtFile, start_time, '|');
                getline(courtFile, end_time, '|');

                // convert the string to a double before storing it in the court_price variable
                string court_price_string;
                getline(courtFile, court_price_string, '|');
                stringstream(court_price_string) >> court_price;

                // convert the string to a bool before storing it in the court_avail variable
                string court_avail_string;
                getline(courtFile, court_avail_string);
                stringstream(court_avail_string) >> court_avail;

                if (court_id != ""){
                    Court c;
                    c.court_id = court_id;
                    c.start_time = start_time;
                    c.end_time = end_time;
                    c.court_price = court_price;
                    c.court_avail = court_avail;

                    courts.push_back(c);
                }
            }

            courtFile.close();

            mergeSort(courts);

            courtFile.open("Court.txt", ios::in);

            if (!courtFile.is_open()) {
                throw runtime_error("Error opening Court.txt file");
            }

            for (const auto& c : courts) {
                string avail;
                if(c.court_avail){
                    avail = "Available";
                }else{
                    avail = "Not Available";
                }
                cout << fixed << setprecision(2);
                cout << "\t\t\t   "  << c.court_id << "\t\t" << c.start_time << " - " << c.end_time << "\t   " << c.court_price << "\t    " << avail << endl;
            }
        }
        courtFile.close();
        cout << endl;

    }catch(const exception& e){
        // print an error message and exit the program
        cerr << e.what() << endl;
    }
}

void Court::merge(vector<Court>& arr1, vector<Court>& arr2, vector<Court>& result) {
    // Initialize the indices for the two vectors and the result vector
    int i = 0, j = 0, k = 0;

    // Loop until one of the vectors is fully traversed
    while (i < arr1.size() && j < arr2.size()) {
        // Compare the start times of the courts at the current indices
        if (arr1[i].start_time < arr2[j].start_time) {
            // If the start time of the court in arr1 is smaller, add it to the result vector
            result[k] = arr1[i];
            i++;
        }
        else {
            // If the start time of the court in arr2 is smaller, add it to the result vector
            result[k] = arr2[j];
            j++;
        }
        k++;
    }

    // Add the remaining elements from arr1 (if any) to the result vector
    while (i < arr1.size()) {
        result[k] = arr1[i];
        i++;
        k++;
    }

    // Add the remaining elements from arr2 (if any) to the result vector
    while (j < arr2.size()) {
        result[k] = arr2[j];
        j++;
        k++;
    }
}

// Recursive function to sort a vector using merge sort
void Court::mergeSort(vector<Court>& arr) {
    // If the vector has more than one element, divide it into two halves and sort each half
    if (arr.size() > 1) {
        int mid = arr.size() / 2;
        vector<Court> left(arr.begin(), arr.begin() + mid);
        vector<Court> right(arr.begin() + mid, arr.end());
        mergeSort(left);
        mergeSort(right);

        // Merge the sorted halves into a single sorted vector
        vector<Court> result(arr.size());
        merge(left, right, result);

        // Copy the sorted vector back into the original vector
        arr = result;
    }
}

bool Court::searchCourt(string court_passed_id, Court& foundCourt) {
    // Hash table for storing list of courts
    unordered_map<string, Court> courts;

    // Read Court.txt file and store the contents into the hash table
    fstream courtFile;
    try{
        courtFile.open("Court.txt", ios::in);
        if (!courtFile.is_open()) {
            throw runtime_error("Error opening Court.txt file");
        }
        while(!courtFile.eof()){
            getline(courtFile, court_id, '|');
            getline(courtFile, start_time, '|');
            getline(courtFile, end_time, '|');

            // convert the string to a double before storing it in the court_price variable
            string court_price_string;
            getline(courtFile, court_price_string, '|');
            stringstream(court_price_string) >> court_price;

            // convert the string to a bool before storing it in the court_avail variable
            string court_avail_string;
            getline(courtFile, court_avail_string);
            stringstream(court_avail_string) >> court_avail;

            Court newCourt;
            newCourt.court_id = court_id;
            newCourt.start_time = start_time;
            newCourt.end_time = end_time;
            newCourt.court_price = court_price;
            newCourt.court_avail = court_avail;
            courts.insert(make_pair(newCourt.court_id, newCourt));
        }
        courtFile.close();
        courts.erase("");

        // Search the hash table for the court with the given ID
        unordered_map<string, Court>::iterator it;
        it = courts.find(court_passed_id);
        if (it == courts.end()) {
            // Court not found
            return false;
        } else {
            // Court found, store the court information in the foundCourt object
            foundCourt = it->second;
            return true;
        }
    }catch(const exception& e){
        // print an error message and exit the program
        cerr << e.what() << endl;
    }
}
/*
 * This method will be used during the court reservation and cancel reservation
 * It provide the following functionality:
 * - Change availability to 0 (Not Available) if current availability is 1 (Available)
 * - Change availability to 1 (Available) if current availability is 0 (Not Available)
 */
void Court::changeAvailability(string cid, bool cur_avail){
    bool new_avail;

    unordered_map<string, Court> courts;
    unordered_map<string, Court>:: iterator it;
    unordered_map<string, Court>:: iterator i;
    fstream courtFile;
    Court curCourt;

    try{
        // Read Court.txt file and store the contents into the hash table
        courtFile.open("Court.txt", ios::in);
        if (!courtFile.is_open()) {
            throw runtime_error("Error opening Court.txt file");
        }
        while(!courtFile.eof()){
            getline(courtFile, court_id, '|');
            getline(courtFile, start_time, '|');
            getline(courtFile, end_time, '|');

            // convert the string to a double before storing it in the court_price variable
            string court_price_string;
            getline(courtFile, court_price_string, '|');
            stringstream(court_price_string) >> court_price;

            // convert the string to a bool before storing it in the court_avail variable
            string court_avail_string;
            getline(courtFile, court_avail_string);
            stringstream(court_avail_string) >> court_avail;

            curCourt.court_id = court_id;
            curCourt.start_time = start_time;
            curCourt.end_time = end_time;
            curCourt.court_price = court_price;
            curCourt.court_avail = court_avail;
            courts.insert(make_pair(curCourt.court_id, curCourt));
        }
        courtFile.close();
        courts.erase("");

        it = courts.find(cid);

        if(it != courts.end()){
            const Court& court = it->second;
            if(cur_avail == 1){
                new_avail = 0;
            }else{
                new_avail = 1;
            }

            courts.at(cid).court_avail = new_avail;  // update the availability

            // Update edited contents in Hash Table to .txt file
            courtFile.open("Court.txt", ios::out);
            if (!courtFile.is_open()) {
                throw runtime_error("Error opening Court.txt file");
            }
            for (i = courts.begin(); i != courts.end(); i++){
                const Court& court = i->second;
                courtFile << court.court_id << '|' << court.start_time << '|' << court.end_time << '|' << court.court_price << '|'<< court.court_avail << "\n";
            }
            courtFile.close();
        }else{
            cout << "\n\t\t\t\t\tCourt " << cid << " does not exist. Try again!" << endl;
        }
    }catch(const exception& e){
        // print an error message and exit the program
        cerr << "Error opening Court.txt file: " << e.what() << endl;
    }
}
