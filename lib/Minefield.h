#ifndef MINEFIELD_H_
#define MINEFIELD_H_

class Minefield {
    public:
        // make a minefield with a preset difficulty
        Minefield(std::string difficulty);
        
        // destructor
        ~Minefield();

        // draw the minefield
        void draw();

        // click on the minefield
        void click(int x, int y);

    private:
        int width;
        int height;
        int numberOfBombs;
        std::vector<std::vector<Tile*> > tileMap;
};

#endif

