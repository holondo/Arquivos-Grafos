#include "Node.h"

Node::Node()
{
    this->key = DEFAULT;
    this->recordRRN = DEFAULT;
}

Node::Node(int key, long recordRRN)
{
    setKey(key);
    setRRN(recordRRN);
}

void Node::setKey(int key)
{
    this->key = key;
}
void Node::setRRN(long RRN)
{
    this->recordRRN = RRN;
}

int Node::getKey()
{
    return this->key;
}
long Node::getRRN()
{
    return this->recordRRN;
}