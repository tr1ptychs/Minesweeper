#include <iostream>
#include <vector>
#include <string>
#include "raylib.h"
#include "raymath.h"
#include "Tile.h"
#include "Minefield.h"

void updateFrame(Minefield* field);


int main(void) {
    InitWindow(1000, 400, "Minesweeper");
    Minefield* field = new Minefield("hard");

    while (!WindowShouldClose()) {
        updateFrame(field);
    }

    CloseWindow();
   

    delete field;
    return 0;
}


void updateFrame(Minefield* field){
    BeginDrawing();
    ClearBackground(BLACK);

    // TODO: implement "hover" click
    
    // if cursor is out of the frame, program will crash.
    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && !(GetMouseX() < 0 
            || GetMouseX() > 1000 || GetMouseY() < 0 || GetMouseY() > 400)) {
        field->click(GetMouseX(), GetMouseY());
        
    }
    field->draw();

    EndDrawing();
}


