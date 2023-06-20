#include "Seek.hpp"

Seek::Seek(float maxAcc)
{
    maxAcceleration = maxAcc;
}

SteeringOutput Seek::calculateAcceleration(Kinematic character, Kinematic target)
{
    SteeringOutput result;
    result.linearAcceleration = target.position - character.position;
    result.linearAcceleration = character.normalize(result.linearAcceleration);
    result.linearAcceleration *= maxAcceleration;
    result.angularAcceleration = 0;

    return result;
}
