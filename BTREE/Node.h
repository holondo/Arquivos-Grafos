#ifndef NODE_CLASS
#define NODE_CLASS

#define DEFAULT -1;
using namespace std;
class Node
{
    private:
        int key;
        long recordRRN;
    public:
        Node();
        Node(int key, long recordRRN);

        void setKey(int key);
        void setRRN(long RRN);

        int getKey();
        long getRRN();
};

#endif