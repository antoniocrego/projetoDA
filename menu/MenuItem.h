#ifndef AERIALTRANSPORTATION_MENUITEM_H
#define AERIALTRANSPORTATION_MENUITEM_H

#include "../Network.h"

using namespace std;

class MenuItem
{
protected:
    /** @var menu we are currently in*/
    int *currMenuPage;
    /** @var pointer to the program's database*/
    Network *network;

public:
    MenuItem(int &currMenuPage, Network &network);
    virtual void execute() = 0;
};

#endif
