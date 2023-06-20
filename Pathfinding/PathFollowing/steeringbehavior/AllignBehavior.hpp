#pragma once

#include "SteeringBehavior.hpp"

class AllignBehavior
{
    private:
        float targetRadius;
        float slowRadius;
        float timeToTarget;
        float maxRotation;
        float maxAngularRotation;
    public:
        AllignBehavior(float tRadius, float sRadius, float maxRot, float maxAng);
        SteeringOutput calculateAcceleration(Kinematic character, Kinematic goal);
        float mapToRange(float theta);
};