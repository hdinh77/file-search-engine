//bag.cpp
//Heather Dinh, 3/13/20

#include "bag.h"
#include <string>
using namespace std;

Bag::Bag() {
    words = NULL;
}

Bag::Bag(const Bag& source) {
    dnode<Word>* cur = source.getListPtr();
    while(cur) {
        Word curWord(cur->getData());
        dnode<Word>* w = new dnode<Word>(NULL, NULL, curWord);
        listInsert(words, w);
        cur = cur->getNext();
    }
}

Bag::~Bag() {
    dnode<Word>* w = words;
    while(w) {
        dnode<Word>* tmp = w;
        w = w->getNext();
        delete tmp;
    } 
    words = NULL;
}

Bag& Bag::operator=(const Bag& source) {
    if(this == &source) {
        return *this;
    }
    
    dnode<Word>* w = words;
    while(w) {
        dnode<Word>* tmp = w;
        w = w->getNext();
        delete tmp;
    }

    words = NULL;

    dnode<Word>* cur = source.getListPtr();
    while(cur) {
        Word curWord(cur->getData());
        dnode<Word>* w = new dnode<Word>(NULL, NULL, curWord);
        listInsert(words, w); 
        cur = cur->getNext();
    }

    return *this;
}

dnode<Word>* Bag::getListPtr() const{
    return words;
}

void Bag::insert_word(string wordName, string fileName) {
    Word curWord(wordName, fileName); 
    if(!words) {
        words = new dnode<Word>(NULL, NULL, curWord);
    }else if(!containsWord(wordName)) {
        dnode<Word>* w = new dnode<Word>(NULL, NULL, curWord);
        listInsert(words, w);
    }else {
        dnode<Word>* curPtr = getWord(wordName);
        curPtr->getData().addFile(fileName);
    }
}

dnode<Word>* Bag::getWord(string wordName) const{
    dnode<Word>* iterator = getListPtr();
    while(iterator) {
        if(iterator->getData().getName() == wordName) {
            return iterator;
        }
        iterator = iterator->getNext();
    }
    return NULL;
}

bool Bag::containsWord(string wordName) const{
    dnode<Word>* iterator = getListPtr();
    while(iterator) {
        if(iterator->getData().getName() == wordName) {
            return true;
        }
        iterator = iterator->getNext();
    }
    return false;
}