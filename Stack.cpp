/*
    Name: Sameeraa Kandalgaonkar
    NetID: sxk220350
    This is the cpp file for the Stack class, it contains the 
    implementation of the Stack class functions like the copy constructor, 
    recursive destructor, overloaded operators.
*/

//include the header file
#include "Stack.h"
#include <iostream>

//Copy constructor
Stack::Stack(const Stack& s) 
{
    //Check if the header of the stack is pointing to a null pointer
    //if not then then set the head to point at nullptr
    if (s.head == nullptr) 
    {
        head = nullptr;
        return;
    }
    //Create a new node and set it to point at the head of the stack
    head = new Node(s.head->getPayload());
    Node* curr = head;
    Node* temp = s.head->getNext();

    //while the temporry node is not pointing to null pointer, assign
    // the next node to the current node and then move the current node
    while (temp != nullptr) 
    {
        curr->setNext(new Node(temp->getPayload()));
        curr = curr->getNext();
        temp = temp->getNext();
    }
}

//Recursive delete function, it checks if the current pointer 
//is pointing to a null pointer, if not then it calls the function
//itself recursively until the current pointer is pointing to a null pointer
void Stack::deleteList(Node* curr) 

{
    if (curr == nullptr)
    {
        return;
    }
    Node* next = curr->getNext();
    delete curr;
    deleteList(next);
}

//Destructor, it calls the recursive delete function 
Stack::~Stack() 
{
    deleteList(head);
}




//  Overloaded << operator for output, it prints the contents of the stack
//  The stack will contain all operators or all operands
//  The stack will be printed in with a space and comma separated.
//  Parameter ostream object passed by reference, stack object passed in by reference
std::ostream &operator<<(std::ostream& out, const Stack& stack)
{
    Node* curr = stack.head;
    bool isOperator = false;
    //first check if the stack is empty
    while(curr != nullptr)
    {
        if (curr->getPayload().getOperator() != ' ')
        {
            //if the current node is an operator
            if (isOperator)
            {
                out << ", ";
            }
            out << curr->getPayload().getOperator();
            isOperator = true;
        }
        else
        {
            //if the current node is an operand
            if (!isOperator)
            {
                // print a comma and space if the previous node was an operator
                out << ", " << curr->getPayload().getOperand();
            }
            isOperator = false;
        }
        //move to the next node
        curr = curr->getNext();
    }
    return out;
}

// ▪ Overloaded >> operator this operator is not used for input
//   It used as pop
//   Parameter: Node pointer parameter
//   Return: dereferenced Node pointer
//   Disconnect head node from list and store in parameter
Stack& Stack::operator>>(Node *&node)
{
    //if the stack is not empty
    if(head != nullptr)
    {
        node = head;
        head = head->getNext();
        node->setNext(nullptr);
    }
    return *this;
}

// ▪ Overloaded << operator it is not used for output
// • Used as push
// • Parameter: Node pointer 
// • Return: dereferenced Node pointer
// • Adds the node to the head of the linked list
Stack& Stack::operator<<(Node *node)
{
    //Check if the stack is empty, if it is not then insert 
    //the node to the beginning of the list
    if(node != nullptr)
    {
        node->setNext(head);
        head = node;
    }
    return *this;
}

//Function to check if the Stack is empty so tha further action can be performed
bool Stack:: isEmpty() const 
{
    return head == nullptr;
}
