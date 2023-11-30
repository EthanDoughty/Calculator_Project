#ifndef CALCULATORS_H
#define CALCULATORS_H
#include <iostream>
#include <string>
#include <cmath>
#include <stack>
#include <sstream> 

bool isOperator(char);
bool isNum(char);
double solver(std::string);
bool errorHandler(std::string);
double expressionParser(std::string&, size_t&);
double termSolver(std::string&);
#endif
