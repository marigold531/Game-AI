#include "Boid.hpp"

Boid::Boid(sf::RenderWindow *w, std::string tex, sf::Vector2f initialPos, int type)
{
    window = w;
    if(type == 1) {}
    if(boidTexture.loadFromFile(tex)) {
        sprite.setTexture(boidTexture);
        if(type == 1) {
            sf::IntRect rect(0, 0, 32, 32); // x = 0, y = 0, width = 10, height = 10
            sprite.setTextureRect(rect);
        }
        else if(type ==  2) {
            
            sf::IntRect rect(0, 0, 150, 150); // x = 0, y = 0, width = 10, height = 10
            sprite.setTextureRect(rect);
        }

    } else {
        exit(EXIT_FAILURE);
    }
    if(type == 2)
        sprite.setScale(0.75, 0.75);
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
    initialPosition = initialPos;
    myKinematic = new Kinematic();
    myKinematic->position = initialPos;
    myKinematic->velocity = sf::Vector2f(0.f, 0.f);

    sprite.setPosition(initialPos.x + sprite.getLocalBounds().width, initialPos.y + sprite.getLocalBounds().height / 2);
    sprite.setPosition(initialPos);

    dropTimer = 10.f;
    crumbIdx = 0;
    breadCrumbs = new std::vector<Crumb>;

    maxSpeed = 100.f;
    maxAcceleration = 2000.f;

    maxRotation = 15.f;
    maxAngularAcceleration = 10000.f;

    arrive = new Arrive(2000, 100, 50, 0.001);
    align = new Align(0.001f, 4, 15, 10000);

    stamina = 10;

    path.clear();
    pathKinematic.clear();
    pathIdx = 1;
    canCreateWanderPath = true;
    canCreateFruitPath = true;
}

Kinematic* Boid::getMyKinematic()
{
    return myKinematic;
}

void Boid::draw()
{
    window->draw(sprite);
}

void Boid::update(SteeringOutput input, float delTime)
{   
    
    myKinematic->update(input, maxSpeed, maxAcceleration, maxRotation, maxAngularAcceleration, delTime);

    // Clamp position within window boundaries
    if(myKinematic->position.x > 650) {
        myKinematic->position.x = -10;
    }
        
    else if(myKinematic->position.x < -10) {
        myKinematic->position.x = 650;  
    }
        
    if(myKinematic->position.y > 490) {
        myKinematic->position.y = -10;
    }
        
    else if(myKinematic->position.y < -10) {
        myKinematic->position.y = 480;
    }
    sprite.setPosition(myKinematic->position);
    sprite.setRotation(myKinematic->orientation * (180.0 / M_PI));
    
}

void Boid::update2(Kinematic goal, float delTime)
{
    myKinematic->update(arrive->calculateAcceleration(*myKinematic, goal), maxSpeed, maxAcceleration, maxRotation, maxAngularAcceleration, delTime);
    myKinematic->update(align->calculateAcceleration(*myKinematic, goal), maxSpeed, maxAcceleration, maxRotation, maxAngularAcceleration, delTime);
    
    sprite.setPosition(myKinematic->position);
    sprite.setRotation(myKinematic->orientation * (180.0 / M_PI));
}

void Boid::resetPosition()
{
    sprite.setPosition(initialPosition);
    myKinematic->position = initialPosition;
    pathIdx = 1;
    path.clear();
    pathKinematic.clear();
}