#include "MainMenu.h"

void MainMenu::show() {
    Font font;

    if (!font.loadFromFile("Times New Roman - Italic.ttf")) {
        return;
    }

    Text title("Tetris", font, 60);
    title.setFillColor(Color::White);
    title.setPosition(100, 100);

    Text startText("Press space to play", font, 30);
    startText.setFillColor(Color::Green);
    startText.setPosition(100, 300);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space) {
                return; // Начинаем игру
            }
        }

        window.clear();
        window.draw(title);
        window.draw(startText);
        window.display();
    }
}