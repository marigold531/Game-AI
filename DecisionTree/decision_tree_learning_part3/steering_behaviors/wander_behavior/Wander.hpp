#pragma once

#include "../SteeringBehavior.hpp"
#include "../orientation_matching/Align.hpp"
#include "../position_matching/Arrive.hpp"

class Wander : SteeringBehavior
{
    private:
        float wanderOffset;
        float wanderRadius;
        float wanderRate;
        
        Arrive *arrive;
        Align *align;
        sf::Vector2f targetRtn;
    
    public:
        float wanderOrientation;
        Wander(float offset, float radius, float rate, float orientaiton, Arrive *arriveBeh, Align *alignBeh);
        SteeringOutput calculateAcceleration(Kinematic character, Kinematic goal) override;
        float randomBinomial();
        double random(int low, int high);
        const sf::Vector2f& getTarget() const { return targetRtn; }
};