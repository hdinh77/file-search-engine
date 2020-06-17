//Heather Dinh, 3/11/20
//wordsearchunion.cpp

#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include<string>

// ADD ANY HEADER FILES YOU NEED
#include "dnode.h"
#include "bag.h"
#include "word.h"
#include "file.h"

using namespace std;

void to_lower(std::string& s) {
   for (std::string::iterator p = s.begin();
        p != s.end(); ++p) {
      *p = tolower(*p);
   }
}


// Given a directory, return all the files in that directory
// if the directory does not exist -- report error.
int getdir (string dir, vector<string> &files)
{
  DIR *dp;
  struct dirent *dirp;
  if((dp  = opendir(dir.c_str())) == NULL) {
    cout << "Error(" << errno << ") opening " << dir << endl;
    return errno;
  }

  while ((dirp = readdir(dp)) != NULL) {
    files.push_back(string(dirp->d_name));
  }
  closedir(dp);
  return 0;
}

int main(int argc, char* argv[])
{
  string dir; 
  vector<string> files = vector<string>();

  Bag cont;
  

  // This part of the program checks if a directory containing the files has been
  // specified. If There is no directory specified, the program terminates.
  // Otherwise, it opens the sub-directory containg the data files using the function
  // getdir().
  if (argc < 2)
    {
      cout << "No Directory specified; Exiting ..." << endl;
      return(-1);
    }
  dir = string(argv[1]);
  if (getdir(dir,files)!=0)
    {
      cout << "Error opening " << dir << "; Exiting ..." << endl;
      return(-2);
    }
  
  // This part of the program opens every data file one by one and prints out the
  // words contained in it.

  string slash("/");
  for (unsigned int i = 0; i < files.size(); i++) {
    if(files[i][0]=='.') continue; //skip hidden files
    cout << "OPEN " << files[i] << endl;
    ifstream fin((string(argv[1])+slash+files[i]).c_str()); //open using absolute path
    // ...read the file..
    string word;
    while(true){
      fin>>word;
      if(fin.eof()) {cout << "EOF " << files[i] << endl; break;}
      // Insert a single C++ statement below to print "<filename>::<word>".
      // cout << files[i] << "::" << word << endl;
      to_lower(word);
      cont.insert_word(word,files[i]);
    }
    fin.close();
  }

  //cout << "This is the next part of the program that you will exercise in the next project." << endl;
  //cont.print_words();

  cout<<"Enter word1: ";
  std::string word1;
  getline(cin, word1, '\n');

  cout<<"Enter word2: ";
  std::string word2;
  getline(cin, word2, '\n');

  // at this point, the input words are stored in the
  // variables "word1" and "word2"

  // ADD CODE HERE TO INVOKE MEMBER FUNCTIONS OF
  // BAG OBJECT CREATED AT LINE 46 FOR PRINTING
  // FILENAMES THAT CONTAINS EITHER OR BOTH OF
  // THE GIVEN WORDS

  dnode<Word>* wordPtr1 = cont.getListPtr();
  while(wordPtr1) {
    if(wordPtr1->getData().getName() == word1) {
      break;
    }
    wordPtr1 = wordPtr1->getNext();
  }

  dnode<Word>* wordPtr2 = cont.getListPtr();
  while(wordPtr2) {
    if(wordPtr2->getData().getName() == word2) {
      break;
    }
    wordPtr2 = wordPtr2->getNext();
  }

  //this will be a new list of the union files if both words exist
  dnode<File>* unionFiles = NULL;

  if(!wordPtr1 && wordPtr2){
    //print out the files of the second word
    cout << "we got here" << endl;
    listPrint(wordPtr2->getData().getListPtr());
  }else if(!wordPtr2 && wordPtr1) {
    //print out the files of the first word
    listPrint(wordPtr1->getData().getListPtr());
  }else if(wordPtr1 && wordPtr2){
    //prints out the union of the two words
    dnode<File>* filesList1 = wordPtr1->getData().getListPtr();
    unionFiles = new dnode<File>(NULL, NULL, filesList1->getData());
    filesList1 = filesList1->getNext();
    
    //enter all files of the first words
    while(filesList1) {
      dnode<File>* f = new dnode<File>(NULL, NULL, filesList1->getData());
      listInsert(unionFiles, f);      
      filesList1 = filesList1->getNext();
    }

    dnode<File>* filesList2 = wordPtr2->getData().getListPtr();
    while(filesList2) {
      //first need to check if this file is already in the unionList
      dnode<File>* tmp = unionFiles;
      bool inUnionFiles = false;
      while(tmp) {
        if(filesList2->getData().getName() == tmp->getData().getName()) {
          inUnionFiles = true;
          break;
        }
        tmp = tmp->getNext();
      }

      if(!inUnionFiles){
        dnode<File>* f = new dnode<File>(NULL, NULL, filesList2->getData());
        listInsert(unionFiles, f);
      }
      
      filesList2 = filesList2->getNext();
    }

    listPrint(unionFiles);

  }

  // YOU MAY ADD CODE HERE IF NEEDED TO
  // CLEAR ANY DYNAMICALLY ALLOCATED SPACES
  while(unionFiles) {
    dnode<File>* tmp = unionFiles;
    unionFiles = unionFiles->getNext();
    delete tmp;
  }
  unionFiles = NULL;
    
  return 0;
}




