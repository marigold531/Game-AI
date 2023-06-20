#pragma once
#include "SteeringBehavior.hpp"

class VelocityMatching : public SteeringBehavior
{
    public:
        SteeringOutput calculateAcceleration(Kinematic character, Kinematic goal) override;
};