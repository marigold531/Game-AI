#include "BehaviorTree.hpp"

TreeNode::~TreeNode() = default;

SequenceNode::SequenceNode(std::vector<TreeNode*>& nodes) : nodes(nodes) {}

bool SequenceNode::evaluate(std::vector<Boid>& monkeys, Boid& monster, std::vector<sf::RectangleShape*>& tiles, std::vector<sf::CircleShape>& allItems)
{
    for (auto &node : nodes)
    {
        if (!node->evaluate(monkeys, monster, tiles, allItems))
            return false;
    }
    return true;
}

SelectorNode::SelectorNode(std::vector<TreeNode*>& nodes) : nodes(nodes) {}

bool SelectorNode::evaluate(std::vector<Boid>& monkeys, Boid& monster, std::vector<sf::RectangleShape*>& tiles, std::vector<sf::CircleShape>& allItems)
{
    for (auto &node : nodes)
    {
        if (node->evaluate(monkeys, monster, tiles, allItems))
            return true;
    }
    return false;
}

InverterNode::InverterNode(TreeNode* node) : node(node) {}

bool InverterNode::evaluate(std::vector<Boid>& monkeys, Boid& monster, std::vector<sf::RectangleShape*>& tiles, std::vector<sf::CircleShape>& allItems)
{
    return !node->evaluate(monkeys, monster, tiles, allItems);
}

ConditionNode::ConditionNode(Condition condition) : condition(condition) {}

bool ConditionNode::evaluate(std::vector<Boid>& monkeys, Boid& monster, std::vector<sf::RectangleShape*>& tiles, std::vector<sf::CircleShape>& allItems) {
    return condition(monkeys, monster, tiles, allItems);
}

ActionNode::ActionNode(Action action) : action(action) {}

bool ActionNode::evaluate(std::vector<Boid>& monkeys, Boid& monster, std::vector<sf::RectangleShape*>& tiles, std::vector<sf::CircleShape>& allItems) {
    return action(monkeys, monster, tiles, allItems);
}