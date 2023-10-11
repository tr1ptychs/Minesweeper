#include "Tile.h"
#include "raylib.h"
#include "raymath.h"

// construct me 
Tile::Tile(int xCoordinate, int yCoordinate, bool hasBomb) : xCoordinate(xCoordinate), 
        yCoordinate(yCoordinate), hasBomb(hasBomb){};

// destructor
Tile::~Tile(){}

// click the tile
void Tile::click(){
    this->isHoverClicked = true;
}

// reveal the tile
bool Tile::reveal(){
    if (!hasFlag) {
        this->isRevealed = true;
        return !this->hasBomb;
    }
    return false;
}

bool Tile::tileHasBomb() {
    return this->hasBomb;
}

// draw the tile on the screen
void Tile::draw() {
    if (isRevealed) {
        if (hasBomb) {
            DrawRectangle(this->xCoordinate, this->yCoordinate, 23, 23, BLACK);
        } else {
            DrawRectangle(this->xCoordinate, this->yCoordinate, 23, 23, this->getColor());
        }
    } else {
        DrawRectangle(this->xCoordinate, this->yCoordinate, 23, 23, GRAY);
    }
    return;
}

void Tile::setColor(Color color) {
    this->color = color;
}

Color Tile::getColor() { return this->color; }
