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
        this->insertNodeInOrder(toInsert);
        this->setNumberOfKeys(this->getNumberOfKeys() + 1);
        return 1;
    }
    return 0;
}

void Page::insertionSort()
{
    Node* key;
    int i, j;
    for (i = 1; i < this->getNumberOfKeys()+1; i++)
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

/* l: left side of current array
    r: right side of current array
    
    Returns: position in array
            -1 if absent in array

    throws: position where key should be*/
int Page::keyBinarySearch(int key, int l, int r)
{
    if(this->getNumberOfKeys() == 0) throw 0;
    if (r >= l)
    {
        int mid = l + (r - l) / 2;

        if (this->records[mid]->getKey() == key)
            return mid;

        if (this->records[mid]->getKey() > key)
            return keyBinarySearch(key, l, mid - 1);

        if(r == l) 
        {
            if(key > l) throw l+1;
            throw l;
        }
        return keyBinarySearch(key, mid + 1, r);
    }
    return -1;
}

string Page::toString()
{
    string toReturn = "";
    for (int i = 0; i < this->getNumberOfKeys(); i++)
    {
        toReturn += "Key :" + to_string(this->records[i]->getKey());
        toReturn += "\tRRN :" + to_string(this->records[i]->getRRN()) + '\n';
    }
    
    return toReturn;
}