#ifndef MINEFIELD_H_
#define MINEFIELD_H_

class Minefield {
    public:
        // make a minefield with a preset difficulty
        Minefield(std::string difficulty);
        
        // destructor
        ~Minefield();

        // initialize the minefield
        void init(std::string difficulty);

        // reinitialize the field with the same difficulty as last.
        void reinit();

        // draw the minefield
        void draw();

        // click on the minefield
        void click(int x, int y);

        // toggle a flag on the tile
        void flag(int x, int y);

        // check to see if the game is lost
        bool checkLose();

        // check to see if the game is won
        bool checkWin();

    private:
        int width;
        int height;
        int numberOfBombs;
        std::string difficulty;
        std::vector<std::vector<Tile*> > tileMap;
};

#endif

