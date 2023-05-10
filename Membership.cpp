#include <iostream>
#include <ctime>
#include <fstream>
#include <conio.h>
#include <iomanip>
#include <stdio.h>
#include "Membership.hpp"

using namespace std;
time_t t = time(NULL);  //Source: https://stackoverflow.com/questions/58151350/more-elegant-way-to-get-the-current-year-in-c
tm* timePtr = localtime(&t);

Membership::Membership(){}

Membership::~Membership(){}

int Membership::readFile(ifstream* file,Member *member){
    Member *temp = member; // create a temp pointer
    string temps;
    int tempi, size=0;

    // skip the header
    *file >> temps;
    *file >> temps;
    *file >> temps;
    *file >> temps;
    *file >> temps;
    *file >> temps;
    *file >> temps;
    *file >> temps;
    *file >> temps;

    while (*file >> temps){ // creating new members until the end of the file
        temp -> fname = temps;

        *file >> temps;
        temp -> lname=temps;

        *file >> temps;
        temp -> email=temps;

        *file >> temps;
        temp -> phone_number=temps;

        *file >> temps;
        temp -> icno=temps;

        *file >> temps;
        temp -> acc_num=temps;

        *file >> temps;
        temp -> password=temps;

        *file >> tempi;
        temp -> valid_month=tempi;

        *file >> tempi;
        temp -> valid_year = tempi;

        Member *newMember = new Member;
        temp -> nextMember = newMember;
        temp = newMember;

        size++;
    }

    temp -> nextMember = NULL;
    delete temp;

    return size;
}

void Membership::setName(Member *m){
    cout << "\n\t\t\t\tEnter your first name: ";
    cin >> m ->fname;
    cout << "\n\t\t\t\tEnter your last name : ";
    cin >> m -> lname;
}

void Membership::setPhonenumber(Member *m){
    bool length, format; // to check the length and format of the phone number
    cout << "\n\t\t\t\tEnter your phone number: ";
    cin >> m -> phone_number;

    while (1){
        if (m -> phone_number.length() == 10 || m -> phone_number.length() == 11){ //check the length of phone number
            length = true;
        }

        for (int i = 0; i < m -> phone_number.length(); i++){
            if (isdigit(m -> phone_number[i])){ // check whether the phone number consist of all digits
                format = true;
            }
            else{
                format = false;
                break;
            }
        }

        if (length && format){
            break;
        }
        else{
            cout << endl;
            cout << "\t\t\t\tEnter a valid phone number: ";
            cin >> m -> phone_number;
        }
    }
}

void Membership::setIC(Member *m){
    bool length, format, exist; // to check the length and format of the ic number
    Member *existmember = new Member;
    ifstream file("Membership.txt");
    int size=readFile(&file, existmember);

    cout << "\n\t\t\t\tEnter your IC Number: ";
    cin >> m -> icno;

    while (1){
        Member *temp = existmember;
        exist = false;

        if (m -> icno.length() == 12){ //check the length of ic number
            length = true;
        }
        else{
            length = false;
        }

        for (int i = 0; i < m -> icno.length(); i++){
            if (isdigit(m -> icno[i])){ // check whether the phone number consist of all digits
                format = true;
            }
            else{
                format = false;
                break;
            }
        }

        for (int i = 0; i < size; i++){
            if (m -> icno == temp ->icno){
                exist = true;
            }
            temp = temp -> nextMember;
        }

        if (length && format && !exist){
            break;
        }

        else if (format == false || length == false){
            cout << endl;
            cout << "\t\t\t\tEnter a valid IC number: ";
            cin >> m -> icno;
        }

        else{
            cout << endl;
            cout << "\t\t\t\tIC Number already exist in database!\n\t\t\t\tEnter new IC Number: ";
            cin >> m ->icno;
        }
    }
}

void Membership::setEmail(Member *m){
    bool format; // to check the format of the email
    cout << "\n\t\t\t\tEnter your email: ";
    cin >> m -> email;

    while (1){
        for (int i = 0; i < m -> email.length(); i++){
            if (m -> email[i] == '@'){ // check whether the email consist of "@"
                format = true;
                break;
            }
            else{
                format = false;
            }
        }

        if (format){
            break;
        }
        else{
            cout << endl;
            cout << "\t\t\t\tEnter a valid email: ";
            cin >> m -> email;
        }
    }
}

