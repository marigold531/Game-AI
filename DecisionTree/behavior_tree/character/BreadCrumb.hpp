#pragma once
#include <SFML/Graphics.hpp>

class Crumb : sf::CircleShape
{
    public:
        Crumb(int id);
        void draw(sf::RenderWindow *window);
        void drop(float x, float y);
        void drop(sf::Vector2f position);
        
    private:
        int id;
};