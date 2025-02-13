#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Tetramino.h"

// Предварительное объявление класса Tetramino
class Tetramino;

using namespace std;
using namespace sf;

class GameField {
public:
    GameField(int width, int height, int tileSize);

    void draw(RenderWindow& window) const;
    bool checkCollision(const Tetramino& tetramino, int x, int y) const;
    void lockTetramino(const Tetramino& tetramino, int x, int y);
    int clearLines();

    int getWidth() const { return width; }
    int getHeight() const { return height; }
    int getTileSize() const { return tileSize; }

private:
    int width, height, tileSize;
    vector<vector<int>> field;
};

#endif // GAMEFIELD_H