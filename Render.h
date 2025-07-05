#pragma once
#include <SFML/Graphics.hpp>
#include "Config.h"
#include <string>

class Render
{
public:
    Render();

    void setStatusScreen(const std::string& message);
    void drawStatusScreen(sf::RenderWindow& window) const;
    void drawGrid(sf::RenderWindow& window, const int gridView[GRID_SIZE][GRID_SIZE]);
   
    void setTimerText(const std::string& timeStr);
    void initTimer();
    void drawTimer(sf::RenderWindow& window) const;

    void initMinesLeft();
    void setMinesLeft(int count);
    void drawMinesLeft(sf::RenderWindow& window) const;
    bool initMinesBox(const std::string& textureFilePath, sf::Vector2f position, sf::Vector2f size);

private:
    sf::Texture texture;
    sf::Sprite sprite;
    sf::RectangleShape overlay;
    sf::Text text;
    sf::Text timerText;
    sf::Text minesLeftText;
    sf::Texture minesBoxTexture;
    sf::Sprite minesBoxSprite;
    sf::Font font;

    static constexpr float OverlaySize = 480.f;
    static const sf::Vector2f OverlayPosition;
    static const sf::Vector2f TextPosition;
};
