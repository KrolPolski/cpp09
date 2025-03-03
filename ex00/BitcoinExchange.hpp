/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 10:56:30 by rboudwin          #+#    #+#             */
/*   Updated: 2025/02/26 14:08:21 by rboudwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <map>
#include <iostream>
#include <fstream>
#include <regex>
#include <iomanip>

class BitcoinExchange
{
private:
	std::map<std::string, float> _exchangeRates;
	std::multimap<std::string, float> _inputData;
	std::string _inputFileName;
	std::ifstream _inputFile;
	std::ifstream _dataFile;
	bool isValidDateFormat(const std::string& date);
	bool isValidDate(const std::string& date);
	float getConversionRate(const std::string& date);
	const std::string getNearestDate(const std::string& date);
	void convertData(std::pair<const std::string, float> item);

public:
	BitcoinExchange() = delete;
	BitcoinExchange(std::string inputFileName);
	BitcoinExchange(const BitcoinExchange& other) = delete;
	BitcoinExchange& operator=(const BitcoinExchange& other) = delete;
	~BitcoinExchange();
	void populateExchangeRates();
	void populateInputData();
};

