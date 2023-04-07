#ifndef PROJETO_SCHEDULE_MENU_H
#define PROJETO_SCHEDULE_MENU_H

#include <vector>
#include <fstream>
#include <iostream>
#include <unordered_set>

using namespace std;

class Menu {
public:
    Menu(string file_, string title);
    Menu(vector<string> options, string title);
    Menu(unordered_set<string> options, string title);
    vector<string> getButtons() const;
    int getOption() const;
    void addButton(string button);
    void setButtons(vector<string> buttons_);
    void draw();
    void clear() const;
private:
    vector<string> buttons;
    int option;
    string title;
};


#endif //PROJETO_SCHEDULE_MENU_H
