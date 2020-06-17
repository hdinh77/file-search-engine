//word.h
//Heather Dinh, 3/13/20

#ifndef WORD_H
#define WORD_H
#include "file.h"
#include "dnode.h"
#include <string>
using namespace std;

class Word {
    public:
        Word();
        Word(const Word &source);
        Word(string wordName);
        Word(string wordName, string fileName);
        ~Word();
        Word& operator=(const Word& source);

        string getName() const;
        void setName(string wordName);
        void addFile(string fileName);
        bool containsFile(string fileName);
        dnode<File>* getListPtr() const;
        dnode<File>* getFile(string fileName) const;
    private:
        dnode<File>* files;
        string name;
};



#endif