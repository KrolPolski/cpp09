/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 13:11:57 by rboudwin          #+#    #+#             */
/*   Updated: 2025/04/06 13:26:30 by rboudwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <cstdlib>
bool RPN::validateArgs()
{
    if (_args == "")
        return false;
    std::istringstream iss(_args);
    std::string word;
    std::string allowed {"0123456789+-*/"};
    // check word by word that we are in the appropriate format
    while (iss >> word)
    {
        if (word.length() != 1)
            return false;
        if (allowed.find(word[0]) == std::string::npos)
            return false;
    }
    return true;
}

void RPN::handleOperator(char c)
{
    if (_calcStack.size() < 2)
    {
        std::cerr << "Error: Not enough operands for operator " << c << std::endl;
        exit(EXIT_FAILURE);
    }
    
    double secondOperand = _calcStack.top();
    _calcStack.pop();
    double firstOperand = _calcStack.top();
    _calcStack.pop();
    switch (c) 
    {
        case '+':
            _calcStack.push(firstOperand + secondOperand);
            break;
        case '-':
            _calcStack.push(firstOperand - secondOperand);
            break;
        case '*':
            _calcStack.push(firstOperand * secondOperand);
            break;
        case '/':
            _calcStack.push(firstOperand / secondOperand);
            break;
        default: 
            std::cerr << "Error: Invalid operator" << std::endl;
            exit(EXIT_FAILURE);
    }
}

double RPN::calculate()
{
    std::istringstream iss(_args);
    std::string word;
    
    while (iss >> word)
    {
        if (std::isdigit(word[0]))
            _calcStack.push(stod(word));
        else
            handleOperator(word[0]);
    }
    if (_calcStack.size() != 1)
    {
        std::cerr << "Error" << std::endl;
        exit(EXIT_FAILURE);
    }
    return (_calcStack.top());
}

RPN::RPN(std::string args) : _args(args)
{
    if (validateArgs())
        std::cout << calculate() << std::endl;
    else
        std::cerr << "Error" << std::endl;
}

RPN::~RPN()
{
}