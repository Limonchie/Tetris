//—чЄт и уровни сложности

#include "Score.h"

Score::Score() : score(0), level(1), linesCleared(0) {}

void Score::addLines(int lines) {
    linesCleared += lines;
    switch (lines) {
    case 1:
        score += 100;
        break;
    case 2:
        score += 300;
        break;
    case 3:
        score += 700;
        break;
    case 4:
        score += 1500;
        break;
    }
    updateLevel();
}

void Score::updateLevel() {
    level = (score / 1000) + 1;
}

int Score::getScore() const {
    return score;
}

int Score::getLevel() const {
    return level;
}

int Score::getLinesCleared() const {
    return linesCleared;
}

void Score::draw(RenderWindow& window, int fieldHeight, int tileSize) const {
    Font font;
    if (!font.loadFromFile("Times New Roman - Italic.ttf")) {
        return;
    }

    Text text;
    text.setFont(font);
    text.setCharacterSize(20);
    text.setFillColor(Color::White);

    text.setString("Score: " + to_string(score));
    text.setPosition(10, fieldHeight * tileSize + 10);
    window.draw(text);

    text.setString("Level: " + to_string(level));
    text.setPosition(150, fieldHeight * tileSize + 10);
    window.draw(text);

    text.setString("Lines: " + to_string(linesCleared));
    text.setPosition(250, fieldHeight * tileSize + 10);
    window.draw(text);
}