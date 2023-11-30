#include <iostream>
#include <string>

//Handles processing of expression to other functions then returns answer
double solver(std::string expression){
    double result{};
    //Pass to Error handler function then to expression parser to solve
    if (errorHandler(expression)){

    }
    
    return result;
}

//Checks for basic errors returns true if error free
bool errorHandler(std::string expression){
    //Check for unmatched & mismatched parentheses/operands
    //Missing operator 5(2+3) missing the *
    //Invalid Characters

}

//PEMDAS Handler Passes to termSolver
//Parses 5-2*(6-3) and passes 6-3 to term solver resulting in 5-2*3 
    //then 2*3 then passes 5-6, Returns final answer of -1 to solver
double expressionParser(std::string expression){

}

//Binary operator solver ex: input 5*5 returns 25
double termSolver(std::string operation){
    //If division check for divide by 0 error first
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
