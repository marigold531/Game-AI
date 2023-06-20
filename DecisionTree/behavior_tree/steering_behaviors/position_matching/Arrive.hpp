#pragma once
#include "../SteeringBehavior.hpp"

class Arrive : public SteeringBehavior
{
    private:
        float maxAcceleration;
        float maxSpeed;
        
        float slowRadius;
        float timeToTarget;
    public:
        float targetRadius;
        Arrive(float maxAcc, float maxSpd, float slowR, float targetR);
        SteeringOutput calculateAcceleration(Kinematic character, Kinematic goal) override;
};