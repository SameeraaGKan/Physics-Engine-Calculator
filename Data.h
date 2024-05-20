/*
    Name:Sameeraa Kandalgaonkar 
    NetID: SXK220350

    This is the header file for the Data class.
    It contains the outline for the Data class and also some inlined functions
*/
#ifndef DATA_H
#define DATA_H

#include <iostream>
#include <string>

class Data
{
    private:
            //private members
            //variables to store the operand and operator
            double operand;
            char operatorr;
    public:
            //public members

            //inline functions
            //default constructor
            Data() 
                {operand = 0; operatorr = ' ';}

            //overloaded constructor - with the operator as a parameter
            Data(char optor)
                {operatorr = optor;}

            //overloaded constructor - with the operand and operator as parameters
            Data(double opand, char optor)
                {operand = opand; operatorr = optor;}

            //Getters, Accessors
            double getOperand() {return operand;}
            char getOperator() {return operatorr;}

            //Setters, Mutators
            void setOperand(double opand){operand = opand;}
            void setOperator(char optor){operatorr = optor;}
};

#endif 