#include <iostream>
#include "dnode.h"
#include "file.h"
#include "bag.h"
#include "word.h"
using namespace std;

int main() {
    Bag b;
    Word w("hello", "notes.txt");
    listInsert(b.getWordList(), w);
    b.printWords();
    //listPrint(b.getWordList());

    /*
    cout << w.numFiles() << endl;
    b.insertWord(w);
    b.printWords();
    */
    return 0;
}