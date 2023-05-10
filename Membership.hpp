#ifndef MEMBERSHIP_HPP
#define MEMBERSHIP_HPP
#include <limits>
#include <iostream>
#include <fstream>
using namespace std;

class Membership{
    private:
        struct Member{
            string fname;
            string lname;
            string email;
            string phone_number;
            string acc_num;
            string icno;
            string password;
            int valid_month;
            int valid_year;
            Member *nextMember;
        };

    public:
        Membership();
        ~Membership();
        Member *members = new Member;
        void setName(Member *m);
        void setIC(Member *m);
        void setAccNum(Member *m);
        void setPassword(Member *m);
        void setPhonenumber(Member *m);
        void setMonth(Member *m);
        void setYear(Member *m);
        void setEmail(Member *m);
        void newMember();
        void renewMember();
        void infoMember();
        void login(Member *m);
        int readFile(ifstream* file,Member *member);
};
#endif // MEMBERSHIP_HPP
