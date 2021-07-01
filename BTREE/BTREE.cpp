#include "BTREE.hpp"
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

/*void BTREE::insertStudent(student *toInsert)
{
    if(toInsert == nullptr) throw "Estudante vazio";
    if(DEBUG) cout << "iniciando inserção. Estudante => " << toInsert->getNome() << '\n';
    if(this->getRootRRN() == -1)//Se a arvore esta vazia
    {
        Page* rootPage = new Page();
        Node* studentNode = toInsert->WriteInFile();
        
        rootPage->insertRecord(studentNode);
        this->writePage(rootPage, 0);
        this->setRoot(0);
    }

    else
    {
        if(DEBUG) cout << "Arvore não estava vazia\n";
        long placeOnTree = -1;
        try
        {
            placeOnTree = this->searchOnTree(toInsert->getNUSP());
            if(DEBUG) cout << "Estudante encontrado na página => " << placeOnTree << '\n';
        }
        catch(long pageRRNToInsert)
        {
            if(DEBUG) cout << "Inserindo novo estudante na página => " << pageRRNToInsert << '\n';
            if(pageRRNToInsert != -1)
            {
                Node* currentNode = toInsert->WriteInFile();
                Page* originalLeafToInsert = this->loadPage(pageRRNToInsert);
                Page* splittedLeaf;
                Page* promottedPage;

                if(originalLeafToInsert->isFull())
                {
                    splittedLeaf = originalLeafToInsert->split();
                    splittedLeaf->insertRecord(currentNode);
                }
                else
                {
                    originalLeafToInsert->insertRecord(currentNode);
                    this->writePage(originalLeafToInsert, pageRRNToInsert);
                }
            }
        }
        
    }
}*/

void BTREE::insertStudent(student *toInsert)
{
    if(this->getRootRRN() == -1)
    {
        Page* rootPage = new Page();
        Node* currentNode = toInsert->WriteInFile();

        rootPage->insertRecord(currentNode);
        
        this->writePage(rootPage, 0);
        this->setRoot(0);
    }

    else
    {
        long foundRRN = -1;
        try
        {
            foundRRN = this->searchOnTree(toInsert->getNUSP());
            if(foundRRN != -1)throw (string)"Registro já inserido!\n";
        }
        catch(ERR_PATH* searchErrorPath)
        {
            Node* currentNode = toInsert->WriteInFile();
            this->recursiveInsertion(currentNode, searchErrorPath);
            free(currentNode);
        }
        
    }
}

Page* BTREE::recursiveInsertion(Node* currentNode, ERR_PATH* errorPath)
{
    long RRNCur = errorPath->pop();

    Page* currentPage = this->loadPage(RRNCur);

    if(currentPage->isFull())
    {
        Page* splittedPage = currentPage->split();
        splittedPage->insertRecord(currentNode);

        Node* smallerNode = splittedPage->popSmaller();
        if(DEBUG) cout << "Menor nó => " << smallerNode->getKey() << '\n';

        //If currentPage was the root of the tree
        if(this->getRootRRN() == RRNCur)
        {
            Page* newRootPage = new Page(false);//The root isn't leaf anymore

            newRootPage->insertRecord(smallerNode);
            newRootPage->childs[0] = this->getRootRRN();//The old root is now the first child
            newRootPage->childs[newRootPage->getNumberOfKeys()] = this->writePage(splittedPage);
            this->writePage(currentPage, RRNCur);
            this->setRoot(this->writePage(newRootPage));
        }

        //If currentPage wasn't the root
        else
        {
            Page* motherPage = this->recursiveInsertion(smallerNode, errorPath);

            motherPage->childs[motherPage->getNumberOfKeys()] = this->writePage(splittedPage);
            this->writePage(motherPage);
            free(motherPage);
            free(currentPage);
            return splittedPage;
        }
        return currentPage;//vertbm
    }

    else
    {
        //cout << "\nINSERÇÃO: Pagina com espaço\n\t***\n" << currentPage->toString();
        currentPage->insertRecord(currentNode);
        this->writePage(currentPage, RRNCur);
        return currentPage;
    }
}

/*Returns:
            pageRRN if found.
            -1 if not found
    throws:
            ERR_PATH if not found && page is leaf
            -1 if tree is empty*/
long BTREE::searchOnTree(int key)
{
    if(this->getRootRRN() == -1) throw -1;//MUDAR P/ ERR
    long pageRRN = -1;

    ERR_PATH *path = new ERR_PATH();
    try
    {
        pageRRN = this->recursiveSearch(this->getRootRRN(), key, path);
    }
    catch(ERR_PATH* finishedPath)
    {
        if(DEBUG) cout << "Volta a Search on tree. Chave throw => " << finishedPath->get() << '\n';
        throw finishedPath;
    }
    return pageRRN;
}

/*Returns: pageRRN if found.
    throws:ERR_PATH if not found && page is leaf*/
