#include "PauseMenu.h"

PauseMenu::PauseMenu(RenderWindow& window) : window(window) {
    if (!font.loadFromFile("Times New Roman - Italic.ttf")) {
        return;
    }

    options.emplace_back("Продолжить", font, 30);
    options.emplace_back("Выйти", font, 30);

    for (size_t i = 0; i < options.size(); ++i) {
        options[i].setFillColor(Color::White);
        options[i].setPosition(150, 250 + i * 50);
    }
}

void PauseMenu::drawMenu() {
    window.clear(Color::Black);

    Text title("Пауза", font, 40);
    title.setFillColor(Color::Yellow);
    title.setPosition(150, 150);
    window.draw(title);

    for (size_t i = 0; i < options.size(); ++i) {
        if (i == selectedOption) {
            options[i].setFillColor(Color::Green); // Выделение текущего пункта
        }
        else {
            options[i].setFillColor(Color::White);
        }
        window.draw(options[i]);
    }

    window.display();
}

void PauseMenu::handleInput() {
    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            window.close();
        }
        if (event.type == Event::KeyPressed) {
            if (event.key.code == Keyboard::Up) {
                selectedOption = max(0, selectedOption - 1); // Переключение вверх
            }
            else if (event.key.code == Keyboard::Down) {
                selectedOption = min((int)options.size() - 1, selectedOption + 1); // Переключение вниз
            }
            else if (event.key.code == Keyboard::Enter) {
                return; // Подтверждение выбора
            }
            else if (event.key.code == Keyboard::Escape) {
                selectedOption = -1; // Отмена паузы
                return;
            }
        }
    }
}

int PauseMenu::show() {
    while (true) {
        handleInput();
        if (selectedOption == -1) {
            return -1; // Вернуться к игре
        }
        else if (selectedOption >= 0 && selectedOption < options.size()) {
            return selectedOption; // Вернуть выбранную опцию
        }
        drawMenu();
    }
}

int PauseMenu::getChoice() const {
    return selectedOption;
}