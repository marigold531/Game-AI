#pragma once
#include "../steeringbehavior/VelocityMatching.hpp"
#include "../steeringbehavior/ArriveBehavior.hpp"
#include "../steeringbehavior/AllignBehavior.hpp"
#include "../steeringbehavior/Seek.hpp"
#include "BreadCrumb.hpp"

using namespace std;
class Boid
{
    private:
        
        sf::RenderWindow *window;
        sf::Texture boidTexture;

        Kinematic *myKinematic;

        float maxSpeed;
        float maxAcceleration;

        float maxRotation;
        float maxAngularAcceleration;


        VelocityMatching mouseVelocityMatching;
        ArriveBehavior *mouseClickArrive;
        AllignBehavior *allignRotation;

        float dropTimer;
        
        int crumbIdx;

    public:
        sf::Sprite sprite;
        Boid(sf::RenderWindow *w, std::string tex, sf::Vector2f initialPos);
        ~Boid();
        
        void draw();
        void update(Kinematic goal, float delTime);
        void updateFollowPath(std::vector<Kinematic *> *path, float delTime);

        Kinematic* getMyKinematic();
        void move();

        vector<Crumb>* breadCrumbs;
};