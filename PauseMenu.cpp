#include "PauseMenu.h"

PauseMenu::PauseMenu(RenderWindow& window) : window(window) {
    if (!font.loadFromFile("Times New Roman - Italic.ttf")) {
        return;
    }

    options.emplace_back("����������", font, 30);
    options.emplace_back("�����", font, 30);

    for (size_t i = 0; i < options.size(); ++i) {
        options[i].setFillColor(Color::White);
        options[i].setPosition(150, 250 + i * 50);
    }
}

void PauseMenu::drawMenu() {
    window.clear(Color::Black);

    Text title("�����", font, 40);
    title.setFillColor(Color::Yellow);
    title.setPosition(150, 150);
    window.draw(title);

    for (size_t i = 0; i < options.size(); ++i) {
        if (i == selectedOption) {
            options[i].setFillColor(Color::Green); // ��������� �������� ������
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
                selectedOption = max(0, selectedOption - 1); // ������������ �����
            }
            else if (event.key.code == Keyboard::Down) {
                selectedOption = min((int)options.size() - 1, selectedOption + 1); // ������������ ����
            }
            else if (event.key.code == Keyboard::Enter) {
                return; // ������������� ������
            }
            else if (event.key.code == Keyboard::Escape) {
                selectedOption = -1; // ������ �����
                return;
            }
        }
    }
}

int PauseMenu::show() {
    while (true) {
        handleInput();
        if (selectedOption == -1) {
            return -1; // ��������� � ����
        }
        else if (selectedOption >= 0 && selectedOption < options.size()) {
            return selectedOption; // ������� ��������� �����
        }
        drawMenu();
    }
}

int PauseMenu::getChoice() const {
    return selectedOption;
}