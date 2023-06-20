#pragma once
#include "../SteeringBehavior.hpp"

class Align : public SteeringBehavior
{
    private:
        float targetRadius;
        float slowRadius;
        float maxRotation;
        float maxAngularAcceleration;
        float timeToTarget;
    public:
        Align(float targetR, float slowR, float maxRot, float maxAngAcc);
        SteeringOutput calculateAcceleration(Kinematic character, Kinematic goal) override;
        float mapToRange(float theta);
};