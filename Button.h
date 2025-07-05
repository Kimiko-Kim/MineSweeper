#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Button
{
private:
    sf::RectangleShape shape;
    sf::Text text;
    sf::Font font;
    sf::Texture texture;
    sf::Sprite sprite;
    bool useTexture = false;

public:
    Button(const std::string& label, sf::Vector2f position, sf::Vector2f size);

    void draw(sf::RenderWindow& window) const;
    bool isMouseOver(const sf::RenderWindow& window) const;
    bool isClicked(sf::RenderWindow& window, sf::Event& event) const;
};
