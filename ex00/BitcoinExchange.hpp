/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 10:56:30 by rboudwin          #+#    #+#             */
/*   Updated: 2025/01/09 11:51:45 by rboudwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <map>
#include <iostream>
#include <fstream>

class BitcoinExchange
{
private:
	std::multimap<std::string, float> _exchangeRates;
	std::multimap<std::string, float> _inputData;
	std::string _inputFileName;
	std::ifstream _inputFile;
	std::ifstream _dataFile;

public:
	BitcoinExchange() = delete;
	BitcoinExchange(std::string inputFileName);
	BitcoinExchange(const BitcoinExchange& other) = delete;
	BitcoinExchange& operator=(const BitcoinExchange& other) = delete;
	~BitcoinExchange();
	void populateExchangeRates();
};

