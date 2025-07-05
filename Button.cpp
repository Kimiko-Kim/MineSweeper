#include "Button.h"

Button::Button(const std::string& label, sf::Vector2f position, sf::Vector2f size)
{
    if (texture.loadFromFile("Button.png"))
    {
        sprite.setTexture(texture);
        sprite.setPosition(position);
        sprite.setScale(
            size.x / texture.getSize().x,
            size.y / texture.getSize().y
        );
        useTexture = true;
    }

    font.loadFromFile("Chewy-Regular.ttf");

    shape.setPosition(position);
    shape.setSize(size);
    shape.setFillColor(sf::Color(200, 200, 200));
    shape.setOutlineColor(sf::Color::Black);
    shape.setOutlineThickness(2);

    text.setFont(font);
    text.setString(label);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::Black);

    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.f, textRect.top + textRect.height / 2.f);
    text.setPosition(position + size / 2.f);
}

void Button::draw(sf::RenderWindow& window) const
{
    if (useTexture)
        window.draw(sprite);
    else
        window.draw(shape);
    window.draw(text);
}

bool Button::isMouseOver(const sf::RenderWindow& window) const
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    return shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
}

bool Button::isClicked(sf::RenderWindow& window, sf::Event& event) const
{
    return isMouseOver(window) &&
        event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left;
}
