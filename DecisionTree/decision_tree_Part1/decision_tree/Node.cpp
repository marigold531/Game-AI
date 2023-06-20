#include "Node.hpp"

// TreeNode
TreeNode::TreeNode(TreeNode* left, TreeNode* right) : left(left), right(right) {}
TreeNode::~TreeNode() = default;

ActionNode::ActionNode(int action, TreeNode* left, TreeNode* right) : TreeNode(left, right), action(action) {}
int ActionNode::evaluate(Boid& boid,  std::vector<sf::RectangleShape*>& tiles,  Graph& graph, std::vector<sf::CircleShape>& allItems) {
    return action;
}

// ConditionNode
ConditionNode::ConditionNode(Condition condition, TreeNode* left, TreeNode* right) : TreeNode(left, right), condition(condition) {}
int ConditionNode::evaluate(Boid& boid,  std::vector<sf::RectangleShape*>& tiles,  Graph& graph, std::vector<sf::CircleShape>& allItems) {
    if(condition(boid, tiles, graph, allItems)) {
        return left->evaluate(boid, tiles, graph, allItems);
    } else {
        return right->evaluate(boid, tiles, graph, allItems);
    }
}
