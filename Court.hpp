#ifndef COURT_HPP
#define COURT_HPP
#include <vector>
#include <iostream>
using namespace std;

// Class for storing badminton court information
class Court{
    protected:
        string court_id;
        string start_time, end_time;
        bool court_avail;               // Court availability (true (1) if available, false (0) if reserved)
        double court_price;

    public:
        Court();
        ~Court();

        void addCourt();
        void removeCourt();
        void editCourt();
        void displayAllCourt();
        void changeAvailability(string edit_id, bool edit_avail);
        bool searchCourt(string court_passed_id, Court& foundCourt);
        void merge(vector<Court>& arr1, vector<Court>& arr2, vector<Court>& result);
        void mergeSort(vector<Court>& arr);

        // Getters
        string getCourtId() const{
            return court_id;
        }
        bool getCourtAvail() const{
            return court_avail;
        }
        double getCourtPrice() const{
            return court_price;
        }
        string getStartTime() const{
            return start_time;
        }
        string getEndTime() const{
            return end_time;
        }
};
#endif // COURT_HPP

