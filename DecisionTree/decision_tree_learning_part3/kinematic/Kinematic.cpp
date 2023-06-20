#include "Kinematic.hpp"

Kinematic::Kinematic() 
{
    position = sf::Vector2f(0.f, 0.f);
    orientation = 0; 

    velocity = sf::Vector2f(0.f, 0.f);
    rotation = 0;
}

void Kinematic::update(SteeringOutput steering, float maxSpeed, float maxAcceleration, float maxRotation, float maxAngular, float delTime)
{
    //clip acceleration
    if(vectorLength(steering.linearAcceleration) > maxAcceleration) {
        steering.linearAcceleration = normalize(steering.linearAcceleration);
        steering.linearAcceleration *= maxAcceleration;
        //printf("stop\n");
    }
    float angularAcceleration = fabs(steering.angularAcceleration);
    if(angularAcceleration > maxAngular) {
        steering.angularAcceleration /= angularAcceleration;
        steering.angularAcceleration *= maxAngular;
        //printf("hi\n");
    }
    if(angularAcceleration == 0) {
        rotation = 0;
    }
    //update position and orientation
    position += velocity * delTime;
    orientation += rotation * delTime;

    //update velocity and rotation
    velocity += steering.linearAcceleration * delTime;
    rotation += steering.angularAcceleration * delTime;
    
    if(vectorLength(velocity) > maxSpeed) {
        velocity = normalize(velocity);
        velocity *= maxSpeed;
    }
    if(fabs(rotation) > maxRotation) {
        rotation = (rotation > 0) ? maxRotation : -maxRotation;
    }
}

float Kinematic::vectorLength(sf::Vector2f vector)
{
    return sqrt(vector.x * vector.x + vector.y * vector.y);
}


sf::Vector2f Kinematic::normalize(sf::Vector2f vector)
{
    float length = vectorLength(vector);
    vector.x /= length;
    vector.y /= length;  
    return vector;
}

int Kinematic::random(int low, int high)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(low, high);
    return distr(gen);
}