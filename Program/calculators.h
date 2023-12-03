#ifndef CALCULATORS_H
#define CALCULATORS_H
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
double expressionParser(std::string&, size_t&);
double termSolver(std::string&);
#endif
