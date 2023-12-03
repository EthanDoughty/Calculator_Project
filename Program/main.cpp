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
int getCounterFromHistoryFile();
void deleteHistoryFile();
using std::istringstream;


//Check to make sure it is looking at operators, used in errorHandler to check for good input
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '^' || c == '(' || c== ')';
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
    int openParens = 0, closedParens = 0, parensCount = 0;
    for (int i = 0; i < expression.size(); i++){
        if(expression[i] == '('){openParens += 1; parensCount += 1;}
        if(expression[i] == ')'){closedParens += 1; parensCount -= 1;}
        if(parensCount < 0){std::cerr << "Parentheses Error\n"; exit(6);}
    }
    if (closedParens != openParens){std::cerr << "Unmatched Parentheses\n"; exit(5);}
    //Checks for invalid characters
    for (int i = 0; i < expression.size(); i++){
        if (isNum(expression[i]) || isOperator(expression[i])){
            continue; 
        }
        else{
            return false;
        }
    }
    return true;
}

//PEMDAS Handler Passes to emdas that passes to termsolver
double parenthesesParser(std::string& expression){
    /*size_t startPos = 0;
    size_t stopPos = 0;
    int openParenCount = 0;
    while (stopPos < expression.size()){
        if (expression[stopPos] == '('){
            if (openParenCount ==0){
                startPos=stopPos;
            }
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
    
    if (expression.find("(") != std::string::npos){
        parenthesesParser(expression);
    }
    else{
        double result = 0;
        for (int i = 0; i < expression.size(); i++){
        if (isOperator(expression[i])){
            result = expressionParser(expression);
            break; 
        }
        else{
            result = stod(expression);
        }
        }
        return result;
    }*/
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
    /*if (s.find("(") != std::string::npos){
        s = std::to_string(parenthesesParser(s));
    }*/
    //std::cout << s << std::endl;
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
        int endpos = 0, count = 0;
        while(count < s.size()) {
            if(s[count] == '-'){
                endpos = count;
                break;
            }
            count++;
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

void printHistory() {
    std::ifstream file("history.txt");
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::cout << line << '\n';
        }
        file.close();
    } else {
        std::cerr << "Unable to open history file.\n";
    }
}

void saveToHistory(std::string expression, double result, int& counter) {
    std::ofstream file("history.txt", std::ios::app);
    file << counter << ") " << expression << " = " << result << "\n";
    file.close();
    counter++;
}

int getCounterFromHistoryFile() {
    int counter = 0;
    std::ifstream file("history.txt");
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            // Increment counter for each line
            counter++;
        }
        file.close();

        // Increment counter by one if there are lines
        if (counter > 0) {
            counter++;
        }
    } else {
        // If the file cannot be opened, assign counter to 1
        counter = 1;
    }

    return counter;
}

void deleteHistoryFile() {
    if (std::remove("history.txt") == 0) {
        std::cout << "History file deleted successfully.\n";
    } else {
        std::cerr << "Error deleting history file.\n";
    }
}

//Gets expression passes to solver prints returned result
int main(int argc, char* argv[]){
    std::string expression;
    if (argc == 2){
        expression = argv[1];
        //Remove's Whitespace
        expression.erase(std::remove_if(expression.begin(), expression.end(), ::isspace), expression.end());
        double result = solver(expression);
        std::cout << "Answer: " << result << std::endl;
    }
    else if (argc > 2){
        std::cerr << "Only 1 expression allowed" << std::endl;
        exit(1);
    }
    else{
        int counter = getCounterFromHistoryFile();
        char selection;
        while (selection != 'c'){
            std::cout << "Select an option:\na) Enter an expression to solve\nb) View History\nc) Exit\n";
            std::cin >> selection;
            std::cin.ignore();
            if (selection == 'a'){
                std::cout << "Enter an expression: ";
                std::getline(std::cin, expression);
                expression.erase(std::remove_if(expression.begin(), expression.end(), ::isspace), expression.end());
                double result = solver(expression);
                saveToHistory(expression, result, counter);
                std::cout << "Answer: " << result << std::endl;
            }
            if (selection == 'b'){
                printHistory();
            }
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
        }
    }
    return 0;
}
