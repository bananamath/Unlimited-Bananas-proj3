#include <Windows.h>
#pragma comment(lib, "winmm.lib")

#include "GameManager.h"
#include "LogManager.h"
#include "DisplayManager.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "Clock.h"
#include "WorldManager.h"
#include "EventStep.h"

using namespace df;

GameManager::GameManager()
{
    setType("GameManager");

    game_over = false;
    frame_time = FRAME_TIME_DEFAULT;
    frame_count = 0;
}


GameManager& GameManager::getInstance()
{
    static GameManager single;
    return single;
}

int GameManager::startUp()
{
    timeBeginPeriod(1);

    LM.startUp();
    WM.startUp();
    DM.startUp();
    IM.startUp();
    RM.startUp();

    Manager::startUp();

    return 0;
}

void GameManager::shutDown()
{
    timeEndPeriod(1);

    setGameOver();

    RM.shutDown();
    IM.shutDown();
    DM.shutDown();
    WM.shutDown();    
    LM.shutDown();

    Manager::shutDown();
}

void GameManager::run()
{
    Clock clock;

    while (!game_over)
    {
        /*
        // Game loop timing test.
        if (frame_count == 330)
        {
            shutDown();
        }
        */

        clock.delta();

        // Increments frame number with each loop.
        frame_count++;

        EventStep s(frame_count);
        onEvent(&s);
        IM.getInput();

        WM.update();
        WM.draw();
        DM.swapBuffers();

        int loop_time = clock.split();

        // Sleeps for the necessary time to maintain set frame_time (default 30fps).
        if (frame_time - loop_time > 0)
        {
            Sleep(frame_time - loop_time);
        }
    }
}

void GameManager::setGameOver(bool new_game_over)
{
    game_over = new_game_over;
}

bool GameManager::getGameOver() const
{
    return game_over;
}

int GameManager::getFrameTime() const
{
    return frame_time;
}

int GameManager::getCurrentFrame()
{
    return frame_count;
}