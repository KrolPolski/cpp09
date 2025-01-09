/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 10:56:26 by rboudwin          #+#    #+#             */
/*   Updated: 2025/01/09 12:32:02 by rboudwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(std::string inputFileName)
{	
	_inputFileName = inputFileName;
	_inputFile.open(inputFileName, std::fstream::in);
	if (!_inputFile.is_open())
		throw std::ios_base::failure("Failed to open input file");
	_dataFile.open("data.csv", std::fstream::in);
	if (!_inputFile.is_open())
		throw std::ios_base::failure("Failed to open data.csv");
}

BitcoinExchange::~BitcoinExchange()
{}
void BitcoinExchange::populateExchangeRates()
{
	std::string currLine;
	std::string date;
	float		value;
	
	size_t delimiter;
	while (std::getline(_dataFile, currLine))
	{
		delimiter = currLine.find(',');
		if (delimiter == currLine.npos)
			std::cout << "No delimiter found" << std::endl;
		else
		{
			date = currLine.substr(0, delimiter);
			if (date == "date")
				continue ;
			std::cout << date << std::endl;
			value = stof(currLine.substr(delimiter + 1));
			std::cout << currLine.substr(delimiter + 1) << " becomes " << value << std::endl;
			_exchangeRates.insert({date, value});
		}
		std::cout << std::endl << "Now displaying map: " << std::endl;
		for (const auto& pair : _exchangeRates)
		{
			std::cout << pair.first << ": " << pair.second << std::endl;
		}
	}
}