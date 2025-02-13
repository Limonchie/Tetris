#ifndef TETRAMINO_H
#define TETRAMINO_H

#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;
using namespace sf;

class Tetramino {
public:
    Tetramino(const vector<vector<int>>& shape, Color color);
    void rotate();
    void undoRotation();
    const vector<vector<int>>& getShape() const;
    Color getColor() const;
    int getRotationCount() const;

private:
    vector<vector<int>> shape;
    Color color;
    static constexpr int ROTATION_LIMIT = 3;
    int rotationCount = 0;
    vector<vector<int>> previousShape;
};

#endif // TETRAMINO_H