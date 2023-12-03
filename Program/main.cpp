#include <iostream>
#include <string> //string functions
#include <cmath> //math function
#include <stack> //stack data structure
#include <sstream> //string stream
#include <cstdlib> //exit function
#include <algorithm>
#include <fstream>

bool isOperator(char);
bool isNum(char);
double solver(std::string);
bool errorHandler(std::string);
double parenthesesParser(std::string&);
double expressionParser(std::string&);
double termSolver(double, double, char);
void printHistory();
void saveToHistory(std::string, double, int&);
void deleteHistoryFile();
using std::istringstream;


//Check to make sure it is looking at operators, used in errorHandler to check for good input
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '^';
}

//Check to see if the character is a parentheses
bool isParens(char c) {
    return c == '(' || c== ')';
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
        if (expression.find("(") != std::string::npos){
            result = parenthesesParser(expression);
        }
        else{
            result = expressionParser(expression);
        }
    }

    return result;
}

//Checks for basic errors returns true if error free
bool errorHandler(std::string expression){
    //Check for unmatched & mismatched parentheses
    int openParens = 0, closedParens = 0, parensCount = 0;
    for (int i = 0; i < expression.size(); i++){
        if(expression[i] == '('){openParens += 1; parensCount += 1;}
        if(expression[i] == ')'){closedParens += 1; parensCount -= 1;}
        if(parensCount < 0){std::cerr << "Parentheses Error\n"; exit(6);}
    }
    if (closedParens != openParens){std::cerr << "Unmatched Parentheses\n"; exit(5);}
    //Checks for invalid characters
    for (int i = 0; i < expression.size(); i++){
        if (isNum(expression[i]) || isOperator(expression[i]) || isParens(expression[i])){
            continue; 
        }
        else{
            std::cerr << "Invalid Characters";
            exit(2);
        }
    }
    //Check for mismatched operands
    for (int i = 0; i < expression.size(); i++){
        if(expression[i] == '+' || expression[i] == '-'){
            //check right to make sure there is a num or open parens
            int rightIndex = i+1;
            if (rightIndex == expression.size() || (expression[rightIndex] != '(' && (!isNum(expression[rightIndex])) && (expression[rightIndex] != '+') && (expression[rightIndex] != '-')))
            {
                std::cerr << "Mismatched operands";
                exit(2);
            }
        }
        //Check for multiplication or division allowing certain conditions for left and right indexes
        if(expression[i] == '*' || expression[i] == '/'){
            int rightIndex = i+1;
            int leftIndex = i-1;
            if(leftIndex < 0 || rightIndex == expression.size() || 
                (expression[rightIndex] != '(' && (!isNum(expression[rightIndex])) && (expression[rightIndex] != '+') && (expression[rightIndex] != '-')) ||
                (expression[leftIndex] != ')' && (!isNum(expression[leftIndex])))){
                std::cerr << "Mismatched operands";
                exit(2);
            }
        }
        //Check left of open parentheses to make sure it isn't improper
        if(expression[i] == '('){
            //Check if left has a parens, or operator
            int leftIndex = i-1;
            if (leftIndex < 0 || (expression[leftIndex] != '(' && (!isOperator(expression[leftIndex])))){
                std::cerr << "Mismatched operands";
                exit(2);
            }
        }
    }
    //Return true if error free
    return true;
}

//Split up parentheses to pass onto expressionParser
double parenthesesParser(std::string& expression) {
    // Search if you need to parse anymore or return the last value.
    while (expression.find('(') != std::string::npos) {
        // Initialize openParenPos/ClosedParenPos variables to store their positions
        int openParenPos = 0, closedParenPos = 0;

        // Find the first open parentheses
        openParenPos = expression.find('(');

        // Find the matching closing parentheses
        int parensCount = 1;
        for (int i = openParenPos + 1; i < expression.size(); ++i) {
            if (expression[i] == '(') {
                parensCount++;
            } else if (expression[i] == ')') {
                parensCount--;
                if (parensCount == 0) {
                    closedParenPos = i;
                    break;
                }
            }
        }

        // Extract the substring between open and closed parentheses
        std::string subExpression = expression.substr(openParenPos + 1, closedParenPos - openParenPos - 1);
        double result = parenthesesParser(subExpression);

        // Replace the parentheses expression with the result in the original expression
        expression.replace(openParenPos, closedParenPos - openParenPos + 1, std::to_string(result));

        openParenPos = 0;
        closedParenPos = 0;
    }

    return expressionParser(expression);
}

// Solves individual expressions
double termSolver(double operand1, double operand2, char op){
    //Switch statement solve operand based on operation given
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
                exit(4);
            }
        case '%':
            if (operand2 != 0.0) {
                return std::fmod(operand1, operand2);
            } else {
                // Handle error: Modulo by zero
                std::cerr << "Error: Modulo by zero\n";
                exit(3);
            }
        default:
            // Handle error: Invalid operator
            std::cerr << "Error: Invalid operator '" << op << "'\n";
            exit(2);
    }
}

