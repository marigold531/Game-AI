#include "Boid.hpp"

Boid::Boid(sf::RenderWindow *w, std::string tex, sf::Vector2f initialPos)
{
    window = w;
    if(boidTexture.loadFromFile(tex)) {
        sprite.setTexture(boidTexture);
    } else {
        exit(EXIT_FAILURE);
    }
    sprite.setScale(0.025, 0.025);
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
    myKinematic = new Kinematic();

    maxSpeed = 200.f;
    maxAcceleration = 2000.f;

    maxRotation = 15.f;
    maxAngularAcceleration = 10000.f;

    myKinematic->position = initialPos; 
    myKinematic->velocity = sf::Vector2f(0.f, 0.f);
    sprite.setPosition(initialPos.x + sprite.getLocalBounds().width, initialPos.y + sprite.getLocalBounds().height / 2);
    sprite.setPosition(initialPos);
    mouseClickArrive = new ArriveBehavior(0.035, 50.f, maxSpeed, maxAcceleration);
    allignRotation = new AllignBehavior( 0.001f, 4.f, maxRotation, maxAngularAcceleration);
    mouseVelocityMatching = VelocityMatching();

    //breadcrumbs
    //breadcrumbs
    dropTimer = 10.f;
    crumbIdx = 0;
    breadCrumbs = new vector<Crumb>;
    
    for(int i = 0; i < 21; i++) {
        Crumb c(i);
        breadCrumbs->push_back(c);
    } 
}

void Boid::draw()
{
    window->draw(sprite);
}



Kinematic* Boid::getMyKinematic()
{
    return myKinematic;
}

void Boid::update(Kinematic goal, float delTime)
{   
    if(dropTimer > 0){
        dropTimer -= 1;
    }
    else {
        dropTimer = 20.f;
        breadCrumbs->at(crumbIdx).drop(myKinematic->position);
        if(crumbIdx < 20) {
            crumbIdx++;
        }
        else {
            crumbIdx = 0;
        }
    }
    // std::cout << "my pos: " << myKinematic->position.x << ", " << myKinematic->position.y << endl;
    // std::cout << "goal pos: " << goal.position.x << ", " << goal.position.y << endl;
    
    //myKinematic->update(mouseVelocityMatching.calculateAcceleration(*myKinematic, goal), maxSpeed, maxAcceleration, maxRotation, maxAngularAcceleration, delTime);
    
    myKinematic->update(mouseClickArrive->calculateAcceleration(*myKinematic, goal), maxSpeed, maxAcceleration, maxRotation, maxAngularAcceleration, delTime);
    myKinematic->update(allignRotation->calculateAcceleration(*myKinematic, goal), maxSpeed, maxAcceleration, maxRotation, maxAngularAcceleration, delTime);
    sprite.setPosition(myKinematic->position);
    sprite.setRotation(myKinematic->oreientation * (180.0 / M_PI));
    
}

void Boid::updateFollowPath(std::vector<Kinematic *> *path, float delTime)
{
    if(dropTimer > 0){
        dropTimer -= 1;
    }
    else {
        dropTimer = 7.f;
        breadCrumbs->at(crumbIdx).drop(myKinematic->position);
        if(crumbIdx < 16) {
            crumbIdx++;
        }
        else {
            crumbIdx = 0;
        }
    }
    // for(auto k : *path) {
    //     cout << "pos" << k->position.x << " " << k->position.y << endl;
    // }

}


Boid::~Boid()
{

}