#include "Node.h"
#define PAGESIZE 4096
#define TREEHEADER PAGESIZE8
#define MAXKEYS 204

class Page
{
    private:
        short numberOfKeys ;
        bool leafStatus;
    public:
        Node records[MAXKEYS];//Talvez usar NOde*...Provavel q sim
        long childs[MAXKEYS + 1];

        Page();
        Page(bool isLeaf);

        void Page::setNumberOfKeys(int amnt);
        void Page::setLeaf(bool isLeaf);

        int getNumberOfKeys();
        bool isLeaf();
};
