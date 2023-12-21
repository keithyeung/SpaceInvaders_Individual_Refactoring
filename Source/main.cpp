/*******************************************************************************************
*
*   raylib [core] example - Basic window
*
*   Welcome to raylib!
*
*   To test examples, just press F6 and execute raylib_compile_execute script
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   Example originally created with raylib 1.0, last time updated with raylib 1.0
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*b
*   Copyright (c) 2013-2022 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include "game.h"
#include "../window.h"


//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
constexpr int SCREEN_WIDTH = 1920;
constexpr int SCREEN_HEIGHT = 1080;
constexpr std::string_view TITLE = "SPACE INVADERS";

int main(void)
{    
    Window window(SCREEN_WIDTH, SCREEN_HEIGHT, TITLE);

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    Game game = { State::STARTSCREEN };
    // Main game loop
    while (!window.ShouldClose())    // Detect window close button or ESC key
    {
        game.Update();

        BeginDrawing();
        ClearBackground(BLACK);
        game.Render();
        EndDrawing();
    }
    std::string filename = "level.txt";  

    return 0;
}