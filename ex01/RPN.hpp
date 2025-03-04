/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:52:40 by rboudwin          #+#    #+#             */
/*   Updated: 2025/03/04 15:22:20 by rboudwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <cctype>

class RPN
{
    private:
        std::stack<double> _calcStack;
        const std::string _args;
        bool validateArgs();
        double calculate();
        void handleOperator(char c);
    public:
    RPN() = delete;
    RPN(std::string args);
    RPN(RPN &other) = delete;
    RPN& operator=(RPN &other) = delete;
    ~RPN();
};
