#ifndef TILE_H_
#define TILE_H_


#include "raylib.h"
class Tile {
    public:
        // constructor, pass in coordinates
        Tile(int xCoordinate, int yCoordinate, bool hasBomb);

        // destructor
        ~Tile();
        
        // click the tile
        void click();

        // reveal the tile.
        bool reveal();

        // place a flag onto the tile or remove flag from tile
        void flag();
        
        // draw the tile on the screen
        void draw();

        // check to see if tile has a bomb.
        bool tileHasBomb();

        // set the color of the tile
        void setColor(Color color);

        // get the color of the tile
        Color getColor();

        // set the hint number
        void setNumber(int hintNumber);

        // get the hint number
        int getNumber();
        
        // set tile to be white 
        void setTileIsWhite();

        // return true if square is white
        bool tileIsWhite();

        // return if the tile is revealed
        bool tileIsRevealed();
    
        bool hasFlag;
    private:
        const bool hasBomb;
        bool isRevealed;
        bool isHoverClicked;
        bool isWhite;
        int number;
        Color color;
        const int xCoordinate;
        const int yCoordinate;
};

#endif

