#ifndef AERIALTRANSPORTATION_PROGRAM_H
#define AERIALTRANSPORTATION_PROGRAM_H

#include "menu/Menu.h"
#include "network.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Program {
public:
    Program();
    int getCurrentPage()const;
    void setCurrentPage(int newCurrentpage);
    void draw();
    void run();
    void menu();
    void createMenu();
    void wait() const;
    void clear() const;


    template<typename type >
    bool getInput(type &input) const;

private:
    int currentMenuPage;
    vector<Menu> menus;
    Network network;
    string chooseStation(bool addStopButton);
    string chooseDistrict(bool addStopButton);
    string chooseMunicipality(bool addStopButton);

    Edge *chooseEdge(bool addStopButton);
};


#endif
