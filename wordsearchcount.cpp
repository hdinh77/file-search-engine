#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <string>

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
  string dir; //
  vector<string> files = vector<string>();

  Bag cont; // BAG OBJECT
  

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
      cont.insert_word(word, files[i]);
    } 
    fin.close(); 
  }

  //cout << "This is the next part of the program that you will exercise in the next project." << endl;
  //cont.print_words();

  cout<<"Enter word: ";
  std::string word;
  getline(cin, word, '\n'); // input word

  cout<<"Enter threshold: ";
  std::string thresh;
  getline(cin, thresh, '\n'); // input threshold

  int t = std::stoi(thresh); // convert to integer

  // at this point, the input word is stored in the
  // variable "word" and input threshold is stored in
  // variable "t"

  // ADD CODE HERE TO INVOKE MEMBER FUNCTIONS OF
  // BAG OBJECT CREATED AT LINE 46 FOR PRINTING
  // FILENAMES THAT CONTAINS THE GIVEN WORD
  // ATLEAST THE GIVEN AMOUNT OF TIMES

  dnode<Word>* wordPtr = cont.getListPtr();

  while(wordPtr) {
    if(wordPtr->getData().getName() == word) {
      break;
    }
    wordPtr = wordPtr->getNext();
  }

  if(wordPtr) {
    dnode<File>* filesList = wordPtr->getData().getListPtr();
    while(filesList) {
      File curFile = filesList->getData();
      if(curFile.getFileCount() >= t) {
        cout << curFile.getName() << endl;
      } 
      filesList = filesList->getNext();
    }
  }

  // YOU MAY ADD CODE HERE IF NEEDED TO
  // CLEAR ANY DYNAMICALLY ALLOCATED SPACES
  return 0;
}




