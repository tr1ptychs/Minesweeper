#include "Tile.h"
#include "raylib.h"
#include "raymath.h"

// construct me 
Tile::Tile(int xCoordinate, int yCoordinate, bool hasBomb) : xCoordinate(xCoordinate), 
        yCoordinate(yCoordinate), hasBomb(hasBomb){
    this->isRevealed = false;
    this->hasFlag = false;
};

// destructor
Tile::~Tile(){}

// click the tile 
void Tile::click() {
    this->isHoverClicked = true;
}

// reveal the tile
bool Tile::reveal() {
    if (!hasFlag) {
        this->isRevealed = true;
        return !this->hasBomb;
    }
    return false;
}

void Tile::flag() { this->hasFlag = !this->hasFlag; }

bool Tile::tileHasBomb() {
    return this->hasBomb;
}

void Tile::setTileIsWhite() { this->isWhite = true;}

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
        if (hasFlag) {
            DrawCircle(this->xCoordinate + 12, this->yCoordinate + 12, 9.f, BLACK);
        }
    }
    return;
}

void Tile::setColor(Color color) {
    this->color = color;
}

Color Tile::getColor() { return this->color; }

bool Tile::tileIsWhite() { return this->isWhite; }

bool Tile::tileIsRevealed() { return this-> isRevealed; }


