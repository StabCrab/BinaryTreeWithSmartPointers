//
// Created by trykr on 11.12.2020.
//

#include "Tree.h"
int main()
{
    Tree tree;
    tree.insertNode(1);
    tree.insertNode(-1);
    tree.insertNode(5);
    tree.insertNode(7);
    tree.printAllNodes(tree.getRoot().get());
    tree.deleteNode(5);
    tree.printAllNodes(tree.getRoot().get());
}