#include "Tile.h"
#include "raylib.h"
#include "raymath.h"
#include <numeric>

// construct me 
Tile::Tile(int xCoordinate, int yCoordinate) : xCoordinate(xCoordinate), yCoordinate(yCoordinate){};

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

// insert a bomb into the tile
void Tile::setBomb(){
    this->hasBomb = true;
    return;
}

// draw the tile on the screen
void Tile::draw(){
    if (isRevealed) {
        DrawRectangle(this->xCoordinate, this->yCoordinate,
                      48, 48, WHITE);
    } else if (isHoverClicked) {
        DrawRectangle(this->xCoordinate, this->yCoordinate, 
                      48, 48, DARKGRAY);
    } else {
        DrawRectangle(this->xCoordinate, this->yCoordinate, 
                      48, 48, GRAY);
    }
    return;
}