long BTREE::recursiveSearch(long pageRRN, int key, ERR_PATH* path)
{
    Page *currentPage = loadPage(pageRRN);
    path->push(pageRRN);

    if(DEBUG)cout << "Recursive search - Página carregada:\n\t***\n" << currentPage->toString();
    
    int keyPos = -1;

    try
    {
        keyPos = currentPage->keyBinarySearch(key, 0, currentPage->getNumberOfKeys() -1);
        if(keyPos != -1) return pageRRN;//if key is not in the array
    }
    catch(int shouldBe)
    {
        if(DEBUG) cout << "Recursive search - de volta\n\t Proxima pag =>" << currentPage->childs[shouldBe] << '\n';
        if(currentPage->childs[shouldBe] == -1)
            throw path;

        return this->recursiveSearch(currentPage->childs[shouldBe], key, path);
    }    
    return (long)keyPos;//enchendo linguica
}

void BTREE::updateStudent(student* toUpdate)
{
    try
    {
        long RRNPage = this->searchOnTree(toUpdate->getNUSP());
        Page* currentPage = this->loadPage(RRNPage);

        Node* studentRef = currentPage->records[currentPage->keyBinarySearch(toUpdate->getNUSP(), 0, currentPage->getNumberOfKeys() - 1)];
        toUpdate->UpdateInFile(studentRef);
        free(currentPage);
        free(studentRef);
    }
    catch(ERR_PATH *e)
    {
        throw (string)"Registro não encontrado!\n";
    }
    
}

string BTREE::searchStudent(int keyQuery)
{
    int foundRRN = -1;
    try
    {
        foundRRN = this->searchOnTree(keyQuery);
    }
    catch(ERR_PATH* e)
    {
        free(e);
        return (string) "Registro nao encontrado!\n";
    }

    Page* foundPage = this->loadPage(foundRRN);
    Node* foundNode = foundPage->records[foundPage->keyBinarySearch(keyQuery, 0, foundPage->getNumberOfKeys() -1)];

    student* foundStudent = this->loadStudent(foundNode->getRRN());

    string content = foundStudent->toString();

    free(foundPage);
    free(foundNode);
    free(foundStudent);
    return content;
}

student* BTREE::loadStudent(long studentRRN)
{
    this->recordFile->seekg(studentRRN * STUDENT_SIZE, ios::beg);

    int nUSP;
    char nome[MAX_STRING];
    char sobrenome[MAX_STRING];
    char curso[MAX_STRING];
    float nota;

    this->recordFile->read((char *)&nUSP, sizeof(int));
    this->recordFile->read((char *)nome, sizeof(char) * MAX_STRING);
    this->recordFile->read((char *)sobrenome, sizeof(char) * MAX_STRING);
    this->recordFile->read((char *)curso, sizeof(char) * MAX_STRING);
    this->recordFile->read((char *)&nota, sizeof(float));

    student* toReturn = new student(nUSP, (string)nome, (string)sobrenome, (string)curso, nota);
    return toReturn;
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

    boolBuffer = false;
    for (int i = 0; i < FREE_SPACE_ON_PAGE; i++)
    {
        this->treeFile->write((char *)&boolBuffer, sizeof(bool));
    }
    
}

long BTREE::writePage(Page* toWrite)
{
    this->treeFile->seekp( 0, ios::end);
    int newPageRRN = (this->treeFile->tellp() / PAGESIZE) - 1;

    this->writePage(toWrite, newPageRRN);

    return newPageRRN;
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

    //Reading keysArray
    this->treeFile->seekg( ( ((pageRRN+1) * PAGESIZE)), ios::beg);
    for(int i = 0; i < keysAmnt; i++)
    {   
        nodeToLoad = new Node();
        this->treeFile->read((char *)&keyBuffer, sizeof(int));
        nodeToLoad->setKey(keyBuffer);
        pageToLoad->records[i] = nodeToLoad;
    }
    
    //Reading RRN array
    this->treeFile->seekg( ( ((pageRRN+1) * PAGESIZE) + RECORD_RRN_PLACE), ios::beg);
    for(int i = 0; i < keysAmnt; i++)
    {   
        nodeToLoad = pageToLoad->records[i];
        this->treeFile->read((char *)&RRNBuffer, sizeof(long));
        nodeToLoad->setRRN(RRNBuffer);
    }

    //Reading childrenArray
    this->treeFile->seekg( ( ((pageRRN+1) * PAGESIZE) + CHILDREN_RRN_PLACE), ios::beg);
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

/*===============================ERR_PATH===============================*/

ERR_PATH::ERR_PATH()
{
    this->top = -1;
}

void ERR_PATH::push(long RRN)
{
    this->top++;
    this->searchPath[this->top] = RRN;
}

long ERR_PATH::get()
{
    return this->searchPath[this->top];
}

long ERR_PATH::pop()
{
    long returnRNN = this->searchPath[this->top];
    this->top--;
    return returnRNN;
}