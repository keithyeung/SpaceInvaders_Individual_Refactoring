#include "game.h"
#include "../window.h"
#include <iostream>
#include <stdexcept>


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
        while (!window.ShouldClose())  
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

    return 0;
}

