#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;
using namespace sf;

class PauseMenu {
public:
    PauseMenu(RenderWindow& window);
    int show();
    int getChoice() const; // ���������� ��������� ����� (0 - ����������, 1 - �����)

private:
    RenderWindow& window;
    Font font;
    vector<Text> options;
    int selectedOption = 0;

    void drawMenu();
    void handleInput();
};

#endif // PAUSEMENU_H