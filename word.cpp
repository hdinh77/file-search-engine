//word.cpp
//Heather Dinh, 3/13/20

#include "word.h"
#include <string>
#include <iostream>
using namespace std;

Word::Word() {
    name = "";
    files = NULL;
} 

Word::Word(const Word &source) {
    name = source.getName(); 
    dnode<File>* cur = source.getListPtr();
    while(cur) {
        File fileName(cur->getData().getName()); 
        dnode<File>* f = new dnode<File>(NULL, NULL, fileName);
        listInsert(files, f); 
        cur = cur->getNext();
    }
}

Word::~Word() {
    dnode<File>* f = files;
    while(f) {
        dnode<File>* tmp = f;
        f = f->getNext();
        delete tmp;
    }
    files = NULL;
}

Word& Word::operator=(const Word& source) {
    //cout << "executing word assignment operator..." << endl;
    if(this == &source) {
        return *this;
    }
    
    dnode<File>* f = files;
    while(f) {
        dnode<File>* tmp = f;
        f = f->getNext();
        delete tmp;
    }

    files = NULL;
    name = source.getName();

    dnode<File>* cur = source.getListPtr();
    while(cur) {
        File fileName(cur->getData().getName()); 
        dnode<File>* f = new dnode<File>(NULL, NULL, fileName);
        listInsert(files, f); 
        cur = cur->getNext();
    }
    return *this;
}

Word::Word(string wordName) {
    name = wordName;
    files = NULL;
}

Word::Word(string wordName, string fileName) {
    name = wordName;
    File f(fileName);
    files = new dnode<File>(NULL, NULL, f);
}

string Word::getName() const {
    return name;
}

dnode<File>* Word::getListPtr() const{
    return files;
}

void Word::setName(string wordName) {
    name = wordName;
}

void Word::addFile(string fileName) {
    if(!containsFile(fileName)) {
        File curFile(fileName); 
        dnode<File>* f = new dnode<File>(NULL, NULL, curFile);
        listInsert(files, f);
    }else {
        dnode<File>* curPtr = getFile(fileName);
        curPtr->getData().addFileCount();
    }
}

bool Word::containsFile(string fileName) {
    dnode<File>* f = files;
    while(f) {
        if(f->getData().getName() == fileName) {
            return true;
        }
        f = f->getNext();
    }
    return false;
}

dnode<File>* Word::getFile(string fileName) const{
    dnode<File>* iterator = getListPtr();
    while(iterator) {
        if(iterator->getData().getName() == fileName) {
            return iterator;
        }
        iterator = iterator->getNext();
    }
    return NULL;
}