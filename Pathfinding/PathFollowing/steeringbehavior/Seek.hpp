#pragma once
#include "SteeringBehavior.hpp"

class Seek : public SteeringBehavior
{
    private:
        float maxAcceleration;
    public:
        Seek(float maxAcc);
        SteeringOutput calculateAcceleration(Kinematic character, Kinematic target) override;
};