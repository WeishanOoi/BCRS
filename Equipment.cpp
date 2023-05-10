#include <iostream>
#include <iomanip>
#include <limits>
#include "Equipment.hpp"
using namespace std;

Equipment::Equipment(){
}

Equipment::~Equipment(){
}

int Equipment::readFile(ifstream* file, Equip *equip){
    Equip *temp = equip; // create a temp pointer
    string temps;
    double tempd, size=0;

    // skip the header
    *file >> temps;
    *file >> temps;
    *file >> temps;
    *file >> temps;
    //*file >> temps;

    while (*file >> temps){ // creating new equipments until the end of the file
        temp -> eq_id = temps;

        *file >> temps;
        temp -> eq_brand = temps;

        *file >> temps;
        temp -> eq_type = temps;

        *file >> tempd;
        temp -> eq_price = tempd;

        Equip *newEquip = new Equip;
        temp -> nextEquip = newEquip;
        temp = newEquip;

        size++;
    }

    temp -> nextEquip = NULL;
    delete temp;

    return size;
}

void Equipment::viewEquip(){
    Equip *equip = new Equip;
    ifstream file("Equipment.txt");
    int size = readFile(&file, equip);

    system("CLS");
    cout << "\t\t\t=====================================================\n"
         << "\t\t\t\tVIEW ALL EXISTING EQUIPMENTS\t\t\t\n"
         << "\t\t\t=====================================================\n\n";

    cout << "\t\t\t--------------------------------------------------------\n"
         << "\t\t\t" << "EQ_ID" << setw(15) << "EQ_BRAND" << setw(20) << "EQ_TYPE" << setw(20) << "EQ_PRICE (RM)" << endl
         << "\t\t\t--------------------------------------------------------\n";

    for (int i = 0; i < size; i++){
        cout << "\t\t\t" << equip -> eq_id << setw(15) << equip -> eq_brand << setw(20) << equip -> eq_type << setw(17) << equip -> eq_price << endl;
        equip = equip -> nextEquip;
    }

    cout << endl << endl;
}

void Equipment::buyEquip(){
    time_t now = time(0);
    //char* dt = ctime(&now);
    tm *ltime = localtime(&now);

    srand(time(0));
    ifstream file("Equipment.txt");

    // Allocate memory for a new Equipment object
    Equip *equip = new Equip;

    int size = readFile(&file, equip);
    ofstream tempf("temp.txt");

    // Write the header line to the temporary file
    tempf << "EQ_ID" << " " << "EQ_BRAND" << " " << "EQ_TYPE" << " " << "EQ_PRICE" << " \n";

    // Prompt the user for eq_id they would like to buy
    string resp_id;
    bool id_found = false;
    Equip *ptr = new Equip; //pointer to traverse file

    while(1){
        cout << "\n\t\t\tEnter the ID for the equipment you would like to buy: ";
        cin >> resp_id;
        ptr = equip;
        for (int i = 0; i < size; i++){
            if (ptr -> eq_id == resp_id){
                id_found = true;
                break;
            }
            ptr = ptr -> nextEquip;
        }

        if(id_found){
            *equip = *ptr;
            break;
        }
        else{
            cout << "\t\t\t\tEquipment ID not found! Please Try again";
            cout << endl;
        }
    }

    //User make payment for equipment
    double price;
    for (int i = 0; i < size; i++){
            if (ptr -> eq_id == resp_id){
                price = ptr -> eq_price;
                break;
            }
        }
    payment(price);

    int order_id = (rand() % 99999) + 10000;
    ofstream salesFile;
    salesFile.open("sales.txt", ios::app);
    salesFile << 1900+ltime->tm_year << '|' << 1+ltime->tm_mon << '|' << ltime->tm_mday << '|' <<
                order_id << '|' << price << '|' << 2 << endl;
    salesFile.close();

    ptr = NULL;
    ptr = new Equip;
    file.close();

    //to remove equipment chosen by user
    file.open("Equipment.txt", ios::out);
    size = readFile(&file, ptr);

    for (int i = 0; i < size; i++){
        if (equip -> eq_id == ptr -> eq_id){
            ptr = ptr -> nextEquip;
            continue;
        }

        else{
            tempf << ptr -> eq_id << " " << ptr -> eq_brand << " " << ptr -> eq_type << " " << ptr -> eq_price;
        }

        if (i != size-1){
            tempf << "\n";
        }

        ptr = ptr -> nextEquip;
    }

    file.close();
    tempf.close();
    remove ("Equipment.txt");
    rename("temp.txt", "Equipment.txt");

    cout << endl << endl;
    cout << "\t\t\tBuying An Equipment: COMPLETE\n";
}

