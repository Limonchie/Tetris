#include "GameField.h"
#include "GameController.h"
#include "MainMenu.h"
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace sf;

int main() {
    srand(time(0));

    RenderWindow window(VideoMode(450, 650), "Tetris");
    GameField field(15, 20, 30);
    MainMenu menu(window);

    menu.show(); // Показываем главное меню

    GameController controller(field, window);
    controller.run();

    return 0;
}