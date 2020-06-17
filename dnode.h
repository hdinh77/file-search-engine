//dnode.h
//Heather Dinh, 3/13/20

#ifndef DNODE_H
#define DNODE_H
#include <cstdlib>
#include <iostream>
using namespace std;

//T represents what type thing that dnode will point to
//either a Word or a File
template <class T> 
class dnode
{
private:
    T data_field;
    // forward pointer
    dnode<T>* link_field;
    // backward pointer
    dnode<T>* prev_field;

public:
    //constructor
    dnode(dnode<T>* next = NULL, dnode<T>* prev = NULL, T& data = NULL) 
        {link_field = next; prev_field = prev; data_field = data;}    

    //accessors
    dnode<T>* getNext() {return link_field;}
    dnode<T>* getPrev() {return prev_field;}
    T& getData() {return data_field;}

    //mutators
    void setNext(dnode<T>* n) {link_field = n;}
    void setPrev(dnode<T>* p) {prev_field = p;}
    void setData(T& d) {data_field = d;}
};

//operator overloaders
template<class T>
bool operator ==(dnode<T> first, dnode<T> second) {
    return (first.getData().getName() == second.getData().getName());
}

template<class T>
bool operator <(dnode<T> first, dnode<T> second) {
    return (first.getData().getName() < second.getData().getName());
}

template<class T>
void listInsert(dnode<T>* &head_ptr, dnode<T>* newNode) {
    dnode<T>* p = head_ptr;
    
    if(p == NULL) {
        head_ptr = newNode;
        return;
    }

    while(p) {    
        if(!p->getNext()){
            if(newNode->getData().getName() > p->getData().getName()) {
                //the node value is bigger than the current
                newNode->setPrev(p);
                p->setNext(newNode);
                return;
            }else if(newNode->getData().getName() < p->getData().getName()){
                //the node value is smaller than the current
                newNode->setPrev(p->getPrev());
                newNode->setNext(p);
                
                //case that there is more than one node
                if(p->getPrev()) {
                    (p->getPrev())->setNext(newNode);
                }else {
                    head_ptr = newNode;
                }
                
                p->setPrev(newNode);
                return;
            }   
        }else if(newNode->getData().getName() < p->getData().getName()) {
                //newnode < p
                //case that there is more than one node
                if(p->getPrev()) {
                    (p->getPrev())->setNext(newNode);
                }else {
                    head_ptr = newNode;
                }
                newNode->setPrev(p->getPrev());
                newNode->setNext(p);
                p->setPrev(newNode);
                return;
        }
        p = p->getNext();
    }
    cout << "how did it get here?" << endl;
}

template<class T>
void listPrint(dnode<T>* head) {
    dnode<T>* n = head;
    while(n) {
        cout << n->getData().getName() << endl;
        n = n->getNext();
    }
}

#endif