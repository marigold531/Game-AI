#include "Align.hpp"
using namespace std;

Align::Align(float targetR, float slowR, float maxRot, float maxAngAcc)
{
    targetRadius = targetR; 
    slowRadius = slowR;
    maxRotation = maxRot;
    maxAngularAcceleration = maxAngAcc;
    timeToTarget = 0.1;
}

SteeringOutput Align::calculateAcceleration(Kinematic character, Kinematic goal)
{
    SteeringOutput result;
    float rotation= goal.orientation - character.orientation;
    
    //map the result (-pi, pi)
    rotation = mapToRange(rotation);

    float rotationSize = fabs(rotation);

    //check if we are there
    if(rotationSize < targetRadius) {
        result.angularAcceleration = 0;
        result.linearAcceleration = sf::Vector2f(0.f, 0.f);
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

    //The final target rotation combines speed
    targetRotation *= rotation / rotationSize;

    //Acceleration tries to get to the target rotation.
    result.angularAcceleration = targetRotation - character.rotation;
    result.angularAcceleration /= timeToTarget;
    //cout << result.angularAcceleration << endl;
    return result;
}

float Align::mapToRange(float theta)
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