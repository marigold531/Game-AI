#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include <cmath>
#include <random>

class SteeringOutput
{
    public:
        sf::Vector2f linearAcceleration;
        float angularAcceleration;
        SteeringOutput() 
        {
            linearAcceleration = sf::Vector2f(0.f, 0.f);
            angularAcceleration = 0.f;
        }
};

class Kinematic
{
    private:
        int id;
    public:
        sf::Vector2f position;
        float orientation;

        sf::Vector2f velocity;
        float rotation;

        Kinematic();
        ~Kinematic() {}
        void update(SteeringOutput steering, float maxSpeed, float maxAcceleration, float maxRotation, float maxAngualr, float delTime);
        sf::Vector2f normalize(sf::Vector2f vector);
        float vectorLength(sf::Vector2f vector);
        int random(int low, int high);
};

