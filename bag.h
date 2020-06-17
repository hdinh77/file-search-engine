//bag.h
//Heather Dinh, 3/13/20

#ifndef BAG_H
#define BAG_H
#include "word.h"
#include "dnode.h"
#include <string>
using namespace std;

class Bag {
    public:
        Bag();
        Bag(const Bag& source);
        ~Bag();
        Bag& operator=(const Bag& source);
        void insert_word(string wordName, string fileName);
        dnode<Word>* getListPtr() const;
        dnode<Word>* getWord(string wordName) const;
        bool containsWord(string wordName) const;
    private:
        dnode<Word>* words;
};

#endif