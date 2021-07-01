#ifndef BTREE_CLASS
#define BTREE_CLASS
#include "Page.h"

#include "student.h"
#include <iostream>
#include <fstream>
#define RECORD_RRN_PLACE (MAXKEYS * 4)
#define CHILDREN_RRN_PLACE (RECORD_RRN_PLACE + (MAXKEYS * 8))
#define NKEYS_PLACE (CHILDREN_RRN_PLACE + ((MAXKEYS +1) * 8))

class ERR_PATH
{
    private:
        long searchPath[MAXKEYS];//pensar
        int top;
    public:
        ERR_PATH();
        void push(long RRN);
        long get();
        long pop();
};

class BTREE
{
    private:
        long rootRRN;
        fstream *treeFile;
        fstream *recordFile;

        long recursiveSearch(long pageRRN, int key, ERR_PATH* path);
        Page* recursiveInsertion(Node* currentNode, ERR_PATH* errorPath);
    public:
        BTREE(string recordFileName, string treeFileName);//FILE if not created, create
        Page* loadPage(long pageRRN);

        void insertStudent(student *toInsert);
        long searchOnTree(int key);
        void updateStudent(student* toUpdate);
        string searchStudent(int keyQuery);
        student* loadStudent(long studentRRN);

        void setRoot(long nodeRRN);
        Node* getNode(long nodeRRN);

        void writePage(Page* toWrite, long pageRRN);
        long writePage(Page* toWrite);
        long getRootRRN();
    
        void close();
};
#endif
