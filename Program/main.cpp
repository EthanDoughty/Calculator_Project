#include <iostream>
#include <string>


double solver(std::string expression){
    double result{};
    
    return result;
}

int main(){
    std::cout << "Enter an expression: ";
    std::string expression;
    std::getline(std::cin, expression);
    double result = solver(expression);
    std::cout << "Answer: " << result << std::endl;
    return 0;
}
