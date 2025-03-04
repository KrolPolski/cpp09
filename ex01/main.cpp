/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:50:19 by rboudwin          #+#    #+#             */
/*   Updated: 2025/03/04 16:23:22 by rboudwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
int main(int argc, char **argv)
{
    if (argc!= 2)
        std::cout << "Please provide operators and operands in quotes, i.e. \"2 4 + 4 *\"" << std::endl;
    else
    {
        std::string args(argv[1]);
        RPN rpn(args);
    }
}