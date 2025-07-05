#include "Dropdown.h"

Dropdown::Dropdown(const std::vector<std::string>& itemList, sf::Vector2f position, sf::Vector2f size)
    : items(itemList)
{
    texture.loadFromFile("Button.png");
    sprite.setTexture(texture);
    sprite.setPosition(position);
    sprite.setScale(
        size.x / texture.getSize().x,
        size.y / texture.getSize().y
    );

    font.loadFromFile("Chewy-Regular.ttf");

    shape.setSize(size);
    shape.setPosition(position);
    shape.setFillColor(sf::Color(200, 200, 200));

    text.setFont(font);
    text.setString("Difficulty");
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::Black);

    sf::FloatRect textRect = text.getLocalBounds();

    text.setOrigin(textRect.left + textRect.width / 2.f,
        textRect.top + textRect.height / 2.f);

    text.setPosition(position.x + size.x / 2.f,
        position.y + size.y / 2.f);

    for (size_t i = 0; i < items.size(); ++i)
    {
        sf::Text optionText;
        optionText.setFont(font);
        optionText.setString(items[i]);
        optionText.setCharacterSize(20);
        optionText.setFillColor(sf::Color::Black);

        sf::FloatRect optionTextRect = optionText.getLocalBounds();

        optionText.setOrigin(optionTextRect.left + optionTextRect.width / 2.f,
            optionTextRect.top + optionTextRect.height / 2.f);

        optionText.setPosition(position.x + size.x / 2.f,
            position.y + size.y / 2.f + (i + 1) * size.y);

        options.push_back(optionText);

        sf::RectangleShape rect;
        rect.setSize(size);
        rect.setPosition(position.x, position.y + (i + 1) * size.y);  
        
        sf::Sprite optionSprite;
        optionSprite.setTexture(texture);
        optionSprite.setPosition(rect.getPosition());
        optionSprite.setScale(
            size.x / texture.getSize().x,
            size.y / texture.getSize().y
        );

        optionSprites.push_back(optionSprite);
        rect.setFillColor(sf::Color(220, 220, 220));
        optionBoxes.push_back(rect);
    }
}

void Dropdown::draw(sf::RenderWindow& window) const
{
    window.draw(sprite);
    window.draw(text);

    if (expanded)
    {
        for (size_t i = 0; i < options.size(); ++i)
        {
            window.draw(optionSprites[i]);
            window.draw(options[i]);
        }
    }
}

void Dropdown::handleEvent(const sf::Event& event, const sf::RenderWindow& window)
{
    if (event.type != sf::Event::MouseButtonPressed)
        return;

    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mouseF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

    if (shape.getGlobalBounds().contains(mouseF))
    {
        expanded = !expanded;
        return;
    }

    if (expanded)
    {
        for (size_t i = 0; i < optionBoxes.size(); ++i)
        {
            if (optionBoxes[i].getGlobalBounds().contains(mouseF))
            {
                selectedIndex = static_cast<int>(i);
                text.setString(items[i]);
                expanded = false;
                return;
            }
        }
    }

    expanded = false;
}

std::string Dropdown::getSelectedItem() const
{
    if (selectedIndex >= 0 && selectedIndex < static_cast<int>(items.size()))
        return items[selectedIndex];
    return "";
}
