//Логика игры

#include "GameController.h"
#include "GameField.h"  
#include "Tetramino.h"  
#include "Score.h"      
#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace sf;

GameController::GameController(GameField& field, RenderWindow& window)
    : field(field), window(window), fallSpeed(0.5f) {
    spawnTetramino();
}

void GameController::run() {
    Clock clock;
    float time = 0.0f;

    while (window.isOpen()) {
        time += clock.restart().asSeconds();
        if (time > fallSpeed) {
            moveTetramino(0, 1);
            time = 0.0f;
        }

        handleInput();
        updateUI();
    }
}

void GameController::spawnTetramino() {
    static const vector<vector<vector<int>>> shapes = {
        {{1, 1, 1, 1}}, // I-фигура
        {{1, 1}, {1, 1}}, // O-фигура
        {{0, 1, 0}, {1, 1, 1}}, // T-фигура
        {{1, 1, 0}, {0, 1, 1}}, // Z-фигура
        {{0, 1, 1}, {1, 1, 0}}, // S-фигура
        {{1, 0, 0}, {1, 1, 1}}, // L-фигура
        {{0, 0, 1}, {1, 1, 1}}  // J-фигура
    };

    static const vector<Color> colors = {
        Color::Red, Color::Green, Color::Blue,
        Color::Yellow, Color::Magenta, Color::Cyan,
        Color::White
    };

    currentTetramino = make_unique<Tetramino>(shapes[rand() % shapes.size()], colors[rand() % colors.size()]);
    tetraminoX = field.getWidth() / 2 - 1;
    tetraminoY = 0;

    if (field.checkCollision(*currentTetramino, tetraminoX, tetraminoY)) {
        gameOver();
    }
}

void GameController::moveTetramino(int dx, int dy) {
    if (!field.checkCollision(*currentTetramino, tetraminoX + dx, tetraminoY + dy)) {
        tetraminoX += dx;
        tetraminoY += dy;
    }
    else if (dy == 1) {
        field.lockTetramino(*currentTetramino, tetraminoX, tetraminoY);
        int lines = field.clearLines();
        if (lines > 0) {
            score.addLines(lines);
            fallSpeed = 0.5f / score.getLevel();
        }
        spawnTetramino();
    }
}

void GameController::handleInput() {
    static Clock moveClock;
    static float moveDelay = 0.1f;

    if (Keyboard::isKeyPressed(Keyboard::Left)) {
        if (moveClock.getElapsedTime().asSeconds() > moveDelay) {
            moveTetramino(-1, 0);
            moveClock.restart();
        }
    }
    if (Keyboard::isKeyPressed(Keyboard::Right)) {
        if (moveClock.getElapsedTime().asSeconds() > moveDelay) {
            moveTetramino(1, 0);
            moveClock.restart();
        }
    }

    // Ускоренное падение при нажатии клавиши Down
    if (Keyboard::isKeyPressed(Keyboard::Down)) {
        fallSpeed = 0.1f; // Ускоренное падение
    }
    else {
        fallSpeed = 0.5f / score.getLevel(); // Восстанавливаем нормальную скорость
    }

    if (Keyboard::isKeyPressed(Keyboard::Up)) {
        static Clock rotateClock; // Таймер для вращений
        static float rotateDelay = 0.2f; // Задержка между вращениями (в секундах)

        if (rotateClock.getElapsedTime().asSeconds() > rotateDelay) { // Проверяем задержку
            currentTetramino->rotate(); // Вызываем rotate для текущей фигуры

            // Получаем вращённую форму фигуры
            const auto& rotatedShape = currentTetramino->getShape();

            // Корректируем позицию, если фигура вышла за границы поля
            if (tetraminoX < 0) {
                tetraminoX = 0;
            }
            if (tetraminoX + rotatedShape[0].size() > field.getWidth()) {
                tetraminoX = field.getWidth() - rotatedShape[0].size();
            }

            // Если вращение приводит к столкновению, отменяем его
            if (field.checkCollision(*currentTetramino, tetraminoX, tetraminoY)) {
                currentTetramino->undoRotation(); // Отменяем вращение
            }

            rotateClock.restart(); // Сбрасываем таймер после вращения
        }
    }

    // Обработка отпускания клавиш
    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            window.close();
        }
        if (event.type == Event::KeyReleased && event.key.code == Keyboard::Down) {
            fallSpeed = 0.5f / score.getLevel(); // Восстанавливаем нормальную скорость
        }
    }
}

void GameController::updateUI() {
    window.clear();
    field.draw(window);

    if (currentTetramino) {
        const auto& shape = currentTetramino->getShape();
        for (int y = 0; y < shape.size(); ++y) {
            for (int x = 0; x < shape[y].size(); ++x) {
                if (shape[y][x]) {
                    RectangleShape tile(Vector2f(field.getTileSize(), field.getTileSize()));
                    tile.setPosition((tetraminoX + x) * field.getTileSize(), (tetraminoY + y) * field.getTileSize());
                    tile.setFillColor(currentTetramino->getColor());
                    window.draw(tile);
                }
            }
        }
    }

    score.draw(window, field.getHeight(), field.getTileSize());
    window.display();
}

void GameController::gameOver() {
    Font font;
    if (!font.loadFromFile("Times New Roman - Italic.ttf")) {
        return;
    }

    Text text("Game Over!", font, 40);
    text.setFillColor(Color::Red);
    text.setPosition(100, 200);

    Text restartText("Press R to Restart", font, 20);
    restartText.setFillColor(Color::White);
    restartText.setPosition(100, 300);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::R) {
                // Сброс состояния игры
                currentTetramino = nullptr;
                tetraminoX = 0;
                tetraminoY = 0;
                score = Score();
                fallSpeed = 0.5f;
                spawnTetramino();
                return; // Вернуться к игре
            }
        }

        window.clear();
        window.draw(text);
        window.draw(restartText);
        window.display();
    }
}