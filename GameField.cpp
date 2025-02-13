//Игровое поле

#include "GameField.h"

GameField::GameField(int width, int height, int tileSize)
    : width(width), height(height), tileSize(tileSize), field(height, vector<int>(width, 0)) {}

void GameField::draw(RenderWindow& window) const {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            RectangleShape tile(Vector2f(tileSize, tileSize));
            tile.setPosition(x * tileSize, y * tileSize);
            tile.setFillColor(field[y][x] ? Color::Cyan : Color::Black);
            window.draw(tile);
        }
    }
}

bool GameField::checkCollision(const Tetramino& tetramino, int x, int y) const {
    const auto& shape = tetramino.getShape();
    for (int ty = 0; ty < shape.size(); ++ty) {
        for (int tx = 0; tx < shape[ty].size(); ++tx) {
            if (shape[ty][tx]) {
                int newX = x + tx;
                int newY = y + ty;
                if (newX < 0 || newX >= width || newY >= height || (newY >= 0 && field[newY][newX])) {
                    return true;
                }
            }
        }
    }
    return false;
}

void GameField::lockTetramino(const Tetramino& tetramino, int x, int y) {
    const auto& shape = tetramino.getShape();
    for (int ty = 0; ty < shape.size(); ++ty) {
        for (int tx = 0; tx < shape[ty].size(); ++tx) {
            if (shape[ty][tx]) {
                field[y + ty][x + tx] = 1;
            }
        }
    }
}

int GameField::clearLines() {
    int linesCleared = 0;
    for (int y = 0; y < height; ++y) {
        bool full = true;
        for (int x = 0; x < width; ++x) {
            if (!field[y][x]) {
                full = false;
                break;
            }
        }
        if (full) {
            linesCleared++;
            for (int i = y; i > 0; --i) {
                field[i] = field[i - 1];
            }
            field[0] = vector<int>(width, 0);
        }
    }
    return linesCleared;
}