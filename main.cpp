/*
    Name:Sameeraa Kandalgaonkar 
    NetID: SXK220350

    This the main file, it contains the main function. It contains functions
    like the functions to convert infix to postfix, evaluate postfix, perform 
    operations on operands and decide the order of operations.
*/

//Include libraries so that functions can be used
#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <sstream>


//include the header files so that objects of those classes can be made
#include "Data.h"
#include "Node.h"
#include "Stack.h"
using namespace std;

//Function protoytpes
int precedence(char operatorr);
string convertToPostfix(const string& expression, Stack& postFixStack);
double evaluatePostfix(const std::string& postfixExp, Stack& operandStack);
double operate(double operand1, double operand2, char optor);


int main() 
{
    //variables to store the name of the file and expression
    string fileName, exp;
    //create ifstream object to read from the file
    ifstream input;
    
    // Prompt the user to enter input filename
    cout << "Enter input filename: "; 
    cin >> fileName;
    input.open(fileName);

    // If the file is opened
    if (input.is_open())
    {
        // While there is a line to read from the file:
        while(getline(input, exp))
        {
             //cout << exp << endl;
            // Read the expression from the file
            Stack postFix;
            string postStr = convertToPostfix(exp, postFix);
            //cout << postStr <<endl;

            // Evaluate the postfix expression
            Stack operandStack;
            double result = evaluatePostfix(postStr, operandStack);

            // Output the result
            cout << postStr << "\t" << fixed << setprecision(3) << result << endl; 

        }

        //Close the file
        input.close();

    }
    else
    {
        //print out an error if the file is not being opened
        cout << "Error opening file " << fileName << endl;
    }

    return 0;
}

//This function is used to get the precedence of the operators
//it returns the precedence of the operator
int precedence(char operatorr)
{
    if (operatorr == '+' || operatorr == '-')
    {
        return 1;
    }
    else if(operatorr == '*' || operatorr == '/')
    {
        return 2;
    }
    else if(operatorr == '^')
    {
        return 3;
    }
    return 0;
}

//this Functions is used to conver the infix expressions to postfix.
//The function parses the expression and groups numbers togethers so that
//they are intact and not separated from each other. it also checks the precedence of the 
//operators.
//Parameter: string which contain the infix expression and stack object passed in by reference
//Return: string which contains the postfix expression
string convertToPostfix(const string& exp, Stack& postFixStack) 
{
    string postfixExp;
    //Use a for loop to iterate through the expression, group the numbers together
    for (unsigned long int i = 0; i < exp.length(); i++)
    {
        //store the first character in a char variable
        char token = exp[i];
        //Check if the current character is a digit
        if (isdigit(token))
        {
            //if the current character is a digit, 
            //then add it to a string which contains the operands, 
            //when the next character is not a digit,
            //then add the operand to the postfix expression
            string operand;
            //check if counter is smaller than the length of the expression 
            if(i < exp.length())
            {   
                //while the present character is a digit or a decimal, 
                //add it to the operand string
                while ((isdigit(exp[i])|| exp[i] == '.'))
                {
                    operand += exp[i];
                    //increment the counter, to keep checking until an operator is encountered
                    i++;
                }
                //decrement the counter to keep checking the next character
                i--;
                //add the operand to the postfix expression, separated by a space
                postfixExp += operand + " ";
            }
        } 
        else if (token == '(') 
        {
            // Opening parenthesis, push to stack
            postFixStack << (new Node(Data{0, token}));
        } 
        else if (token == ')')
        {
            // While the postFix stack is not empty and the top element is not an opening parenthesis
            while (!postFixStack.isEmpty() &&
                postFixStack.getHead()->getPayload().getOperator() != '(')
            {
                postfixExp += postFixStack.getHead()->getPayload().getOperator();
                postfixExp += " ";
                //pop the stack using the overloaded >> operator
                Node* temp;
                postFixStack >> temp;
                delete temp;
            }
            if (!postFixStack.isEmpty() && 
                postFixStack.getHead()->getPayload().getOperator() == '(') 
            {
                // Remove the opening parenthesis from the stack
                Node* temp;
                postFixStack >> temp;
                delete temp;
            }
        } 
        else 
        {
            // Operator, pop from stack until lower precedence operator or empty
            while (!postFixStack.isEmpty() && 
                precedence(postFixStack.getHead()->getPayload().getOperator()) 
                >= precedence(token)) 
            {
                postfixExp += postFixStack.getHead()->getPayload().getOperator();
                postfixExp += " ";
                //pop the stack using the overloaded >> operator
                Node* temp;
                postFixStack >> temp;
                delete temp;
            }
            postFixStack << (new Node(Data{0, token}));
        }
    }

    // Pop remaining operators from the stack and append to postfix expression
    while (!postFixStack.isEmpty()) 
    {
        postfixExp += postFixStack.getHead()->getPayload().getOperator();
        postfixExp += " ";
        //pop the stack using the overloaded >> operator
        Node* temp;
        postFixStack >> temp;
        delete temp;
    }

    //return the postFix expression
    return postfixExp;
}

//This functions is used to operate the operands based on operators
//Parameter: double operand1, double operand2, char optor
//Return: double which is the result of the operation
//It used switch statements to decide the operation to be performed
double operate(double operand1, double operand2, char optor) 
{
    switch (optor) 
    {
        case '+':
            return operand1 + operand2;
            break;
        case '-':
            return operand1 - operand2;
            break;
        case '*':
            return operand1 * operand2;
            break;
        case '^':
            return pow(operand1, operand2);
            break;
        case '/':
            if (operand2 != 0)
            {
               return operand1 / operand2;
            }
            break;
        default:
            cout << "Invalid operator" << endl;
    }
    return 0.0;
}

//This function is used to evaluate the postfix expression, it uses stringstream 
//to parse the expression, if the first character is a digit then it is 
//pushed onto the stack, but if the first character is an operator then 
//it is popped from the stack and used to perform the operation, for which 
// the first two operands are popped from the stack and the result is pushed
//Parameters: string with expression, stack object passed in by reference
//Return: double which is the result of the expression


double evaluatePostfix(const std::string &postfixExp, Stack &operandStack)
{
    // using stringstream to split the expression
    std::stringstream ss(postfixExp);
    std::string pFix;

    // while there is a token to read from the string
    while (ss >> pFix)
    {
        // store the first character into a char variable
        char first = pFix[0];

        if (isdigit(first) || (first == '-' && pFix.length() > 1))
        {
            // Operand, convert string to double and push onto operand stack
            double operand = stod(pFix);
            operandStack << (new Node(Data{operand, ' '}));
        }
        else if (first == '+' || first == '-' || first == '*' || first == '/' || first == '^')
        {
            // pop the first 2 operands on the stack and store them in variables
            Node *temp3;
            operandStack >> temp3;
            double operand2 = temp3->getPayload().getOperand();
            delete temp3;

            Node *temp2;
            operandStack >> temp2;
            double operand1 = temp2->getPayload().getOperand();
            delete temp2;

            // store the result of their operation in a double variable
            double result = operate(operand1, operand2, first);
            // push the result onto the stack using the overloaded << operator
            operandStack << (new Node(Data{result, ' '}));
        }
    }
    // pop the result from the stack and return it
    return operandStack.getHead()->getPayload().getOperand();
}


