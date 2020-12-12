//
// Created by trykr on 12.12.2020.
//
#include "Tree.h"

Node::Node(const int &value)
{
    std::cout << "Node:" + std::to_string(value) + " created" << std::endl;
    data = value;
    //parent = nullptr;
    //childLeft = nullptr;
    //childRight = nullptr;
}

int Node::getData()
{
    return data;
}

void Node::setLeftChild(std::shared_ptr<Node> node)
{
    childLeft = node;
}

void Node::setRightChild(std::shared_ptr<Node> node)
{
    childRight = node;
}

void Node::setParent(std::shared_ptr<Node> node)
{
    parent = std::weak_ptr<Node>(node);
}

Node::~Node()
{
    std::cout << "Node:" + std::to_string(data) + " destructed" << std::endl;
}

Tree::Tree()
{
    rootNode = nullptr;
}

void Tree::deleteNode(int value)
{
    Node* node = findNode(rootNode.get(), value);
    Node* removedNode;
    std::shared_ptr<Node> nodeReplacement;
    if(node->childLeft == nullptr || node->childRight == nullptr)               /* в этой и следующих двух строках ищем вершину removedNode, которую мы потом вырежем из дерева. Это либо node, либо следующий за node */
        removedNode = node;
    else
        removedNode = findSuccsessor(node->getData());
    if(removedNode->childLeft != nullptr)                                  /* nodeReplacement - указатель на существующего ребенка removedNode или 0 если таковых нет */
        nodeReplacement = removedNode->childLeft;
    else
        nodeReplacement = removedNode->childRight;
    if(nodeReplacement != nullptr)                                        /* эта и следующие 9 строк - вырезание removedNode */
        nodeReplacement->setParent(removedNode->parent.lock());
    if(removedNode->parent.lock() == nullptr)
        rootNode = std::shared_ptr<Node>(nodeReplacement);
    else
    {
        if (removedNode == (removedNode->parent).lock()->childLeft.get())
            (removedNode->parent).lock()->setLeftChild(nodeReplacement);
        else
            (removedNode->parent).lock()->setRightChild(nodeReplacement);
    }
    if(removedNode != node)
        node->data = removedNode->getData();
}


int Tree::insertNode(const int &value)
{
    std::shared_ptr<Node> newNode = std::make_shared<Node>(value);
    std::shared_ptr<Node> ptr(rootNode);
    std::shared_ptr<Node> ptr1;

    while(ptr != nullptr)
    {
        ptr1 = ptr;
        if (value < ptr.get()->getData())
            ptr = ptr.get()->childLeft;
        else
            ptr = ptr.get()->childRight;
    }
    newNode->parent = ptr1;
    if(ptr1 == nullptr)
    {
        rootNode = newNode;
    }
    else
    {
        if(value < ptr1->getData())
            ptr1->childLeft = std::shared_ptr<Node>(newNode);
        else
            ptr1->childRight = std::shared_ptr<Node>(newNode);
    }
    return 0;
}


void Tree::printAllNodes(Node *node)
{
    if(node != nullptr)
    {
        printAllNodes(node->childLeft.get());
        std::cout << node->getData() << std::endl;
        printAllNodes(node->childRight.get());
    }
}


Node* Tree::findSuccsessor(const int & val)
{
    Node* x= findNode(rootNode.get(), val);
    Node* y;
    if(x == nullptr)
        return nullptr;
    if (x->childRight != nullptr)
        return findMin(x->childRight.get());
    y = x->parent.lock().get();
    while (y != nullptr && x == y->childRight.get())
    {
        x = y;
        y = y->parent.lock().get();
    }
    return y;
}


Node* Tree::findMax(Node *x)
{
    while(x->childRight != nullptr)
        x = x->childRight.get();
    return x;
}

Node* Tree::findMin(Node* x)
{
    while(x->childLeft != nullptr)
        x=x->childLeft.get();
    return x;
}

Node* Tree::findNode(Node * n, const int & val)
{
    if (n == 0 || val == n->getData())
        return n;
    if(val > n->getData())
        return findNode(n->childRight.get(), val);
    else
        return findNode(n->childLeft.get(), val);
}

std::shared_ptr<Node> Tree::getRoot() {
    return rootNode;
}
