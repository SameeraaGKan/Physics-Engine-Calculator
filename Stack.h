/*
    Name:Sameeraa Kandalgaonkar 
    NetID: SXK220350

    This is the header file for the Stack class. 
    It contains the outline for the Stack class
*/

#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <string>

#include "Node.h" 

class Stack
{
    // o Attribute names
    private:

        // ▪ Head - node pointer
        Node *head;

    public:
        // o Default constructor
        Stack() {head = nullptr;} 

        // o Overloaded constructor
            // ▪ Node pointer parameter
            // ▪ Head points at new node
        Stack(Node *n) : head(n) {}

        // o Copy constructor
            // ▪ Stack parameter
            // ▪ Create a copy of the stack passed in (enforces data hiding and data integrity)
            // ▪ Assign head to first node
        Stack(const Stack &s);

        // o Destructor
            // ▪ Recursively delete linked list (-5 points if not recursive)
        ~Stack();
        void deleteList(Node* curr);

        // o Accessor and mutator for head
        Node *getHead() {return head;}
        void setHead(Node *h1) {head = h1;}

        // ▪ Overloaded << operator for output
        friend std::ostream &operator<<(std::ostream&, const Stack&);
    
        // ▪ Overloaded >> operator
        Stack& operator>>(Node *&node);       
        
        // ▪ Overloaded << operator
        Stack& operator<<(Node *node);

        //function to check if stack is empty
        bool isEmpty() const;
    };
#endif