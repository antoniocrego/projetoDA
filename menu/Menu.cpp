#include "Menu.h"

/**Constructor of the Menu, reads a file with buttons and adds them to a vector of strings
 * @brief Constructor of the Menu
 * @param path the path to the file containing the buttons of the menu
 */
Menu::Menu(string path)
{
    ifstream file(path);
    for (string button; getline(file, button);)
    {
        this->buttons.push_back(button);
    }
}

void Menu::clearScreen() const {
    for(int i = 0; i < 20; i++){
        cout << '\n';
    }
}

/**
 * @brief Adds a MenuItem to the menu's actions
 * @param menuItem
 * complexity O(1)
 */
void Menu::addMenuItem(MenuItem *menuItem)
{
    actions.push_back(menuItem);
}

/**
 * @return buttons
 */
vector<string> Menu::getButtons()
{
    return buttons;
}

/**
 * @brief Draws the menu
 * complexity O(N) being N the number of buttons
 */
void Menu::draw() const
{
    clearScreen();
    string display;
    display = " _____________________________________________ \n"
              "|                     Menu                    |\n"
              "|_____________________________________________|\n";

    for (int i = 0; i < this->buttons.size(); i++)
    {
        display += "|---------------------------------------------|\n";
        display += "| [" + to_string(i + 1) + "] " + this->buttons[i];
        for (int j = 0; j < (39 - this->buttons[i].length()); j++)
            display += " "; // adding spaces to format the menu
        if (i < 9)
            display += ' ';
        display += "|\n";
    }
    display += "|_____________________________________________|\n";
    display += "|<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<|\n";
    display += "|_____________________________________________|\n";
    cout << display << endl;
}

/**
 * @brief Will execute the action corresponding to the option chosen
 * @param option option chosen
 */
void Menu::doAction(int option)
{
    actions[option]->execute();
}

/**
 * @return the actions of the menu
 */
vector<MenuItem *> Menu::getActions()
{
    return actions;
}
