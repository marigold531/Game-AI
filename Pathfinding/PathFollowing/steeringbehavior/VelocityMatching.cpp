#include "VelocityMatching.hpp"

SteeringOutput VelocityMatching::calculateAcceleration(Kinematic character, Kinematic goal)
{
    SteeringOutput rtn;

    rtn.linearAcceleration = goal.velocity - character.velocity;
    rtn.angularAcceleration = 0.f;
    return rtn;
}