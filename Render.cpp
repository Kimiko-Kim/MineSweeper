#include "Render.h"

const sf::Vector2f Render::OverlayPosition = { OFFSET_X, OFFSET_Y };
const sf::Vector2f Render::TextPosition = { 300.f, 300.f };

Render::Render()
{
    texture.loadFromFile("tiles.png");
    sprite.setTexture(texture);
    font.loadFromFile("Chewy-Regular.ttf");
    text.setFont(font);
}

void Render::drawGrid(sf::RenderWindow& window, const int gridView[GRID_SIZE][GRID_SIZE])
{
    for (int i = 0; i < GRID_SIZE; ++i)
    {
        for (int j = 0; j < GRID_SIZE; ++j)
        {
            sprite.setTextureRect(sf::IntRect(gridView[i][j] * TILE_SIZE, 0, TILE_SIZE, TILE_SIZE));
            sprite.setPosition(i * TILE_SIZE + OFFSET_X, j * TILE_SIZE + OFFSET_Y);
            window.draw(sprite);
        }
    }
}

void Render::initTimer()
{
    timerText.setFont(font);
    timerText.setCharacterSize(46);
    timerText.setFillColor(sf::Color::White);
    timerText.setPosition(300.f, 50.f);
}

void Render::setTimerText(const std::string& timeStr)
{
    timerText.setString(timeStr);
}

void Render::drawTimer(sf::RenderWindow& window) const
{
    window.draw(timerText);
}

void Render::initMinesLeft()
{
    minesLeftText.setFont(font);
    minesLeftText.setCharacterSize(26);
    minesLeftText.setFillColor(sf::Color::Black);
    minesLeftText.setPosition(70.f, 50.f);
}

bool Render::initMinesBox(const std::string& textureFilePath, sf::Vector2f position, sf::Vector2f size)
{
    if (!minesBoxTexture.loadFromFile("Button.png"))
        return false; 

    minesBoxSprite.setTexture(minesBoxTexture);

    sf::Vector2f textureSize(minesBoxTexture.getSize());
    minesBoxSprite.setScale(size.x / textureSize.x, size.y / textureSize.y);

    minesBoxSprite.setPosition(position);

    return true;
}

void Render::setMinesLeft(int count)
{
    std::string str = "Mines left: " + std::to_string(count);
    minesLeftText.setString(str);

    sf::FloatRect textRect = minesLeftText.getLocalBounds();

    minesLeftText.setOrigin(textRect.left + textRect.width / 2.f,
        textRect.top + textRect.height / 2.f);

    sf::Vector2f boxPos = minesBoxSprite.getPosition();
    sf::Vector2f boxSize(minesBoxSprite.getGlobalBounds().width,
        minesBoxSprite.getGlobalBounds().height);

    minesLeftText.setPosition(boxPos.x + boxSize.x / 2.f,
        boxPos.y + boxSize.y / 2.f);
}


void Render::drawMinesLeft(sf::RenderWindow& window) const
{
    window.draw(minesBoxSprite);
    window.draw(minesLeftText);
}

void Render::setStatusScreen(const std::string& message)
{
    overlay = sf::RectangleShape(sf::Vector2f(OverlaySize, OverlaySize));
    overlay.setFillColor(sf::Color(0, 0, 0, 150));
    overlay.setPosition(OverlayPosition);
    overlay.setOutlineThickness(2);
    overlay.setOutlineColor(sf::Color::White);

    text.setString(message);
    text.setCharacterSize(70);
    text.setFillColor(sf::Color::White);

    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.f, textRect.top + textRect.height / 2.f);
    text.setPosition(TextPosition);
}

void Render::drawStatusScreen(sf::RenderWindow& window) const
{
    window.draw(overlay);
    window.draw(text);
}