// Breaks up the string into individual expressions which get passed to termSolver
double expressionParser (std::string &s){
    //Check for addition operator
    if(s.find('+') != std::string::npos){
        int endpos = 0, count = s.size();
        while(count >= 0) {
            if(s[count] == '+'){
                endpos = count;
                break;
            }
            count--;
        }
        //Extract substrings left & right of operator
        std::string temp1 = s.substr(0,endpos);
        std::string temp2 = s.substr(endpos+1, s.size()-1);
        //Recursively Parse Substrings
        double temp3 = expressionParser(temp1);
        double temp4 = expressionParser(temp2);
        //Combine results
        return termSolver(temp3, temp4, s[endpos]);
    }
    //Check for subtraction operator
    else if(s.find('-') != std::string::npos){
        int endpos = 0, count = 0;
        while(count < s.size()) {
            if(s[count] == '-'){
                endpos = count;
                break;
            }
            count++;
        }
        //Extract substrings left & right of operator
        std::string temp1 = s.substr(0,endpos);
        std::string temp2 = s.substr(endpos+1, s.size()-1);
        //Recursively Parse Substrings
        double temp3 = expressionParser(temp1);
        double temp4 = expressionParser(temp2);
        //Combine results
        return termSolver(temp3, temp4, s[endpos]);
    }
    //Check for multiplication or division operator
    else if(s.find('*') != std::string::npos || s.find('/') != std::string::npos){
        int endpos = 0, count =s.size();
        while(count >= 0) {
            if(s[count] == '*' || s[count] == '/'){
                endpos = count;
                break;
            }
            count--;
        }
        //Extract substrings left & right of operator
        std::string temp1 = s.substr(0,endpos);
        std::string temp2 = s.substr(endpos+1, s.size()-1);
        //Recursively Parse Substrings
        double temp3 = expressionParser(temp1);
        double temp4 = expressionParser(temp2);
        //Combine results
        return termSolver(temp3, temp4, s[endpos]);
    }
    //Check for exponent operator
    else if(s.find('^') != std::string::npos){
        int endpos = 0, count = s.size();
        while(count >= 0) {
            if(s[count] == '^'){
                endpos = count;
                break;
            }
            count--;
        }
        //Extract substrings left & right of operator
        std::string temp1 = s.substr(0,endpos);
        std::string temp2 = s.substr(endpos+1, s.size()-1);
        //Recursively Parse Substrings
        double temp3 = expressionParser(temp1);
        double temp4 = expressionParser(temp2);
        //Combine results
        return termSolver(temp3, temp4, s[endpos]);
    }
    //Converts string to double if no operators are found
    else{
        return stod(s);
    }
}

//Prints lines of history file to console
void printHistory() {
    std::ifstream file("history.txt");
    if (!file.is_open()) {
        std::cerr << "Unable to open history file.\n";
        exit(7);
    }

    std::cout << file.rdbuf();
    file.close();
}

//Writes lines to file with in #) expression = result format
void saveToHistory(std::string expression, double result, int& counter) {
    //Open history.txt in append mode
    std::ofstream file("history.txt", std::ios::app);
    //Write expression to file
    file << counter << ") " << expression << " = " << result << "\n";
    file.close();
    counter++;
}

//Asks to delete history file upon exiting program
void deleteHistoryFile() {
    if (std::remove("history.txt") == 0) {
        std::cout << "History file deleted successfully.\n";
    } else {
        std::cerr << "Error deleting history file.\n";
        exit(8);
    }
}

//Looks if arguments provided in launch if so prints result if not asks user for further input
int main(int argc, char* argv[]){
    std::string expression;
    //Checks amount of arguments provided in launch
    if (argc == 2){
        expression = argv[1];
        //Remove's Whitespace
        expression.erase(std::remove_if(expression.begin(), expression.end(), ::isspace), expression.end());
        double result = solver(expression);
        std::cout << "Answer: " << result << std::endl;
    }
    //If more than 2 arguments quits program
    else if (argc > 2){
        std::cerr << "Only 1 expression allowed" << std::endl;
        exit(1);
    }
    //If no arguments provided prompts user for input
    else{
        int counter = 1;
        char selection = 0;
        do {
            std::cout << "Select an option:\na) Enter an expression to solve\nb) View History\nc) Exit\n";
            std::cin >> selection;
            //Gets rid of newline character for proper recongition of expression later
            std::cin.ignore();
            //Prompts user for expression then prints answer
            if (selection == 'a'){
                std::cout << "Enter an expression: ";
                std::getline(std::cin, expression);
                //Removes whitespace
                expression.erase(std::remove_if(expression.begin(), expression.end(), ::isspace), expression.end());
                //Gets answer of equation and saves to history.txt
                double result = solver(expression);
                saveToHistory(expression, result, counter);
                std::cout << "Answer: " << result << std::endl;
            }
            //Prints out history.txt
            if (selection == 'b'){
                printHistory();
            }
            //Prompts for saving/deletion of history.txt and exits program
            if (selection == 'c'){
                char saveOption;
                std::cout << "Do you want to save the history file (s) or delete it (d)? \n";
                std::cin >> saveOption;
                if (saveOption == 'd') {
                    deleteHistoryFile();
                }
                else if (saveOption == 's') {
                    //Pretty much do nothing
                    std::cout << "History file saved successfully\n";
                }
                else {
                    std::cerr << "Invalid option. Exiting without deleting the history file.\n";
                }
                std::cout << "Goodbye!\n";
            }
        } while (selection != 'c');
    }
    return 0;
}
