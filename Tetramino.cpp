//Управление фигурами

#include "Tetramino.h"

Tetramino::Tetramino(const vector<vector<int>>& shape, Color color)
    : shape(shape), color(color) {}

void Tetramino::rotate() {
    vector<vector<int>> rotated(shape[0].size(), vector<int>(shape.size(), 0));
    for (int y = 0; y < shape.size(); ++y) {
        for (int x = 0; x < shape[y].size(); ++x) {
            rotated[x][shape.size() - 1 - y] = shape[y][x];
        }
    }

    // Сохраняем текущую форму перед вращением
    previousShape = shape;

    // Применяем вращение
    shape = rotated;
    rotationCount++;
}

void Tetramino::undoRotation() {
    if (rotationCount > 0) {
        shape = previousShape; // Возвращаем предыдущую форму
        rotationCount--;
    }
}

const vector<vector<int>>& Tetramino::getShape() const {
    return shape;
}

Color Tetramino::getColor() const {
    return color;
}

int Tetramino::getRotationCount() const {
    return rotationCount;
}