//file.h
//Heather Dinh, 3/13/20

#ifndef FILE_H
#define FILE_H
#include <string>
using namespace std;

class File{
    public:
        //constructor
        File();
        File(string name);

        string getName() const;
        int getFileCount() const;
        void addFileCount();

    private:
        string filename;
        int count = 0;
};
#endif