void Membership::setAccNum(Member *m){
    srand(time(0));
    int AccNum1 = (rand() % 999999) + 100000; // random number for account
    m -> acc_num = to_string(AccNum1);
}

void Membership::setPassword(Member *m){
    char password_1[50], password[50];

    cout << "\t\t\tENTER YOUR PASSWORD : ";
    int a = 0;
    while(password[a - 1] != '\r'){
        password[a] = getch();
        if(password[a-1]!='\r'){
            cout << "*";
        }
        a++;
    }
    password[a-1] = '\0';
    string pw = password;

    cout << "\n\t\t\tREENTER YOUR PASSWORD :";
    //cin >> password_1;
    a = 0;
    while(password_1[a - 1] != '\r'){
        password_1[a] = getch();
        if(password_1[a-1]!='\r'){
            cout << "*";
        }
        a++;
    }
    password_1[a-1] = '\0';
    string pw1 = password_1;

    while (pw1 != pw){
        cout << "\n\t\t\tYour password does not match. Try again !!"
             << "\n\n\t\t\tENTER YOUR PASSWORD: ";
        a = 0;
        while(password[a - 1] != '\r'){
            password[a] = getch();
            if(password[a-1]!='\r'){
                cout << "*";
            }
            a++;
        }
        password[a-1] = '\0';
        pw = password;

        cout << "\n\t\t\tREENTER YOUR PASSWORD: ";
        a = 0;
        while(password_1[a - 1] != '\r'){
            password_1[a] = getch();
            if(password_1[a-1]!='\r'){
                cout << "*";
            }
            a++;
        }
        password_1[a-1] = '\0';
        pw1 = password_1;
    }

    m ->password = pw1;
}

void Membership::setMonth(Member *m){
    m -> valid_month = timePtr->tm_mon + 1;
}

void Membership::setYear(Member *m){
    m -> valid_year = timePtr->tm_year + 1900 + 1;  //give extra one year upon registration for validity
}

void Membership::login(Member *m){
    try{
        ifstream file("Membership.txt");
        if (!file.is_open()) {
            throw runtime_error("Error opening Court.txt file");
        }

        else{
            string acc_input, temp_pass;
            bool acc_found = false;
            char pass[50];
            int login_attempt = 1, i = 0;

            int size=readFile(&file, m);

            while(1){
                cout << "\n\t\t\t\t\tEnter your account number : ";
                cin >> acc_input;
                Member *temp = m;
                for (int i = 0; i < size; i++){
                    if (temp -> acc_num == acc_input){
                        acc_found = true;
                        break;
                    }
                    temp = temp -> nextMember;
                }

                if(acc_found){
                    *m = *temp;
                    break;
                }
                else{
                    cout << "\n\t\t\t\t\tAccount not found! Please Try again";
                    cout << endl;
                }
            }

            cout << "\n\t\t\t\t\tEnter your password: ";
            int a = 0;
            while(pass[a - 1] != '\r'){
                pass[a] = getch();
                if(pass[a-1]!='\r'){
                    cout << "*";
                }

                a++;
            }

            pass[a-1] = '\0';

            for (login_attempt = 1 ; login_attempt <= 2 ; login_attempt ++){
                if (pass == m -> password){
                    cout << "Login Successful !!!";
                    break;
                }

                cout << endl;
                cout << "Login Failed. Attempt " << login_attempt  << " of 3" << endl;
                cout << "Please re-enter Password: " ;
                int a = 0;
                while(pass[a - 1] != '\r'){
                    pass[a] = getch();

                    if(pass[a-1]!='\r'){
                        cout << "*";
                    }
                    a++;
                }

                pass[a-1] = '\0';

                if (pass == m -> password){
                    cout << "Login Successful !!!";
                        break;
                }
            }

            if (login_attempt == 3){
                cout << endl;
                cout << "Login Failed. Attempt 3 of 3" << endl;
            }
        }
    }catch(const exception& e){
        // print an error message and exit the program
        cerr << e.what() << endl;
    }
}

