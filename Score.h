#ifndef SCORE_H
#define SCORE_H

#include <SFML/Graphics.hpp>
#include <string>

using namespace std;
using namespace sf;

class Score {
public:
    Score();
    void addLines(int lines);
    void updateLevel();
    int getScore() const;
    int getLevel() const;
    int getLinesCleared() const;
    void draw(RenderWindow& window, int fieldHeight, int tileSize) const;

private:
    int score;
    int level;
    int linesCleared;
};

#endif // SCORE_H