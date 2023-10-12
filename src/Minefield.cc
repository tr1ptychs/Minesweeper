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
                                                                / this->numberOfBombs));
    bool hasBomb;
    int count = 0;
    bool done = false;
    std::cout << this->width << std::endl;
    // init bombs
    //while (count < this->numberOfBombs) {
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
        std::cout << count << std::endl;
    //}
    if (count != numberOfBombs) {
        init(difficulty);
        return;
    }
    // init colors 
    Color colors[] = {WHITE, BLUE, GREEN, RED, DARKBLUE, MAROON, (Color) {0, 128, 128, 255}, VIOLET, DARKGRAY};

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
                        if (xCoord < this->width && xCoord >= 0 && yCoord < this->height && yCoord >= 0) {
                            if (this->tileMap.at(yCoord).at(xCoord)->tileHasBomb()) {
                                count++;
                            }
                        }
                    }
                }        
            }
            this->tileMap.at(y).at(x)->setColor(colors[count]);
            if (count == 0) tileMap.at(y).at(x)->setTileIsWhite();
        }
    }
}

void Minefield::reinit() {
    init(this->difficulty);
}

void Minefield::draw() {
    // std::cout << "x: 5, y: 8" << std::endl;
    // std::cout << this->tileMap.at(5).at(8) << std::endl;
    for (int y = 0; y < this->height; y++) {
        for (int x = 0; x < this->width; x++) {
            //std::cout << "x: " << x << std::endl << "y: " << y << std::endl;
            this->tileMap.at(y).at(x)->draw();
        }
    }
}

void Minefield::flag(int x, int y) {
    this->tileMap.at(floor(y/25)).at(floor(x/25))->flag(); 
}

void Minefield::click(int x, int y) {
    int xCoord = floor(x/25);
    int yCoord = floor(y/25);
    if (!(xCoord < 0 || xCoord >= this->width || yCoord < 0 || yCoord >= this->height)){
        if (!this->tileMap.at(yCoord).at(xCoord)->tileIsRevealed()){
            this->tileMap.at(yCoord).at(xCoord)->reveal();
            
            // if tile is white reveal neighbors.
            if (this->tileMap.at(yCoord).at(xCoord)->tileIsWhite() 
                    && !this->tileMap.at(yCoord).at(xCoord)->tileHasBomb()) {
                for (int i = -1; i < 2; i++) {
                    for (int j = -1; j < 2; j++) {
                        if (!(i == 0 && j == 0)) {
                            this->click(x + 25 * i, y + 25 * j);
                        }
                    }
                }
            }
        }
    }
}



bool Minefield::checkLose() {
    for (int y = 0; y < this->height; y++) {
        for (int x = 0; x < this->width; x++) {
            if (this->tileMap.at(y).at(x)->tileHasBomb() && this->tileMap.at(y).at(x)->tileIsRevealed()) {
                return true;
            }
        }
    }
    return false;
}

bool Minefield::checkWin() {
    for (int y = 0; y < this->height; y++) {
        for (int x = 0; x < this->width; x++) {
            if (!this->tileMap.at(y).at(x)->tileHasBomb() && !this->tileMap.at(y).at(x)->tileIsRevealed()) {
                return false;
            }
        }
    }
    return true;
}
