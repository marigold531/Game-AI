#include "ArriveBehavior.hpp"

ArriveBehavior::ArriveBehavior(float tRadius, float sRadius, float mVel, float mAcc)
{
    targetRadius = tRadius;
    slowRadius = sRadius;
    maxVelocity = mVel;
    maxAcceleration = mAcc;
    timeToTarget = 1.f / 60.f;

}

SteeringOutput ArriveBehavior::calculateAcceleration(Kinematic character, Kinematic goal)
{
    //float timeToTarget = elapsedTime;
    
    SteeringOutput result;
    
    //get the direction to the target
    sf::Vector2f direction = goal.position - character.position;

    float distance = character.vectorLength(direction);

    //if we are there steering output will just be zero
    if(distance < targetRadius) {
        result.angularAcceleration = 0.f;
        result.linearAcceleration = sf::Vector2f(0.f, 0.f);
        return result;
    }

    //if we are outside of the slowRadius, then we move at max speed
    float goalSpeed = 0;
    if(distance > slowRadius)
        goalSpeed = maxVelocity;
    else
        goalSpeed = maxVelocity * distance / slowRadius;
    
    //combines speed and direction to velocity
    sf::Vector2f goalVelocity = direction;
    goalVelocity = character.normalize(goalVelocity);
    goalVelocity *= goalSpeed;
    
    //accelerates
    result.linearAcceleration = goalVelocity - character.velocity;
    result.linearAcceleration /= timeToTarget;
    
    result.angularAcceleration = 0;
    return result;
}