#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <sstream>
#include "GameLogic.h"
#include "Render.h"
#include "Button.h"
#include "Dropdown.h"
#include "Config.h"

class MinesweeperApp
{
public:
    MinesweeperApp();
    void run();

private:
    void initializeGridView();
    Game::Difficulty getDifficultyFromString(const std::string& difficultyStr) const;
    void startNewGame();
    void processEvents();
    void update();
    void renderFrame();
    int countFlags(int gridView[GRID_SIZE][GRID_SIZE]) const;

private:
    sf::RenderWindow window;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Clock gameClock;
    sf::Time pauseStartTime;
    sf::Time totalPausedTime;;
    bool wasPaused = false;
    Render render;
    Game game;

    int gridLogic[GRID_SIZE][GRID_SIZE];
    int gridView[GRID_SIZE][GRID_SIZE];

    bool gameOver;
    bool isPaused;
    bool firstClick;

    Game::Difficulty currentDifficulty;
    int mineCount;

    Dropdown difficultyDropdown;
    Button newGameBTN;
    Button pauseBTN;
    Button exitBTN;
};
