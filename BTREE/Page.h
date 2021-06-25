#include "Node.h"
#include <string>
#define PAGESIZE 4096
#define TREEHEADER PAGESIZE8
#define MAXKEYS 204
#define ORDER MAXKEYS + 1

class Page
{
    private:
        short numberOfKeys;
        bool leafStatus;
        void insertNodeInOrder(Node *toInsert);
        void insertionSort();
    public:
        Node *records[MAXKEYS];//Talvez usar NOde*...Provavel q sim
        long childs[ORDER];

        Page();
        Page(bool isLeaf);

        void setNumberOfKeys(int amnt);
        void setLeaf(bool isLeaf);

        int getNumberOfKeys();
        bool isLeaf();
        bool isFull();

        int insertRecord(Node *toInsert);
        int keyBinarySearch(int key, int l, int r);
        string toString();
};
