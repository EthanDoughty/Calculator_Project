#include <iostream>
#include <string> //string functions
#include <cmath> //math function
#include <stack> //stack data structure
#include <sstream> //string stream
#include <cstdlib> //exit function
#include <algorithm>

bool isOperator(char);
bool isNum(char);
double solver(std::string);
bool errorHandler(std::string);
double parenthesesParser(std::string&, size_t&);
double expressionParser(std::string&);
double termSolver(double, double, char);
using std::istringstream;


//Check to make sure it is looking at operators, used in errorHandler to check for good input
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '^';
}

//Check to make sure it is checking numbers, used in errorHandler to check for good input
bool isNum(char c) {
    return (c >= '0' && c <= '9') || c == '.';
}

//Handles processing of expression to other functions then returns answer
double solver(std::string expression){ 
    double result{};
    //Pass to Error handler function then to expression parser to solve
    if (errorHandler(expression)){
        size_t index = 0;
        if (expression.find("(") != std::string::npos){
            result = parenthesesParser(expression, index);
        }
        else{
            result = expressionParser(expression);
        }
    }
    return result;
}

//Checks for basic errors returns true if error free
bool errorHandler(std::string expression){
    int openParens = 0, closedParens = 0, parensCount = 0;
    for (int i = 0; i < expression.size(); i++){
        if(expression[i] == '('){openParens += 1; parensCount += 1;}
        if(expression[i] == ')'){closedParens += 1; parensCount -= 1;}
        if(parensCount < 0){std::cerr << "Parentheses Error\n"; exit(6);}
    }
    if (closedParens != openParens){std::cerr << "Unmatched Parentheses\n"; exit(5);}
    //Checks for invalid characters
    for (int i = 0; i < expression.size(); i++){
        if (isNum(expression[i]) || isOperator(expression[i]) ){
            continue; 
        }
        else{
            return false;
        }
    }
    return true;
}

//PEMDAS Handler Passes to emdas that passes to termsolver
double parenthesesParser(std::string& expression, size_t& index){
    size_t startPos = index;
    size_t stopPos = index;
    int openParenCount = 0;
    while (stopPos < expression.size()){
        if (expression[stopPos] == '('){
            openParenCount++;
        }
        else if(expression[stopPos] == ')'){
            openParenCount--;
            if (openParenCount == 0){
                break;
            }
        }
        stopPos++;
    }
    std::string subexpression = expression.substr(startPos + 1, stopPos - startPos - 1);
    double subexpressionResult = expressionParser(subexpression);
    expression.replace(startPos, stopPos-startPos+1, std::to_string(subexpressionResult));
    return 0; 
} 

// handles individual expressions
double termSolver(double operand1, double operand2, char op){
    switch (op) {
        case '+':
            return operand1 + operand2;
        case '-':
            return operand1 - operand2;
        case '*':
            return operand1 * operand2;
        case '^':
            return pow(operand1, operand2);
        case '/':
            if (operand2 != 0.0) {
                return operand1 / operand2;
            } else {
                // Handle error: Division by zero
                std::cerr << "Error: Division by zero\n";
                return 0.0;
            }
        case '%':
            if (operand2 != 0.0) {
                return std::fmod(operand1, operand2);
            } else {
                // Handle error: Modulo by zero
                std::cerr << "Error: Modulo by zero\n";
                return 0.0;
            }
        default:
            // Handle error: Invalid operator
            std::cerr << "Error: Invalid operator '" << op << "'\n";
            return 0.0;
    }
}

// Breaks up the string into individual expressions which get passed to term2
double expressionParser (std::string &s){
    if(s.find('+') != std::string::npos){
        int endpos = 0, count = s.size();
        while(count >= 0) {
            if(s[count] == '+'){
                endpos = count;
                break;
            }
            count--;
        }
        std::string temp1 = s.substr(0,endpos);
        std::string temp2 = s.substr(endpos+1, s.size()-1);
        double temp3 = expressionParser(temp1);
        double temp4 = expressionParser(temp2);
        return termSolver(temp3, temp4, s[endpos]);
    }
    else if(s.find('-') != std::string::npos){
        int endpos = 0, count = s.size();
        while(count >= 0) {
            if(s[count] == '-'){
                endpos = count;
                break;
            }
            count--;
        }
        std::string temp1 = s.substr(0,endpos);
        std::string temp2 = s.substr(endpos+1, s.size()-1);
        double temp3 = expressionParser(temp1);
        double temp4 = expressionParser(temp2);
        return termSolver(temp3, temp4, s[endpos]);
    }
    else if(s.find('*') != std::string::npos || s.find('/') != std::string::npos){
        int endpos = 0, count =s.size();
        while(count >= 0) {
            if(s[count] == '*' || s[count] == '/'){
                endpos = count;
                break;
            }
            count--;
        }
        std::string temp1 = s.substr(0,endpos);
        std::string temp2 = s.substr(endpos+1, s.size()-1);
        double temp3 = expressionParser(temp1);
        double temp4 = expressionParser(temp2);
        return termSolver(temp3, temp4, s[endpos]);
    }
    else if(s.find('^') != std::string::npos){
        int endpos = 0, count = s.size();
        while(count >= 0) {
            if(s[count] == '^'){
                endpos = count;
                break;
            }
            count--;
        }
        std::string temp1 = s.substr(0,endpos);
        std::string temp2 = s.substr(endpos+1, s.size()-1);
        double temp3 = expressionParser(temp1);
        double temp4 = expressionParser(temp2);
        return termSolver(temp3, temp4, s[endpos]);
    }
    else{
        return stod(s);
    }
}

//Gets expression passes to solver prints returned result
int main(int argc, char* argv[]){
    std::string expression;

    if (argc == 2){
        expression = argv[1];
    }
    else if (argc > 2){
        std::cerr << "Only 1 expression allowed" << std::endl;
        exit(1);
    }
    else{
        std::cout << "Enter an expression: ";
        std::getline(std::cin, expression);
    }
    //Test this
    //expression.erase(std::remove_if(expression.begin(), expression.end(), ::isspace), expression.end());
    std::cout << "Expression: " << expression << std::endl;
    double result = solver(expression);
    std::cout << "Answer: " << result << std::endl;
    return 0;
}
