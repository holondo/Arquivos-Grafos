#include "Page.h"

/*
Number of keys = 0
Is Leaf = false
*/
Page::Page()
{
    this->setNumberOfKeys(0);
    this->setLeaf(true);

    for(int i = 0; i < ORDER; i++)
    {
        this->childs[i] = -1;
    }
}

Page::Page(bool isLeaf)
{
    this->setNumberOfKeys(0);
    this->setLeaf(isLeaf);

    for(int i = 0; i < ORDER; i++)
    {
        this->childs[i] = -1;
    }
}

void Page::setNumberOfKeys(int amnt)
{
    this->numberOfKeys = (short)amnt;
}

void Page::setLeaf(bool isLeaf)
{
    this->leafStatus = isLeaf;
}

int Page::getNumberOfKeys()
{
    return this->numberOfKeys;
}

bool Page::isLeaf()
{
    return this->leafStatus;
}
bool Page::isFull()
{
    if(this->getNumberOfKeys() >= MAXKEYS)
        return true;

    else return false;
}

void Page::insertNodeInOrder(Node* toInsert)
{
    this->records[this->getNumberOfKeys()] = toInsert;
    insertionSort(); 
}

int Page::insertRecord(Node* toInsert)
{
    if(toInsert == nullptr || !this->isLeaf())
        throw "Erro";//ver comofas excessao direito

    if(this->isFull())
    {

    }

    else
    {
        insertNodeInOrder(toInsert);
        this->setNumberOfKeys(this->getNumberOfKeys() + 1);
        return 1;
    }
    return 0;
}

void Page::insertionSort()
{
    Node* key;
    int i, j;
    for (i = 1; i < this->getNumberOfKeys(); i++)
    {
        key = this->records[i];
        j = i - 1;

        while (j >= 0 && this->records[j]->getKey() > key->getKey())
        {
            this->records[j + 1] = this->records[j];
            j = j - 1;
        }
        this->records[j + 1] = key;
    }
}