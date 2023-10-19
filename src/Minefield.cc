#include <string>
#include <random>
#include <iostream>
#include <ctime>
#include "Tile.h"
#include "Minefield.h"
#include "raylib.h"


Minefield::Minefield(std::string difficulty) {
    init(difficulty);
}

Minefield::~Minefield(){
    for(int y = 0; y < this->height; y++) {
        for(int x = 0; x < this->width; x++) {
            delete tileMap.at(y).at(x);
        }
    }
}

void Minefield::init(std::string difficulty) {
    this->difficulty = difficulty;
    if (difficulty == "easy") {
        this->width = 9;
        this->height = 9;
        this->numberOfBombs = 10;
    } else if (difficulty == "medium") {
        this->width = 16;
        this->height = 16;
        this->numberOfBombs = 40;
    } else if (difficulty == "hard") {
        this->width = 40;
        this->height = 16;
        this->numberOfBombs = 99;
    }

    // init map
    this->tileMap = std::vector<std::vector<Tile*>>(this->height);
    for (int y = 0; y < this->height; y++) {
        this->tileMap.at(y) = std::vector<Tile*>(this->width);
    }

    // bomb placement engine
    std::default_random_engine generator(std::random_device{}()); 
    std::uniform_int_distribution<int> distribution(1, floor((this->width * this->height) 
                                                                / this->numberOfBombs) + 1);
    bool hasBomb;
    int count = 0;
    bool done = false;
    
    // init bombs
    for (int y = 0; y < this->height; y++) {
        for (int x = 0; x < this->width; x++) {
            if (!done) {
                hasBomb = distribution(generator) == 1;
                if (hasBomb) count++;
                if (count == this->numberOfBombs) done = true;
            } else { hasBomb = false; }

                this->tileMap.at(y).at(x) = new Tile(25 * x + 1, 25 * y + 1, hasBomb);
            }
    }
    if (count != numberOfBombs) {
        init(difficulty);
        return;
    }
    // init colors 
    Color colors[] = {RAYWHITE, BLUE, GREEN, RED, DARKBLUE, MAROON, (Color) {0, 128, 128, 255}, VIOLET, DARKGRAY};
    int xCoord;
    int yCoord;
    

    for (int y = 0; y < this->height; y++) {
        for (int x = 0; x < this->width; x++) {
            count = 0;

            if (!this->tileMap.at(y).at(x)->tileHasBomb()) {
                for (int i = -1; i < 2; i++) {
                    for (int j = -1; j < 2; j++) {
                        xCoord = x + j;
                        yCoord = y + i;
                        if (coordinateIsInBounds(xCoord, yCoord)) {
                            if (this->tileMap.at(yCoord).at(xCoord)->tileHasBomb()) {
                                count++;
                            }
                        }
                    }
                }        
            }
            this->tileMap.at(y).at(x)->setColor(colors[count]);
            this->tileMap.at(y).at(x)->setNumber(count);
            if (count == 0) tileMap.at(y).at(x)->setTileIsWhite();
        }
    }
}

void Minefield::reinit() {
    init(this->difficulty);
}

void Minefield::draw() {
    for (int y = 0; y < this->height; y++) {
        for (int x = 0; x < this->width; x++) {
            this->tileMap.at(y).at(x)->draw();
        }
    }
}

void Minefield::flag(int x, int y) {
    this->tileMap.at(floor(y/25)).at(floor(x/25))->flag(); 
}

void Minefield::click(int x, int y) {
    x = floor(x/25);
    y = floor(y/25);

    Tile* currentTile = getTileAtCoordinates(x, y);
    if (currentTile == nullptr) return;

    if (currentTile->tileIsRevealed()) return; 
    currentTile->reveal();
            
    // if tile is white reveal neighbors.
    if (!currentTile->tileIsWhite() || currentTile->tileHasBomb()) return;
        
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            this->click(25 * (x + i), 25 * (y + j));
        }
    }
}

void Minefield::chord(int x, int y) {
    x = floor(x/25);
    y = floor(y/25);

    Tile* currentTile = getTileAtCoordinates(x, y);
    if (currentTile->tileHasBomb()) return;
    Tile* countTile;
    if (currentTile == nullptr) return;
    int count = 0;

    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            countTile = getTileAtCoordinates(x + i, y + j);
            if (countTile != nullptr && countTile->hasFlag) {
                count++;
            }
        }
    }
   
    if (count == currentTile->getNumber()) {
        for (int i = -1; i < 2; i++) {
            for (int j = -1; j < 2; j++) {
                this->click(25 * (x + i), 25 * (y + j));
            }
        }   
    }
}


bool Minefield::checkLose() {
    Tile* currentTile;

    for (int y = 0; y < this->height; y++) {
        for (int x = 0; x < this->width; x++) {
            currentTile = this->tileMap.at(y).at(x);

            if (currentTile->tileHasBomb() && currentTile->tileIsRevealed()) {
                return true;
            }
        }
    }
    return false;
}

bool Minefield::checkWin() {
    Tile* currentTile;

    for (int y = 0; y < this->height; y++) {
        for (int x = 0; x < this->width; x++) {
            currentTile = this->tileMap.at(y).at(x);

            if (!currentTile->tileHasBomb() && !currentTile->tileIsRevealed()) {
                return false;
            }
        }
    }
    return true;
}

bool Minefield::coordinateIsInBounds(int x, int y) {
    return x >= 0 && x < this->width && y >= 0 && y < this->height;
}

Tile* Minefield::getTileAtCoordinates(int x, int y) {
    if (!coordinateIsInBounds(x, y)) return nullptr;
    
    return this->tileMap.at(y).at(x);
}
