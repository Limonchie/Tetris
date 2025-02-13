#ifndef MAINMENU_H
#define MAINMENU_H

#include <SFML/Graphics.hpp>
#include <string>

using namespace std;
using namespace sf;

class MainMenu {
public:
    MainMenu(RenderWindow& window) : window(window) {}

    void show();

private:
    RenderWindow& window;
};

#endif // MAINMENU_H