void Membership::newMember(){
    ofstream file("Membership.txt", ios::app);

    char resp;
    Member *member = new Member;

    system("CLS");
    cout << "\n\n\t\t\tWELCOME TO THE COURT !!\t\t\t\n\n"
            "\t\t\tWe are glad on your interest to be a part of our family\t\t\n\n";

    setName(member);
    setPhonenumber(member);
    setIC(member);
    setEmail(member);
    setMonth(member);
    setYear(member);

    while(1){
        system("CLS");
        cout << "\n\t-------------------------------------------------------------------------------------------------\n\n" <<
        setw(30)<< "\tHello Mr/MS , " << endl << endl <<
        setw(50)<< "Your First Name is : " << member -> fname << endl << endl <<
        setw(50)<< "Your Last Name is : " << member -> lname << endl << endl <<
        setw(50)<< "Your IC is : " << member -> icno << endl << endl <<
        setw(50)<< "Your Phone Number is : " << member -> phone_number << endl << endl <<
        setw(50)<< "Your Email is : " << member -> email << endl << endl
        << "\t --------------------------------------------------------------------------------------------------\n\n"
        << "\t\t\tWOULD YOU LIKE TO CONFIRM YOUR DETAILS [Y/N] : ";
        cin >> resp;
        resp = tolower(resp);

        while ((resp != 'y') && (resp != 'n') ){
            cout << "\n\t\t\t\t Enter a valid response: ";
            cin >> resp;
        }

        if (resp == 'n'){
            system("CLS");
            cout << "\n\t\t\t\tWHICH DATA YOU WOULD LIKE TO CHANGE :\t\t\n\n"
                 << "\t\t\t\t\t(A) NAME\n\n"
                 << "\t\t\t\t\t(B) IDENTIFICATION NUMBER\n\n"
                 << "\t\t\t\t\t(C) EMAIL ADDRESS\t\n\n"
                 << "\t\t\t\t\t(D) PHONE NUMBER\t\n\n"
                 << "\t\t\t\tEnter your response:" ;

            cin >> resp;
            resp = tolower(resp);

            while ((resp != 'a') &&  (resp != 'b') && (resp != 'c') && (resp != 'd')){
              cout << "\n\t\t\t\t\tEnter a valid response: ";
              cin >> resp;
            }

            switch(resp){
                case 'a':
                    setName(member);
                    break;
                case 'b':
                    setIC(member);
                    break;
                case 'c':
                    setEmail(member);
                    break;
                case 'd':
                    setPhonenumber(member);
                    break;
            }
        }

        else{
            break;
        }
    }

    system("CLS");
    cout << endl;
    setAccNum(member);

    cout <<setw(80)<< "\t\t--------------------------------------\t\t";
    cout << "\n\t\t\tYour Account Number is : |\t\t" << member -> acc_num << setw(18)<<"|\n";
    cout <<setw(80)<< "\t\t--------------------------------------\n\n";
    cout << "\t\t\tYou are required to set a password for your account:\n\n";

    setPassword(member);

    file << "\n" << member -> fname << " " << member -> lname << " " << member -> email << " " << member -> phone_number << " " <<
            member -> icno << " " << member -> acc_num << " " << member -> password << " " << member -> valid_month << " " << member ->valid_year;
    file.close();

    cout << endl << endl;
    cout << "\t\t\tYou are done with your account registration !!\n"
         << "\t\t\tNO FEES FOR NEW MEMBERS \n"
         << "\t\t\tOne point will be given for each ringgit in purchase\n"
         << "\t\t\tThere are alot of exciting rewards that you can claim using the points\n";

}

