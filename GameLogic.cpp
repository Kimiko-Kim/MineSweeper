#include "GameLogic.h"
#include "Config.h"
#include <random>
#include <cstdlib>
#include <cmath>

void Game::handleClick(sf::Event event, int x, int y, int gridLogic[GRID_SIZE][GRID_SIZE], int gridView[GRID_SIZE][GRID_SIZE], bool& gameOver, Render& render, int mineCount)
{
    if (gameOver || event.type != sf::Event::MouseButtonPressed)
        return;

    if (event.mouseButton.button == sf::Mouse::Left)
        openCell(x, y, gridLogic, gridView);
    else if (event.mouseButton.button == sf::Mouse::Right)
    {
        toggleFlag(x, y, gridView);
        checkWinCondition(gridLogic, gridView, mineCount, gameOver, render);
    }

    // If a mine is opened, the game is over
    if (gridView[x][y] == static_cast<int>(CellType::Mine))
    {
        gameOver = true;
        render.setStatusScreen("Game Over");

        // Open all mines
        for (int i = 0; i < GRID_SIZE; ++i)
            for (int j = 0; j < GRID_SIZE; ++j)
                if (gridLogic[i][j] == static_cast<int>(CellType::Mine))
                    gridView[i][j] = static_cast<int>(CellType::Mine);
    }
}

void Game::checkWinCondition(int gridLogic[GRID_SIZE][GRID_SIZE], int gridView[GRID_SIZE][GRID_SIZE], int mineCount, bool& gameOver, Render& render)
{
    int correctFlags = 0;
    int totalFlags = 0;

    for (int y = 0; y < GRID_SIZE; ++y)
    {
        for (int x = 0; x < GRID_SIZE; ++x)
        {
            if (gridView[y][x] == static_cast<int>(CellType::Flag))
            {
                totalFlags++;
                if (gridLogic[y][x] == static_cast<int>(CellType::Mine))
                    correctFlags++;
            }
        }
    }

    if (totalFlags == mineCount && correctFlags == mineCount)
    {
        gameOver = true;
        render.setStatusScreen("You win!");
    }
}

void Game::openCell(int x, int y, int gridLogic[GRID_SIZE][GRID_SIZE], int gridView[GRID_SIZE][GRID_SIZE])
{
    if (gridView[x][y] == static_cast<int>(CellType::Closed) || gridView[x][y] == static_cast<int>(CellType::Flag))
        gridView[x][y] = gridLogic[x][y];
}

void Game::toggleFlag(int x, int y, int gridView[GRID_SIZE][GRID_SIZE])
{
    if (gridView[x][y] == static_cast<int>(CellType::Closed))
        gridView[x][y] = static_cast<int>(CellType::Flag);
    else if (gridView[x][y] == static_cast<int>(CellType::Flag))
        gridView[x][y] = static_cast<int>(CellType::Closed);
}

int Game::getMineCount(Difficulty d)
{
    switch (d)
    {
    case Difficulty::Easy: return 10;
    case Difficulty::Medium: return 20;
    case Difficulty::Hard: return 35;
    }
    return 10;
}

void Game::generateField(int gridLogic[GRID_SIZE][GRID_SIZE], int gridView[GRID_SIZE][GRID_SIZE], int safeX, int safeY, int mineCount)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, GRID_SIZE - 1);

    // Initialize to empty
    for (int i = 0; i < GRID_SIZE; ++i)
        for (int j = 0; j < GRID_SIZE; ++j)
            gridLogic[i][j] = static_cast<int>(CellType::Empty);

    int placed = 0;
    while (placed < mineCount)
    {
        int x = dis(gen);
        int y = dis(gen);

        if (std::abs(x - safeX) <= 1 && std::abs(y - safeY) <= 1)
            continue;

        if (gridLogic[x][y] == static_cast<int>(CellType::Mine))
            continue;

        gridLogic[x][y] = static_cast<int>(CellType::Mine);
        ++placed;
    }

    // Counting neighboring mines
    for (int i = 0; i < GRID_SIZE; ++i)
    {
        for (int j = 0; j < GRID_SIZE; ++j)
        {
            if (gridLogic[i][j] == static_cast<int>(CellType::Mine))
                continue;

            int count = 0;
            for (int dx = -1; dx <= 1; ++dx)
            {
                for (int dy = -1; dy <= 1; ++dy)
                {
                    int nx = i + dx, ny = j + dy;
                    if (nx >= 0 && nx < GRID_SIZE && ny >= 0 && ny < GRID_SIZE)
                        if (gridLogic[nx][ny] == static_cast<int>(CellType::Mine))
                            ++count;
                }
            }
            gridLogic[i][j] = count;
        }
    }

    // Set all cells as closed
    for (int i = 0; i < GRID_SIZE; ++i)
        for (int j = 0; j < GRID_SIZE; ++j)
            gridView[i][j] = static_cast<int>(CellType::Closed);
}