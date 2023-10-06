#ifndef TILE_H_
#define TILE_H_


class Tile {
    public:
        // constructor, pass in coordinates
        Tile(int xCoordinate, int yCoordinate);

        // destructor
        ~Tile();
        
        // click the tile
        void click();

        // reveal the tile.
        bool reveal();
        
        // insert a bomb into the tile
        void setBomb();
        
        // draw the tile on the screen
        void draw();

    private:
        bool hasBomb;
        bool isRevealed;
        bool isHoverClicked;
        bool hasFlag;
        int hintNumber;
        const int xCoordinate;
        const int yCoordinate;
};

#endif

