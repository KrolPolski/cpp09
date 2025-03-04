/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 13:11:57 by rboudwin          #+#    #+#             */
/*   Updated: 2025/03/04 15:03:35 by rboudwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
bool RPN::validateArgs()
{
    std::cout << "Inside validateArgs" << std::endl;
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

double RPN::calculate()
{
   return 0; 
}

RPN::RPN(std::string args) : _args(args)
{
    std::cout << "RPN constructor called" << std::endl;
    std::cout << _args << std::endl;
    if (validateArgs())
        calculate();
    else
        std::cerr << "Error" << std::endl;
}

RPN::~RPN()
{
    std::cout << "RPN destructor called" << std::endl;
}