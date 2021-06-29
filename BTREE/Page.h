#include "Node.h"
#include <string>
#include <iostream>
#define DEBUG false
#define PAGESIZE 4096
#define TREEHEADER PAGESIZE8
#define MAXKEYS 204
#define ORDER MAXKEYS + 1
#define FREE_SPACE_ON_PAGE (PAGESIZE - ( ( MAXKEYS * 4) + ( MAXKEYS * 8) + (( MAXKEYS + 1)*8) + 3) )

class Page
{
    private:
        short numberOfKeys;
        bool leafStatus;
        void insertNodeInOrder(Node *toInsert);
        void insertionSort();
    public:
        Node *records[MAXKEYS];//Talvez usar NOde*...Provavel q sim
        long childs[ORDER];//children****

        Page();
        Page(bool isLeaf);

        void setNumberOfKeys(int amnt);
        void setLeaf(bool isLeaf);

        int getNumberOfKeys();
        bool isLeaf();
        bool isFull();

        int insertRecord(Node *toInsert);
        int keyBinarySearch(int key, int l, int r);
        Node* popSmaller();
        Page* split();
        string toString();
};
