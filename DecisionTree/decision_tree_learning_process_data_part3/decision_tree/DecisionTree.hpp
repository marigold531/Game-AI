#pragma once

#include <vector>

class TreeNode {
public:
    virtual ~TreeNode();
    virtual int evaluate(std::vector<int>& input) = 0;
};

class DecisionTreeNode : public TreeNode {
public:
    DecisionTreeNode(int attribute, std::vector<TreeNode*> children);
    ~DecisionTreeNode();

    int evaluate(std::vector<int>& input) override;

private:
    int attribute;
    std::vector<TreeNode*> children;
};

class ActionTreeNode : public TreeNode {
public:
    ActionTreeNode(int action);

    int evaluate(std::vector<int>& input) override;

private:
    int action;
};

