#include "Page.h"

/*
Number of keys = 0
Is Leaf = false
*/
Page::Page()
{
    this->setNumberOfKeys(0);
    this->setLeaf(false);
}

Page::Page(bool isLeaf)
{
    this->setNumberOfKeys(0);
    this->setLeaf(isLeaf);
}

void Page::setNumberOfKeys(int amnt)
{
    this->numberOfKeys = (short)amnt;
}

void Page::setLeaf(bool isLeaf)
{
    this->leafStatus = isLeaf;
}