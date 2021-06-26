#include "BTREE.hpp"
#define DEBUG false
BTREE::BTREE(string recordFileName, string treeFileName)
{
    this->treeFile = new fstream(treeFileName, ios::in | ios::out | ios::binary);
    this->recordFile = new fstream(recordFileName, ios::in | ios::out | ios::binary);

    if(this->treeFile->is_open() && this->recordFile->is_open())
    {
        this->treeFile->read((char *) &(this->rootRRN), sizeof(long));
        this->setRoot(this->rootRRN);
        if(DEBUG)cout << "Arquivos estavam abertos. Raiz: " << to_string(this->rootRRN) << '\n';
    }
    else
    {
        this->treeFile = new fstream(treeFileName, ios::in | ios::out | ios::binary | ios::trunc);
        this->recordFile = new fstream(recordFileName, ios::in | ios::out | ios::binary | ios::trunc);
        this->setRoot((long)-1);
        if(DEBUG)cout << "Arquivos criados. Raiz: " << to_string(this->rootRRN) << '\n';
    }    
}

void BTREE::setRoot(long nodeRRN)
{
    this->rootRRN = nodeRRN;
    this->treeFile->seekp(0, ios::beg);

    this->treeFile->write((char *) &nodeRRN, sizeof(long));
}

long BTREE::getRootRRN()
{
    return this->rootRRN;
}

void BTREE::insertStudent(student *toInsert)
{
    if(toInsert == nullptr) throw "Estudante vazio";

    if(this->getRootRRN() == -1)//Se a arvore esta vazia
    {
        Page* rootPage = new Page();
        Node* studentNode = new Node(toInsert->getNUSP(), rootPage->getNumberOfKeys());
        rootPage->insertRecord(studentNode);
        //this->writeRecord();
        this->writePage(rootPage, 0);
        this->setRoot(0);
    }

    else
    {

    }

    // long rrnOnTree /*= searchOnTree(toInsert->key)*/;
    // //if(rrnOnTree != -1)throw "O registro já existe!";

    // //this->recordFile->writeToDatafile(record);
    // Node* currentNode = new Node(toInsert->getNUSP(), rrnOnTree);
}

/*Returns: pageRRN if found.
            -1 if not found
    throws: pageRRN if not found && page is leaf
            -1 if tree is empty*/
long BTREE::searchOnTree(int key)
{
    if(this->getRootRRN() == -1) throw -1;
    long pageRRN = -1;
    try
    {
        pageRRN = this->recursiveSearch(this->getRootRRN(), key);
    }
    catch(long shouldBe)
    {
        throw shouldBe;
    }
    return pageRRN;
}

/*Returns: pageRRN if found.
    throws:pageRRN if not found && page is leaf*/
long BTREE::recursiveSearch(long pageRRN, int key)
{
    Page *currentPage = loadPage(pageRRN);
    if(DEBUG)cout << "Página carregada:\n\t***\n" << currentPage->toString();
    
    int keyPos = -1;

    try
    {
        keyPos = currentPage->keyBinarySearch(key, 0, currentPage->getNumberOfKeys());
        if(keyPos != -1) return pageRRN;//if key is not in the array
    }
    catch(int shouldBe)
    {
        if(currentPage->childs[shouldBe] == -1)
            throw pageRRN;

        return this->recursiveSearch(currentPage->childs[shouldBe], key);
    }    
    return (long)keyPos;//enchendo linguica
}

void BTREE::writePage(Page* toWrite, long pageRRN)
{
    this->treeFile->seekp( ( (pageRRN+1) * PAGESIZE ), ios::beg);
    int keyBuffer = -1;
    long RRNBuffer = -1;
    short shortBuffer = (short)toWrite->getNumberOfKeys();
    bool boolBuffer = toWrite->isLeaf();

    for (int i = 0; i < MAXKEYS; i++)
    {
        if(i < toWrite->getNumberOfKeys())
            keyBuffer = toWrite->records[i]->getKey();
        else
            keyBuffer = -1;
        
        this->treeFile->write((char *) &keyBuffer, sizeof(int));
    }

    for (int i = 0; i < MAXKEYS; i++)
    {
        if(i < toWrite->getNumberOfKeys())
            RRNBuffer = toWrite->records[i]->getRRN();
        else
            RRNBuffer = (long)-1;
        
        this->treeFile->write((char *) &RRNBuffer, sizeof(long));
    }

    for (int i = 0; i < ORDER; i++)
    {
        RRNBuffer = toWrite->childs[i];
        this->treeFile->write((char *) &RRNBuffer, sizeof(long));
    }

    this->treeFile->write((char *) &shortBuffer, sizeof(short));
    this->treeFile->write((char *) &boolBuffer, sizeof(bool));
}

Page* BTREE::loadPage(long pageRRN)
{
    Page* pageToLoad = new Page();
    Node* nodeToLoad;
    int keyBuffer;
    long RRNBuffer;
    short keysAmnt;
    bool leafStatus;

    //Reading numberOfKeys
    this->treeFile->seekg( ( ((pageRRN+1) * PAGESIZE) + NKEYS_PLACE), ios::beg);
    this->treeFile->read((char *) &keysAmnt, sizeof(short));
    if(DEBUG) cout << "Carregando Pagina.\nNumero de chaves: " << to_string(keysAmnt) << '\n';
    pageToLoad->setNumberOfKeys(keysAmnt);

    //Reading isLeaf
    this->treeFile->read((char *)&leafStatus, sizeof(bool));
    pageToLoad->setLeaf(leafStatus);

    this->treeFile->seekg( ( ((pageRRN+1) * PAGESIZE)), ios::beg);
    for(int i = 0; i < keysAmnt; i++)
    {   
        nodeToLoad = new Node();
        this->treeFile->read((char *)&keyBuffer, sizeof(int));
        nodeToLoad->setKey(keyBuffer);
        pageToLoad->records[i] = nodeToLoad;
    }
    
    this->treeFile->seekg( ( ((pageRRN+1) * PAGESIZE) + RECORD_RRN_PLACE), ios::beg);
    for(int i = 0; i < keysAmnt; i++)
    {   
        nodeToLoad = pageToLoad->records[i];
        this->treeFile->read((char *)&RRNBuffer, sizeof(long));
        nodeToLoad->setRRN(RRNBuffer);
    }

    this->treeFile->seekg( ( ((pageRRN+1) * PAGESIZE) + CHIDREN_RRN_PLACE), ios::beg);
    for(int i = 0; i < ORDER; i++)
    {   
        this->treeFile->read((char *)&RRNBuffer, sizeof(long));

        pageToLoad->childs[i] = RRNBuffer;
    }
    return pageToLoad;
}

void BTREE::close()
{
    this->treeFile->close();
    this->recordFile->close();

}
