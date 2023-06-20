#pragma once
#include <vector>
#include <functional>
#include "../character/Boid.hpp"
#include "../graph/Graph.hpp"

class TreeNode
{
    public:
        virtual ~TreeNode();
        virtual bool evaluate(std::vector<Boid>& monkeys, Boid& monster, std::vector<sf::RectangleShape*>& tiles, std::vector<sf::CircleShape>& allItems) = 0;
};

class SequenceNode : public TreeNode
{
    private:
        std::vector<TreeNode *> nodes;
    public:
        explicit SequenceNode(std::vector<TreeNode *> &nodes);
        bool evaluate(std::vector<Boid>& monkeys, Boid& monster, std::vector<sf::RectangleShape*>& tiles, std::vector<sf::CircleShape>& allItems) override;
};

class SelectorNode : public TreeNode
{
    private:
        std::vector<TreeNode *> nodes;
    public:
        explicit SelectorNode(std::vector<TreeNode *> &nodes);
        bool evaluate(std::vector<Boid>& monkeys, Boid& monster, std::vector<sf::RectangleShape*>& tiles, std::vector<sf::CircleShape>& allItems) override;
};

class InverterNode : public TreeNode
{
    private:
        TreeNode *node;
    public:
        explicit InverterNode(TreeNode* node);
        bool evaluate(std::vector<Boid>& monkeys, Boid& monster, std::vector<sf::RectangleShape*>& tiles, std::vector<sf::CircleShape>& allItems) override;
};

class ConditionNode : public TreeNode
{
    using Condition = std::function<bool(std::vector<Boid>&, Boid&, std::vector<sf::RectangleShape*>&, std::vector<sf::CircleShape>&)>;
    private:
        Condition condition;
    public:
        explicit ConditionNode(Condition condition);
        //bool evaluate() override;
        bool evaluate(std::vector<Boid>& monkeys, Boid& monster, std::vector<sf::RectangleShape*>& tiles, std::vector<sf::CircleShape>& allItems) override;

};

class ActionNode : public TreeNode
{
    using Action = std::function<bool(std::vector<Boid>&, Boid&, std::vector<sf::RectangleShape*>&, std::vector<sf::CircleShape>&)>;
    private:
        Action action;
    public:
        explicit ActionNode(Action action);
        bool evaluate(std::vector<Boid>& monkeys, Boid& monster, std::vector<sf::RectangleShape*>& tiles, std::vector<sf::CircleShape>& allItems) override;
};