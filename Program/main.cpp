#include "calculators.h"

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '^';
}

//Check to make sure it is checking numbers and not equivalent char values
bool isNum(char c) {
    return (c >= '0' && c <= '9') || c == '.';
}

//Handles processing of expression to other functions then returns answer
double solver(std::string expression){ 
    double result{};
    //Pass to Error handler function then to expression parser to solve
    if (errorHandler(expression)){
        size_t index = 0;
        result = expressionParser(expression, index);
    }
    return result;
}

//Checks for basic errors returns true if error free
bool errorHandler(std::string expression){
    
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

//PEMDAS Handler Passes to termSolver
//Parses 5-2*(6-3) and passes 6-3 to term solver resulting in 5-2*3 
    //then 2*3 then passes 5-6, Returns final answer of -1 to solver
double expressionParser(std::string& expression, size_t& index){
    //std::cout << expression.length() << std::endl;
    expression.find("(") != std::string::npos;
    // return something here
    return 0; 
}

//Binary operator solver ex: input 5*5 returns 25
double termSolver(std::string& operation) {
    std::istringstream std::iss(operation);
    double operand1, operand2;
    char op;

    std::iss >> operand1 >> op >> operand2;

    switch (op) {
        case '+':
            return operand1 + operand2;
        case '-':
            return operand1 - operand2;
        case '*':
            return operand1 * operand2;
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


//Gets expression passes to solver prints returned result
int main(){
    std::cout << "Enter an expression: ";
    std::string expression;
    std::getline(std::cin, expression);
    double result = solver(expression);
    std::cout << "Answer: " << result << std::endl;
    return 0;
}
