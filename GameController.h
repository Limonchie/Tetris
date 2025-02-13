#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "GameField.h"  // ��������� GameField
#include "Tetramino.h"  // ��������� Tetramino
#include "Score.h"      // ��������� Score

using namespace std;
using namespace sf;

class GameController {
public:
    GameController(GameField& field, RenderWindow& window);
    void run();

private:
    void spawnTetramino();
    void moveTetramino(int dx, int dy);
    void handleInput();
    void updateUI();
    void gameOver();

    GameField& field;
    RenderWindow& window;
    unique_ptr<Tetramino> currentTetramino;
    int tetraminoX, tetraminoY;
    Score score; // ������ ������ Score
    float fallSpeed;
};

#endif // GAMECONTROLLER_H