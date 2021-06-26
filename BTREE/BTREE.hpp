#include "Page.h"
#include "student.h"
#include <iostream>
#include <fstream>
#define NKEYS_PLACE 4088
#define RECORD_RRN_PLACE 816
#define CHIDREN_RRN_PLACE 2448

class BTREE
{
    private:
        long rootRRN;
        fstream *treeFile;
        fstream *recordFile;

        Page* loadPage(long pageRRN);
        long recursiveSearch(long pageRRN, int key);
    public:
        BTREE(string recordFileName, string treeFileName);//FILE if not created, create

        void insertStudent(student *toInsert);
        long searchOnTree(int key);

        void setRoot(long nodeRRN);
        Node* getNode(long nodeRRN);

        void writePage(Page* toWrite, long pageRRN);
        long getRootRRN();

        void close();
};
