//
// Created by trykr on 12.12.2020.
//
#include "Tree.h"

Node::Node(const int &value)
{
    std::cout << "Node:" + std::to_string(value) + " created" << std::endl;
    data = value;

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

void Node::setData(int value)
{
    data = value;
}

Node::~Node()
{
    std::cout << "Node:" + std::to_string(data) + " destructed" << std::endl;
}

std::shared_ptr<Node> Node::getLeftChild() {
    return childLeft;
}

std::shared_ptr<Node> Node::getRightChild()
{
    return childRight;
}

std::weak_ptr<Node> Node::getParent() {
    return parent;
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
    if(node->getLeftChild() == nullptr || node->getRightChild() == nullptr)               /* в этой и следующих двух строках ищем вершину removedNode, которую мы потом вырежем из дерева. Это либо node, либо следующий за node */
        removedNode = node;
    else
        removedNode = findSuccsessor(node->getData());
    if(removedNode->getLeftChild() != nullptr)                                  /* nodeReplacement - указатель на существующего ребенка removedNode или 0 если таковых нет */
        nodeReplacement = removedNode->getLeftChild();
    else
        nodeReplacement = removedNode->getRightChild();
    if(removedNode != node)
    {
        int temp = node->getData();
        node->setData(removedNode->getData());
        removedNode->setData(temp);
    }
    if(nodeReplacement != nullptr)                                        /* эта и следующие 9 строк - вырезание removedNode */
        nodeReplacement->setParent(removedNode->getParent().lock());
    if(removedNode->getParent().lock() == nullptr)
        rootNode = std::shared_ptr<Node>(nodeReplacement);
    else
    {
        if (removedNode == (removedNode->getParent()).lock()->getLeftChild().get())
            (removedNode->getParent()).lock()->setLeftChild(nodeReplacement); // тут может сломаться
        else
            (removedNode->getParent()).lock()->setRightChild(nodeReplacement);
    }

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
            ptr = ptr.get()->getLeftChild();
        else
            ptr = ptr.get()->getRightChild();
    }
    newNode->setParent(ptr1);
    if(ptr1 == nullptr)
    {
        rootNode = newNode;
    }
    else
    {
        if(value < ptr1->getData())
            ptr1->setLeftChild(std::shared_ptr<Node>(newNode));
        else
            ptr1->setRightChild(std::shared_ptr<Node>(newNode));
    }
    return 0;
}


void Tree::printAllNodes(Node *node)
{
    if(node != nullptr)
    {
        printAllNodes(node->getLeftChild().get());
        std::cout << node->getData() << std::endl;
        printAllNodes(node->getRightChild().get());
    }
}


Node* Tree::findSuccsessor(const int & val)
{
    Node* x= findNode(rootNode.get(), val);
    Node* y;
    if(x == nullptr)
        return nullptr;
    if (x->getRightChild() != nullptr)
        return findMin(x->getRightChild().get());
    y = x->getParent().lock().get();
    while (y != nullptr && x == y->getRightChild().get())
    {
        x = y;
        y = y->getParent().lock().get();
    }
    return y;
}


Node* Tree::findMax(Node *x)
{
    while(x->getRightChild() != nullptr)
        x = x->getRightChild().get();
    return x;
}

Node* Tree::findMin(Node* x)
{
    while(x->getLeftChild() != nullptr)
        x=x->getLeftChild().get();
    return x;
}

Node* Tree::findNode(Node * n, const int & val)
{
    if (n == 0 || val == n->getData())
        return n;
    if(val > n->getData())
        return findNode(n->getRightChild().get(), val);
    else
        return findNode(n->getLeftChild().get(), val);
}

std::shared_ptr<Node> Tree::getRoot() {
    return rootNode;
}

Tree::~Tree()
{

}

