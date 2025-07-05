#pragma once
#include "Render.h"

class Game
{
public:
    enum class Difficulty { Easy, Medium, Hard };

    void handleClick(sf::Event event, int x, int y, int gridLogic[GRID_SIZE][GRID_SIZE], int gridView[GRID_SIZE][GRID_SIZE], bool& gameOver, Render& render, int mineCount);
    void generateField(int gridLogic[GRID_SIZE][GRID_SIZE], int gridView[GRID_SIZE][GRID_SIZE], int safeX, int safeY, int mineCount);
    static int getMineCount(Difficulty d);
    void checkWinCondition(int gridLogic[GRID_SIZE][GRID_SIZE], int gridView[GRID_SIZE][GRID_SIZE], int mineCount, bool& gameOver, Render& render);


private:
    void openCell(int x, int y, int gridLogic[GRID_SIZE][GRID_SIZE], int gridView[GRID_SIZE][GRID_SIZE]);
    void toggleFlag(int x, int y, int gridView[GRID_SIZE][GRID_SIZE]);
};
