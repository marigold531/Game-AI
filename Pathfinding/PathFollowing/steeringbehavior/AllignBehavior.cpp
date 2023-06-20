#include "AllignBehavior.hpp"

AllignBehavior:: AllignBehavior(float tRadius, float sRadius, float maxRot, float maxAng)
{
    targetRadius = tRadius;
    slowRadius = sRadius;
    maxRotation = maxRot;
    maxAngularRotation = maxAng;
    timeToTarget = (1.f / 60.f);
}

SteeringOutput AllignBehavior::calculateAcceleration(Kinematic character, Kinematic goal)
{
    SteeringOutput result;
    float rotation = goal.oreientation - character.oreientation;
    
    //Map the result to (-pi, pi)
    rotation = mapToRange(rotation);
    
    
    float rotationSize = fabs(rotation);
    //std::cout << "bir brothaa: " << rotation << "   comparing:  " << targetRadius <<  std::endl;
    //check if we are there, return
    if(rotationSize < targetRadius) {
        result.angularAcceleration = 0;
        result.linearAcceleration = sf::Vector2f(0, 0);
        return result;
    }

    //outside of slowRadius
    float targetRotation;
    if(rotationSize > slowRadius) {
        targetRotation = maxRotation;
    }
    else {
        targetRotation = maxRotation * rotationSize / slowRadius;
    }

    targetRotation *= rotation / rotationSize;

    result.angularAcceleration = targetRotation - character.rotation;
    result.angularAcceleration /= timeToTarget;
    
    return result;
}

float AllignBehavior::mapToRange(float theta)
{
    float r = fmod(theta, (2 * M_PI));  
    if(fabs(r) <= M_PI) {
        return r;
    }
    if(r > M_PI) {
        return r - 2 * M_PI;
    }
    else {
        return 2 * M_PI + r;
    }
}