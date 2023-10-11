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
        
        // draw the tile on the screen
        void draw();

        // check to see if tile has a bomb.
        bool tileHasBomb();

        // set the color of the tile
        void setColor(Color color);

        // get the color of the tile
        Color getColor();

    private:
        const bool hasBomb;
        bool isRevealed;
        bool isHoverClicked;
        bool hasFlag;
        Color color;
        const int xCoordinate;
        const int yCoordinate;
};

#endif

