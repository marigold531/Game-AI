#pragma once
#include "../steering_behaviors/orientation_matching/Align.hpp"
#include "../steering_behaviors/position_matching/Arrive.hpp"
#include "../steering_behaviors/wander_behavior/Wander.hpp"

#include "BreadCrumb.hpp"

class Boid
{
    private:
        sf::RenderWindow *window;
        sf::Texture boidTexture;
        Kinematic *myKinematic;
        float dropTimer;
        int crumbIdx;

        float maxSpeed;
        float maxAcceleration;
        float maxRotation;
        float maxAngularAcceleration;

        Arrive *arrive;
        Align *align;

        

    public:
        sf::Sprite sprite;
        std::vector<Crumb>* breadCrumbs;
        Boid(sf::RenderWindow *w, std::string tex, sf::Vector2f initialPos);
        ~Boid(){}
        void draw();
        void update(SteeringOutput input, float delTime);
        void update2(Kinematic goal, float delTime);
        Kinematic* getMyKinematic();
        int foodLevel;

};