#include "Wander.hpp"

Wander::Wander(float offset, float radius, float rate, float orientaiton, Arrive *arriveBeh, Align *alignBeh)
{
    wanderOffset = offset;
    wanderRadius = radius;
    wanderRate = rate;
    wanderOrientation = orientaiton;
    align = alignBeh;
    arrive = arriveBeh;
}

SteeringOutput Wander::calculateAcceleration(Kinematic character, Kinematic goal)
{
    SteeringOutput result;
    
    wanderOrientation += randomBinomial() * wanderRate;
    float targetOrientation = wanderOrientation + character.orientation;
    //std::cout << wanderOrientation << "," << character.orientation << std::endl;
    sf::Vector2f target = character.position + wanderOffset * sf::Vector2f(std::cos(character.orientation), std::sin(character.orientation));
    target += wanderRadius * sf::Vector2f(std::cos(targetOrientation), std::sin(targetOrientation));
    targetRtn = target;
    Kinematic targetKinematic;
    targetKinematic.position = target;

    sf::Vector2f positionDifference = target - character.position;
    if (positionDifference.x != 0.0f || positionDifference.y != 0.0f) {
         targetKinematic.orientation = std::atan2(positionDifference.y, positionDifference.x);
    }
    result.angularAcceleration = align->calculateAcceleration(character, targetKinematic).angularAcceleration;
    result.linearAcceleration = arrive->calculateAcceleration(character, targetKinematic).linearAcceleration;

    return result;
}

float Wander::randomBinomial() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(0, 1);

    float random1 = dist(gen);
    float random2 = dist(gen);
    float result = (random1) - (random2);
    return result;
}

float randomFloat(float min, float max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(min, max);
    return dist(gen);
}