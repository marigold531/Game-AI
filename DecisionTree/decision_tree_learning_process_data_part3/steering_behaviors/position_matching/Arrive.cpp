#include "Arrive.hpp"

Arrive::Arrive(float maxAcc, float maxSpd, float slowR, float targetR)
{
    maxAcceleration = maxAcc;
    maxSpeed = maxSpd;
    slowRadius = slowR;
    targetRadius = targetR;
    timeToTarget = 0.1;
}

SteeringOutput Arrive::calculateAcceleration(Kinematic character, Kinematic goal)
{
    SteeringOutput result;

    //get the direction to target
    sf::Vector2f direction = goal.position - character.position;
    float distance = character.vectorLength(direction);

    //if we are there steering output will just be zero
    if(distance < targetRadius) {
        result.angularAcceleration = 0.f;
        result.linearAcceleration = sf::Vector2f(0.f, 0.f);
        return result;
    }

    //if we are outside of the slowRadius, then go max speed
    float targetSpeed;
    if(distance > slowRadius) {
        targetSpeed = maxSpeed;
    }
    else {
        targetSpeed = maxSpeed * distance / slowRadius;
    }

    //combines speed and direction to velocity
    sf::Vector2f targetVelocity = direction;
    targetVelocity = character.normalize(targetVelocity);
    targetVelocity *= targetSpeed;

    //accelerates
    result.linearAcceleration = targetVelocity -  character.velocity;
    result.linearAcceleration /= timeToTarget;

    result.angularAcceleration = 0.f;

    return result;
}