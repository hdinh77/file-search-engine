//file.cpp
//Heather Dinh, 3/13/20

#include <string>
#include "file.h"
using namespace std;

File::File() {
    filename = "";
    count = 1;
}

File::File(string name) {
    filename = name;
    count = 1;
}

string File::getName() const{
    return filename;
}

int File::getFileCount() const{
    return count;
}

void File::addFileCount() {
    count++;
}
