#pragma once
#include "../kinematic/Kinematic.hpp"

class SteeringBehavior 
{
    public:
        virtual SteeringOutput calculateAcceleration(Kinematic character, Kinematic target) = 0;
};