void Membership::renewMember(){
    try{
        ifstream file("Membership.txt");

        if (!file.is_open()) {
            throw runtime_error("Error opening Membership.txt file");

        }else{
            double pay, cash;
            int extend;
            char resp;
            time_t now = time(0);
            tm *ltime = localtime(&now);

            srand(time(0));

            Member *member = new Member;
            login(member);

            system("CLS");
            cout << endl << endl;
            cout << " Hello " << member -> fname << " " << member -> lname << " ,\n\n"
                 << " Your account is valid until " << member -> valid_month << " - " << member -> valid_year << endl << endl;

            if ((member -> valid_month <= timePtr->tm_year + 1900 ) && (member -> valid_year < (timePtr->tm_mon + 1))){
                cout << " YOUR ACCOUNT HAS EXPIRED !!!\n\n";
            }

            cout << " Select an option to extend your membership :- \n\n"
                 << "\t\t---------------\t\t----------------\t---------------\n"
                 << "\t\t/ (a) 1 years  /\t/  (b) 3 years  /\t/ (c) 5 years  /\n"
                 << "\t\t---------------\t\t----------------\t----------------\n\n";

            cout << " Your selection [ A, B, C ] = ";
            cin >> resp;
            resp = tolower(resp);

            while((resp != 'a') && (resp != 'b') && (resp != 'c')){
                cout << " Please select a correct option [ a, b, c] : ";
                cin >> resp;
            }

            switch(resp){
                case 'a':
                    extend = 1;
                    pay = 10;
                    break;
                case 'b':
                    extend = 3;
                    pay = 20;
                    break;
                case 'c':
                    extend = 5;
                    pay = 30;
                    break;
            }

            system("cls");
            cout << "\t=========================================================\n"
                 << "\t=                         RECEIPT                       =\n"
                 << "\t---------------------------------------------------------\n"
                 << "\t=                      COURT INVOICE                    =\n"
                 << "\t=========================================================\n\n" <<endl;

            if (extend == 1){
                cout << "\n\tYou have selected 1 Years to extend membership " << endl;
            }
            else if(extend == 3){
                cout << "\n\tYou have selected 3 Years to extend membership " << endl;
            }
            else{
                cout << "\n\tYou have selected 5 Years to extend membership " << endl;
            }

            cout << "\n\tThe amount you need to pay is : RM " << pay << endl;
            cout << "\n\tCash          : " << "RM ";
            //cin >> cash;

//            while (cash < pay)
//            {
//                cout << "\n\tSorry! Your cash is insufficient, please pay the sufficient amount of cash! " << endl;
//                cout << "\n\tCash : " << "RM ";
//                cin >> cash;
//            }

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
                else if(cash < pay){
                    cout << "\n\t\t\tSorry! Your cash is insufficient, please pay the sufficient amount of cash! " << endl;
                    cout << "\t\t\tCash : " << "RM ";
                    cin >> cash;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }
                break;
            }

            double remaining = cash - pay;
            cout<< setprecision(2) << "\n\tThe change is RM " << remaining << ", Thank you!\n" << endl;


            Member *temp = new Member;
            int size=readFile(&file, temp);

            ofstream tempf("temp.txt");
            tempf << "M_FNAME" << " " << "M_LNAME" << " " << "M_EMAIL" << " " << "M_PNUMBER" << " " << "M_ICNO" << " "
            << "M_ACCNUM" << " " << "M_PWORD" << " " << "M_VMONTH" << " " << "M_VYEAR" << " \n";
            for (int i = 0; i < size; i++){
                if (temp -> acc_num == member -> acc_num){
                    tempf << temp -> fname << " " << temp -> lname << " " << temp -> email << " " << temp -> phone_number << " "
                    << temp -> icno << " " << temp -> acc_num << " " << temp -> password << " " << temp -> valid_month << " " << member ->valid_year + extend;
                }
                else{
                    tempf << temp -> fname << " " << temp -> lname << " " << temp -> email << " " << temp -> phone_number << " "
                    << temp -> icno << " " << temp -> acc_num << " " << temp -> password << " " << temp -> valid_month << " " << member ->valid_year;
                }
                if (i != size-1){
                    tempf << "\n";
                }

                temp = temp -> nextMember;
            }

            file.close();
            tempf.close();
            remove ("Membership.txt");
            rename("temp.txt", "Membership.txt");

            int order_id = (rand() % 99999) + 10000;
            ofstream salesFile;
            salesFile.open("sales.txt", ios::app);
            salesFile << 1900+ltime->tm_year << '|' << 1+ltime->tm_mon << '|' << ltime->tm_mday << '|' <<
                        order_id << '|' << pay << '|' << 3 << endl;
            salesFile.close();
        }
    }catch(const exception& e){
        // print an error message and exit the program
        cerr << e.what() << endl;
    }
}

void Membership::infoMember(){
    Member *member = new Member;
    login(member);

    system("CLS");
    cout << "\n\n";
    cout << "\t\t\t\t=========================================================\n"
         << "\t\t\t\t=                  MEMBER INFORMATION                   =\n"
         << "\t\t\t\t=========================================================\n"
         << "\n\t\t\t\tAccount Number : " << member -> acc_num
         << "\n\t\t\t\tFirst Name     : " << member -> fname
         << "\n\t\t\t\tLast Name      : " << member -> lname
         << "\n\t\t\t\tPhone no.      : " << member -> phone_number
         << "\n\t\t\t\tE-mail         : " << member -> email
         << "\n\t\t\t\tIC Number      : " << member -> icno
         << "\n\t\t\t\tValid month    : " << member -> valid_month
         << "\n\t\t\t\tValid year     : " << member -> valid_year
         << "\n\t\t\t\t---------------------------------------------------------" << endl;
}
