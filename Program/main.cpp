#include "calculators.h"
using std::istringstream;


// 9
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
double expressionParser(std::string& expression, size_t& index){
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
    double subexpressionResult = termSolver(subexpression);
    expression.replace(startPos, stopPos-startPos+1, std::to_string(subexpressionResult));
    return 0; 
} 


// -2+5*4
double emdas(std::string& expression){
    if (expression.find("(") != std::string::npos){
        size_t index = 0;
        expressionParser(expression, index);
    }
    
    for (int i = 0; i < expression.size(); i++){
        if (expression[i] == '^'){

        }
    }
    for (int i = 0; i < expression.size(); i++){
        if (expression[i] == '*' || expression[i] == '/'){
            // something happens here
            
        }
    }
    return 0;
}

//Binary operator solver ex: input 5*5 returns 25
double termSolver(std::string& operation) {
    istringstream iss(operation);
    double operand1, operand2;
    char op;

    iss >> operand1 >> op >> operand2;

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
                // Handle error: Division by zero (Doesn't end program)
                std::cerr << "Error: Division by zero\n";
                exit(2);
            }
        case '^':
            return pow(operand1, operand2);
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
            exit(4);
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
    expression.erase(std::remove_if(expression.begin(), expression.end(), ::isspace), expression.end());
    std::cout << "Expression: " << expression << std::endl;
    double result = solver(expression);
    std::cout << "Answer: " << result << std::endl;
    return 0;
}
