#ifndef EQUIPMENT_HPP
#define EQUIPMENT_HPP
#include <queue>
#include <iostream>
#include <fstream>
using namespace std;

class Equipment{

private:
    struct Equip{
        string eq_id, eq_name, eq_type, eq_brand;
        double eq_price;
        Equip *nextEquip;
    };

public:
    Equipment();
    ~Equipment();

    int readFile(ifstream* file, Equip *equip);
    void viewEquip();
    void buyEquip();
    void payment(double eq_price);
    void addEquip();
    void removeEquip();
    void editEquip();
    void setEquip_id(Equip *equip);
    char setEquip_brand(Equip *equip);
    char setEquip_type(Equip *equip);
    void setEquip_price(Equip *equip);

};

#endif // EQUIPMENT_HPP


