#include<cstdlib>
#include<iostream>
#include<string>

using namespace std;

#ifndef RESERVATION_HPP
#define RESERVATION_HPP
#include "Membership.hpp"

class Reservation{
    protected:
        string name, phone_number, court_id;
        string start_time, end_time;
        string order_id;
        double price;
        int year, month, day, file_type;

    public:
        Reservation();
        ~Reservation();

        void setName();
        void setPhonenumber();
        string getName();
        string getPhonenumber();
        void payment(double pay);
        void add_reserve();
        void cancel_sales(string cancel_id);
        void cancel_reservation();
        void totalSalesFrame();
        void displayTotal();
        void displayDetails();

        string found;
        int line;
};
#endif

