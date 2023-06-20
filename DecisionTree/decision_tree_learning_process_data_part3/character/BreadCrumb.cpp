#include "BreadCrumb.hpp"

Crumb::Crumb(int id)
{
    this->id = id;
    this->setRadius(3.5);
    this->setFillColor(sf::Color(194, 99, 23));
    this->setPosition(-100, -100);
}

void Crumb::draw(sf::RenderWindow *window)
{
    window->draw(*this);
}

void Crumb::drop(float x, float y)
{
    this->setPosition(x, y);
}

void Crumb::drop(sf::Vector2f position)
{
    this->setPosition(position);
}