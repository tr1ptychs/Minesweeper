#include "raylib.h"
#include "raymath.h"
#include "Tile.h"


#include <iostream>
#include <vector>

void updateFrame();
void initTileMap();
void drawTileMap();

Tile* testTile = new Tile(0, 0);
std::vector<int> mouseTilePosition = std::vector<int>(2);
std::vector<std::vector<Tile*> > tileMap (5, std::vector<Tile*> (8));


int main(void) {
    
    InitWindow(400, 250, "Minesweeper");
    initTileMap();

    while (!WindowShouldClose()) {
        updateFrame();
    }

    CloseWindow();
    
    delete testTile;
    return 0;
}


void updateFrame(){
    BeginDrawing();
    ClearBackground(BLACK);

    // TODO: implement "hover" click
    //if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
    //    tileMap.at(floor(GetMousePosition().y / 50)).at(floor(GetMousePosition().x / 50))->click();
    //}
    
    // if cursor is out of the frame, program will crash.
    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && !(GetMouseX() < 0 
            || GetMouseX() > 400 || GetMouseY() < 0 || GetMouseY() > 250)) {
        tileMap.at(floor(GetMousePosition().y / 50)).at(floor(GetMousePosition().x / 50))->reveal();
    }

    drawTileMap();

    EndDrawing();
}

void initTileMap(){
    for(int y = 0; y < 5; y++) {
        for(int x = 0; x < 8; x++) {
            tileMap.at(y).at(x) = new Tile(50 * x, 50 * y);
        }
    }
}

void drawTileMap(){
     for(int y = 0; y < tileMap.size(); y++) {
        for(int x = 0; x < tileMap.at(0).size(); x++) {
            tileMap.at(y).at(x)->draw();
        }
    }
}
