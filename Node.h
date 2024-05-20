/*
    Name:Sameeraa Kandalgaonkar 
    NetID: SXK220350

    This is the header file for the Node class. 
    It contains the outline for the Node class and also some inlined functions
*/
#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>
#include "Data.h"

class Node 
{
    private:
            //private data members 
            Data payLoad;

    public:
            //public data members

            //next pointer 
            Node *next;

            //default constructor
            Node() 
                {next = nullptr;}

            //overloaded constructor
            Node(const Data &d)
                {payLoad = d; next = nullptr;}

            //Getters, Accessors
            Data getPayload() {return payLoad;}
            Node *getNext() {return next;}    

            //Setters, Mutators
            void setPayload(Data pay){payLoad = pay;}    
            void setNext(Node *n){next = n;}
};

#endif 
