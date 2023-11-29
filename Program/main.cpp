#include <iostream>
#include <string>

//Handles processing of expression to other functions then returns answer
double solver(std::string expression){
    double result{};
    //Loop to get rid of parentheses & pass equation to term solver then set variable to return
    
    return result;
}

//PEMDAS Handler
double expressionParser(std::string expression){

}

//Binary operator solver
double termSolver(double termOne, double termTwo, std::string operator){

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
