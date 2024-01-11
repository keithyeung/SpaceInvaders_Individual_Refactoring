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
#include <iostream>
#include <stdexcept>


//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
constexpr int SCREEN_WIDTH = 1920;
constexpr int SCREEN_HEIGHT = 1080;
constexpr std::string_view TITLE = "SPACE INVADERS";

//TODO: start making slide drafts. One slide, one smell/issue. Sort on severity. 
//      Always add a "future work" or "remaining issues" at the end, to let you demonstrate knowledge even if you didn't have time to fix the code in question.
//TODO: reduce branching, nesting and function length. (perhaps branches are better expressed as functions? perhaps some features are missing a class (Animation))

int main(void)
{
    try
    {
        Window window(SCREEN_WIDTH, SCREEN_HEIGHT, TITLE);
        Game game{};
        // Main game loop
        while (!window.ShouldClose())  // Detect window close button or ESC key
        {
            game.Update();
            game.Render();
        }

        std::string filename = "level.txt";
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception caught: " << e.what() << std::endl;
        TraceLog(LOG_ERROR,"Exception caught : %s", e.what());
    }
    catch (...)
    {
        std::cerr << "Unknown exception caught." << std::endl;
        TraceLog(LOG_ERROR, "An unexpected error occurred.");
    }

    return 0;
}