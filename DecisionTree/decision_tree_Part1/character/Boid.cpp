#include "Boid.hpp"

Boid::Boid(sf::RenderWindow *w, std::string tex, sf::Vector2f initialPos)
{
    window = w;
    if(boidTexture.loadFromFile(tex)) {
        sprite.setTexture(boidTexture);
    } else {
        exit(EXIT_FAILURE);
    }

    sprite.setScale(0.018, 0.018);
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);

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

    foodLevel = 10;
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