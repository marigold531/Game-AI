#pragma once
#include <functional>
#include "../character/Boid.hpp"
#include "../graph/Graph.hpp"

class TreeNode {
    public:
        TreeNode(TreeNode* left, TreeNode* right);
        virtual ~TreeNode();
        virtual int evaluate(Boid& boid, std::vector<sf::RectangleShape*>& tiles, Graph& graph, std::vector<sf::CircleShape>& allItems) = 0;

    protected:
        TreeNode* left;
        TreeNode* right;
};

class ActionNode : public TreeNode {
    public:
        explicit ActionNode(int action, TreeNode* left = nullptr, TreeNode* right = nullptr);
        int evaluate(Boid& boid, std::vector<sf::RectangleShape*>& tiles, Graph& graph, std::vector<sf::CircleShape>& allItems) override;

    private:
        int action;
};

class ConditionNode : public TreeNode {
    public:
        using Condition = std::function<bool(Boid&, std::vector<sf::RectangleShape*>&, Graph&, std::vector<sf::CircleShape>&)>;
        explicit ConditionNode(Condition condition, TreeNode* left, TreeNode* right);
        int evaluate(Boid& boid,  std::vector<sf::RectangleShape*>& tiles, Graph& graph, std::vector<sf::CircleShape>& allItems) override;

    private:
        Condition condition;
};
