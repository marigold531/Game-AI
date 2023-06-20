#include "DecisionTree.hpp"
TreeNode::~TreeNode() = default;

DecisionTreeNode::DecisionTreeNode(int attribute, std::vector<TreeNode*> children)
    : attribute(attribute), children(children) {}

DecisionTreeNode::~DecisionTreeNode() {
    for (TreeNode* child : children) {
        delete child;
    }
}

int DecisionTreeNode::evaluate(std::vector<int>& input) {
    int attributeValue = input[attribute];
    return children[attributeValue]->evaluate(input);
}

ActionTreeNode::ActionTreeNode(int action) : action(action) {}

int ActionTreeNode::evaluate(std::vector<int>& input) {
    return action;
}
