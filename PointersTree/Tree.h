//
// Created by trykr on 10.12.2020.
//

#ifndef MISP_LABS_TREE_H
#define MISP_LABS_TREE_H
#include <memory>
#include <iostream>
class Node
{
private:
    int data;
    std::weak_ptr<Node> parent;
    std::shared_ptr<Node> childLeft;
    std::shared_ptr<Node> childRight;
public:
    Node(const int& value);
    int getData();
    ~Node();
    void setLeftChild(std::shared_ptr<Node> node);
    void setRightChild(std::shared_ptr<Node> node);
    void setParent(std::shared_ptr<Node> node);
    void setData(int value);

    std::shared_ptr<Node> getLeftChild();
    std::shared_ptr<Node> getRightChild();
    std::weak_ptr<Node> getParent();
};




class Tree
{
public:
    ~Tree();
    Tree();
    void deleteNode(int value);
    int insertNode(const int &);
    void printAllNodes(Node*);
    Node* findMax(Node*);
    Node* findMin(Node*);
    Node* findNode(Node*, const int &);
    Node* findSuccsessor(const int &);
    std::shared_ptr<Node> getRoot();

private:
    std::shared_ptr<Node> rootNode;
};



#endif //MISP_LABS_TREE_H
