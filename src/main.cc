#include <iostream>
#include <vector>
#include <string>
#include "raylib.h"
#include "raymath.h"
#include "Tile.h"
#include "Minefield.h"

void updateFrame(Minefield* field);

int main(void) {
    InitWindow(1000, 400, "Minimal Minesweeper");
    Minefield* field = new Minefield("easy");

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

    int x = floor(GetMouseX() / 25);
    int y = floor(GetMouseY() / 25);

    // reveal and flag
    if (!field->checkLose() && !field->checkWin()) {
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) || IsKeyReleased(KEY_Q)) {
            field->click(x, y);
        } 
        if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT) || IsKeyReleased(KEY_W)) {
            field->flag(x, y);
        }
        if (IsMouseButtonReleased(MOUSE_BUTTON_MIDDLE)) {
            field->chord(x, y);
        }
    } else if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT) || IsKeyReleased(KEY_Q)) field->reinit();
    
    // new game/change game
    if (IsKeyReleased(KEY_ONE)) {
        field->init("easy");
    } else if (IsKeyReleased(KEY_TWO)) {
        field->init("medium");
    } else if (IsKeyReleased(KEY_THREE)) {
        field->init("hard");
    }

    field->draw();

    EndDrawing();
}