void Equipment::payment(double eq_price){
    double cash;
    cout << "\n\t\t\tThe amount you need to pay is : RM " << eq_price << endl;
    cout << "\t\t\tCash          : " << "RM ";
    //cin >> cash;
//    while (cash < eq_price)
//        {
//            cout << "\n\t\t\tSorry! Your cash is insufficient, please pay the sufficient amount of cash! " << endl;
//            cout << "\t\t\tCash : " << "RM ";
//            cin >> cash;
//        }

    while(true){
        //cout << "\n\tCash          : " << "RM ";
        cin >> cash;

        if(cin.fail()){
            cout<<endl;
            cout << "\n\t\t\tSorry! Your cash is insufficient, please pay the sufficient amount of cash! " << endl;
            cout << "\t\t\tCash : " << "RM ";
            cin >> cash;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        else if(cash < eq_price){
            cout << "\n\t\t\tSorry! Your cash is insufficient, please pay the sufficient amount of cash! " << endl;
            cout << "\t\t\tCash : " << "RM ";
            cin >> cash;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        break;
    }
        double remaining = cash - eq_price;
        cout<< setprecision(2) << "\n\t\t\tThe change is RM " << remaining << ", Thank you!" << endl;
}

void Equipment::addEquip(){
    ofstream file("Equipment.txt", ios::app);
    Equip *equip = new Equip;
    system("CLS");
    cout << "\t\t\t=================================================\n"
         << "\t\t\t\tADDING NEW EQUIPMENT\t\t\t\n"
         << "\t\t\t=================================================\n\n";

    setEquip_id(equip);
    setEquip_price(equip);

    file << "\n" << equip -> eq_id << " " << equip -> eq_brand << " " << equip -> eq_type << " " << equip -> eq_price;
    file.close();

    cout << endl << endl;
    cout << "\t\t\tAdding New Equipment: COMPLETE\n";
}

void Equipment::removeEquip(){
    ifstream file("Equipment.txt");
    Equip *equip = new Equip;
    string resp_id;
    bool id_found = false;
    system("CLS");
    cout << "\t\t\t=====================================================\n"
         << "\t\t\t\tREMOVING EXISTING EQUIPMENT\t\t\t\n"
         << "\t\t\t=====================================================\n\n";

    Equip *ptr = new Equip;
    int size = readFile(&file, equip);
    ofstream tempf("temp.txt");
    tempf << "EQ_ID" << " " << "EQ_BRAND" << " " << "EQ_TYPE" << " " << "EQ_PRICE" << " \n";

    while(1){
        cout << "\n\t\t\tEnter the ID for the equipment you would like to remove : ";
        cin >> resp_id;
        ptr = equip;
        for (int i = 0; i < size; i++){
            if (ptr -> eq_id == resp_id){
                id_found = true;
                break;
            }
            ptr = ptr -> nextEquip;
        }

        if(id_found){
            *equip = *ptr;
            break;
        }
        else{
            cout << "\t\t\t\tEquipment ID not found! Please Try again";
            cout << endl;
        }
    }

    ptr = NULL;
    ptr = new Equip;
    file.close();
    file.open("Equipment.txt", ios::out);
    size = readFile(&file, ptr);

    for (int i = 0; i < size; i++){
        if (equip -> eq_id == ptr -> eq_id){
            ptr = ptr -> nextEquip;
            continue;
        }

        else{
            tempf << ptr -> eq_id << " " << ptr -> eq_brand << " " << ptr -> eq_type << " " << ptr -> eq_price;
        }

        if (i != size-1){
            tempf << "\n";
        }

        ptr = ptr -> nextEquip;
    }

    file.close();
    tempf.close();
    remove ("Equipment.txt");
    rename("temp.txt", "Equipment.txt");

    cout << endl << endl;
    cout << "\t\t\tRemoving Existing Equipment: COMPLETE\n";
}

void Equipment::editEquip(){
    ifstream file("Equipment.txt");
    Equip *equip = new Equip;
    string resp_id;
    bool id_found = false;
    system("CLS");
    cout << "\t\t\t=====================================================\n"
         << "\t\t\t\tEDITING EXISTING EQUIPMENT'S DETAILS\t\t\t\n"
         << "\t\t\t=====================================================\n\n";

    Equip *ptr = new Equip;
    int size = readFile(&file, equip);
    ofstream tempf("temp.txt");
    tempf << "EQ_ID" << " " << "EQ_BRAND" << " " << "EQ_TYPE" << " " << "EQ_PRICE" << " \n";

    while(1){
        cout << "\n\t\t\tEnter the ID for the equipment you would like to edit its price : ";
        cin >> resp_id;
        ptr = equip;
        for (int i = 0; i < size; i++){
            if (ptr -> eq_id == resp_id){
                id_found = true;
                break;
            }
            ptr = ptr -> nextEquip;
        }

        if(id_found){
            *equip = *ptr;
            break;
        }
        else{
            cout << "\t\t\t\tEquipment ID not found! Please Try again";
            cout << endl;
        }
    }

    cout << "\n\t\t\tThe original price for equipment ID " << equip -> eq_id << " is RM" << equip -> eq_price;

    //cout << "\n\t\t\tEnter the new price for equipment ID " << equip -> eq_id << ": RM";
    //cin >> equip -> eq_price;
    setEquip_price(equip);

    ptr = NULL;
    ptr = new Equip;
    file.close();
    file.open("Equipment.txt", ios::out);
    size = readFile(&file, ptr);

    for (int i = 0; i < size; i++){
        if (ptr -> eq_id == equip -> eq_id){
            tempf << ptr -> eq_id << " " << ptr -> eq_brand << " " << ptr -> eq_type << " " << equip -> eq_price;
        }

        else{
            tempf << ptr -> eq_id << " " << ptr -> eq_brand << " " << ptr -> eq_type << " " << ptr -> eq_price;
        }

        if (i != size-1){
            tempf << "\n";
        }

        ptr = ptr -> nextEquip;
    }

    file.close();
    tempf.close();
    remove ("Equipment.txt");
    rename("temp.txt", "Equipment.txt");

    cout << endl << endl;
    cout << "\t\t\tEditing Existing Equipment's Detail: COMPLETE\n";
}

void Equipment::setEquip_id(Equip *equip){
    Equip *temp = new Equip;
    string brandstr, typestr, counterstr;

    //to generate equipment's ID
    ifstream file("Equipment.txt");
    int counter = readFile(&file, temp);

    brandstr = setEquip_brand(equip);
    typestr = setEquip_type(equip);
    counterstr = to_string(counter);
    equip -> eq_id = brandstr + typestr + counterstr;
    cout << "\t\t\tThe equipment's ID is " << equip -> eq_id;
    file.close();
}

char Equipment::setEquip_brand(Equip *equip){
    bool br_exist = false; // to check the equipment's brand to create the equipment's ID
    char brand;
    string brandstr;

    cout << "\t\t\tEnter the equipment's brand, Yonex[Y] or Perfly[P]: ";
    cin >> brand;
    brand = toupper(brand);

    //check the equipment's brand
    while (!br_exist){
        if (brand == 'Y' || brand == 'P'){
            if(brand == 'Y'){
                equip -> eq_brand = "Yonex";
                br_exist = true;
                break;
            }
            if(brand == 'P'){
                equip -> eq_brand = "Perfly";
                br_exist = true;
                break;
            }
        }

        else{
            cout << endl;
            cout << "\t\t\tEnter a valid equipment's brand, Yonex[Y] or Perfly[P]: ";
            cin >> brand;
            brand = toupper(brand);
        }
    }

    return brand;
}

char Equipment::setEquip_type(Equip *equip){
    bool ty_exist = false; // to check the equipment's type to create the equipment's ID
    char type;
    string typestr;

    cout << "\t\t\tEnter the equipment's type, Racket[R] or Shuttlecock[S]: ";
    cin >> type;
    type = toupper(type);

    //check the equipment's type
    while (!ty_exist){
        if (type == 'R' || type == 'S'){
            if(type == 'R'){
                equip -> eq_type = "Racket";
                ty_exist = true;
                break;
            }
            if(type == 'S'){
                equip -> eq_type = "Shuttlecock";
                ty_exist = true;
                break;
            }
        }

        else{
            cout << endl;
            cout << "\t\t\tEnter a valid equipment's type, Racket[R] or Shuttlecock[S]: ";
            cin >> type;
            type = toupper(type);
        }
    }

    return type;
}

void Equipment::setEquip_price(Equip *equip){
    cout << "\n\t\t\tEnter the equipment's price: RM";
    //cin >> equip -> eq_price;

    while(true){
        //cout << "\n\tCash          : " << "RM ";
        cin >> equip -> eq_price;

        if(cin.fail()){
            cout<<endl;
            cout << "\n\t\t\tInvalid ! Enter the equipment's price: RM";
            cin >> equip -> eq_price;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        break;
    }
}

