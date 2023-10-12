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

    // reveal and flag
    if (!field->checkLose() && !field->checkWin()) {
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            field->click(GetMouseX(), GetMouseY());
        }
        if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT)) {
            field->flag(GetMouseX(), GetMouseY());
        }
    } else if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
        field->reinit();
    }

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


