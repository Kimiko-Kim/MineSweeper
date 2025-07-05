#include "MinesweeperApp.h"
#include <ctime>

MinesweeperApp::MinesweeperApp()
    : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Minesweeper!"),
    difficultyDropdown(std::vector<std::string>{ "Easy", "Medium", "Hard" }, { 230.f, 620.f }, { 140.f, 50.f }),
    newGameBTN("New Game", { 60.f, 620.f }, { 140.f, 50.f }),
    pauseBTN("Pause", { 450.f, 50.f }, { 90.f, 50.f }),
    exitBTN("Exit", { 400.f, 620.f }, { 140.f, 50.f }),
    gameOver(true),
    isPaused(false),
    firstClick(true),
    currentDifficulty(Game::Difficulty::Medium),
    mineCount(Game::getMineCount(Game::Difficulty::Medium))
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    initializeGridView();
    render.initTimer();
    sf::Vector2f boxPos(60.f, 50.f);
    sf::Vector2f boxSize(200.f, 50.f);
    render.initMinesBox("box.png", boxPos, boxSize);
    render.setStatusScreen("Choose a\ndifficulty level");
}

void MinesweeperApp::initializeGridView()
{
    for (int i = 0; i < GRID_SIZE; ++i)
        for (int j = 0; j < GRID_SIZE; ++j)
            gridView[i][j] = static_cast<int>(CellType::Closed);
}

Game::Difficulty MinesweeperApp::getDifficultyFromString(const std::string& diff) const
{
    if (diff == "Easy") return Game::Difficulty::Easy;
    if (diff == "Hard") return Game::Difficulty::Hard;
    return Game::Difficulty::Medium;
}

int countCorrectFlags(int gridLogic[GRID_SIZE][GRID_SIZE], int gridView[GRID_SIZE][GRID_SIZE])
{
    int correctFlags = 0;
    for (int y = 0; y < GRID_SIZE; ++y)
        for (int x = 0; x < GRID_SIZE; ++x)
            if (gridView[y][x] == static_cast<int>(CellType::Flag) &&
                gridLogic[y][x] == static_cast<int>(CellType::Mine))
            {
                correctFlags++;
            }
    return correctFlags;
}

void MinesweeperApp::startNewGame()
{
    gameOver = false;
    isPaused = false;
    firstClick = true;

    currentDifficulty = getDifficultyFromString(difficultyDropdown.getSelectedItem());
    mineCount = Game::getMineCount(currentDifficulty);

    gameClock.restart();
    totalPausedTime = sf::Time::Zero;
    pauseStartTime = sf::Time::Zero;
    wasPaused = false;
    render.setTimerText("0:00");
    render.initMinesLeft();

    initializeGridView();
    game.generateField(gridLogic, gridView, 0, 0, mineCount);

    sf::Vector2f boxPos(60.f, 50.f);
    sf::Vector2f boxSize(200.f, 50.f);
    render.initMinesBox("box.png", boxPos, boxSize);

    render.setStatusScreen("");
}

void MinesweeperApp::processEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        difficultyDropdown.handleEvent(event, window);

        if (event.type == sf::Event::Closed || exitBTN.isClicked(window, event))
            window.close();

        if (newGameBTN.isClicked(window, event))
            startNewGame();

        if (pauseBTN.isClicked(window, event))
        {
            isPaused = !isPaused;
            render.setStatusScreen(isPaused ? "Pause" : "");
        }

        if (event.type == sf::Event::MouseButtonPressed && !gameOver && !isPaused)
        {
            sf::Vector2i pos = sf::Mouse::getPosition(window);
            bool insideX = (pos.x >= OFFSET_X && pos.x < OFFSET_X + GRID_SIZE * TILE_SIZE);
            bool insideY = (pos.y >= OFFSET_Y && pos.y < OFFSET_Y + GRID_SIZE * TILE_SIZE);
            if (insideX && insideY)
            {
                int x = (pos.x - OFFSET_X) / TILE_SIZE;
                int y = (pos.y - OFFSET_Y) / TILE_SIZE;

                if (firstClick)
                {
                    currentDifficulty = getDifficultyFromString(difficultyDropdown.getSelectedItem());
                    mineCount = Game::getMineCount(currentDifficulty);

                    game.generateField(gridLogic, gridView, x, y, mineCount);
                    firstClick = false;
                    render.setStatusScreen("");
                }

                game.handleClick(event, x, y, gridLogic, gridView, gameOver, render, mineCount);
            }
        }
    }
}

void MinesweeperApp::update()
{
    if (gameOver) return;

    if (isPaused && !wasPaused)
    {
        pauseStartTime = gameClock.getElapsedTime();
        wasPaused = true;
        return;
    }

    if (!isPaused && wasPaused)
    {
        sf::Time pausedDuration = gameClock.getElapsedTime() - pauseStartTime;
        totalPausedTime += pausedDuration;
        wasPaused = false;
    }

    if (isPaused) return; 

    sf::Time elapsed = gameClock.getElapsedTime() - totalPausedTime;

    int seconds = static_cast<int>(elapsed.asSeconds());
    int minutes = seconds / 60;
    int remainingSeconds = seconds % 60;

    std::ostringstream ss;
    ss << minutes << ":" << (remainingSeconds < 10 ? "0" : "") << remainingSeconds;
    render.setTimerText(ss.str());

    int minesLeft = mineCount - countCorrectFlags(gridLogic, gridView);
    if (minesLeft < 0)
        minesLeft = 0;

    render.setMinesLeft(minesLeft);
}


void MinesweeperApp::renderFrame()
{
    window.clear(sf::Color(55, 176, 203));

    backgroundTexture.loadFromFile("Background.PNG");
    backgroundSprite.setTexture(backgroundTexture);
    sf::Vector2u textureSize = backgroundTexture.getSize();
    sf::Vector2u windowSize = window.getSize();

    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;

    backgroundSprite.setScale(scaleX, scaleY);
    backgroundSprite.setPosition(0.f, 0.f);

    window.draw(backgroundSprite);
    render.drawGrid(window, gridView);

    if (gameOver || isPaused)
        render.drawStatusScreen(window);

    newGameBTN.draw(window);
    render.drawTimer(window);
    render.drawMinesLeft(window);
    difficultyDropdown.draw(window);
    exitBTN.draw(window);
    pauseBTN.draw(window);

    window.display();
}

void MinesweeperApp::run()
{
    while (window.isOpen())
    {
        processEvents();
        update();
        renderFrame();
    }
}
