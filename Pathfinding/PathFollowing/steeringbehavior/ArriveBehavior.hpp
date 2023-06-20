#pragma once
#include "SteeringBehavior.hpp"

class ArriveBehavior : public SteeringBehavior
{
    private:
        float targetRadius;
        float slowRadius;
        float maxVelocity;
        float maxAcceleration;
        float timeToTarget;

    public:
        //ArriveBehavior(){}
        ArriveBehavior(float tRadius, float sRadius, float mVel, float mAcc);
        SteeringOutput calculateAcceleration(Kinematic character, Kinematic goal);
};