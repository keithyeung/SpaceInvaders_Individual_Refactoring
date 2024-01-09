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

//TODO: start making slide drafts. One slide, one smell/issue. Sort on severity. 
//      Always add a "future work" or "remaining issues" at the end, to let you demonstrate knowledge even if you didn't have time to fix the code in question.
//TODO: make sure you handle the exceptions in main
// TODO: physical structure. Extract all types into separate files. 
//TODO: review all interfaces. 
//  Delete unused / unecessary stuff. 
//  Make const when possible (all render!),
//  make noexcept when possible (almost everything that doesn't allocate, or calls functions that are documented to throw, like std::from_chars)
//TODO: reduce branching, nesting and function length. (perhaps branches are better expressed as functions? perhaps some features are missing a class (Animation))
// TODO: catch the exceptions in main, and display a message box with the error message.
//

int main(void)
{    
    Window window(SCREEN_WIDTH, SCREEN_HEIGHT, TITLE);

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    Game game{};
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