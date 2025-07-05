#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Dropdown
{
private:
    sf::RectangleShape shape;
    sf::Font font;
    sf::Text text;

    std::vector<sf::Text> options;
    std::vector<sf::RectangleShape> optionBoxes;

    sf::Texture texture;
    sf::Sprite sprite;
    std::vector<sf::Sprite> optionSprites;

    std::vector<std::string> items;
    bool expanded = false;
    int selectedIndex = -1;

public:
    Dropdown(const std::vector<std::string>& itemList, sf::Vector2f position, sf::Vector2f size);

    void draw(sf::RenderWindow& window) const;
    void handleEvent(const sf::Event& event, const sf::RenderWindow& window);

    int getSelectedIndex() const { return selectedIndex; }
    std::string getSelectedItem() const;
};
