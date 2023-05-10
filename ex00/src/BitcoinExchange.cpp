#include "../include/BitcoinExchange.hpp"

#include <iterator>
#include <utility>
#include <cstdlib>
#include <fstream>
#include <string>
#include <iostream>

//	CONSTRUCTORS | DESTRUCTOR

BitcoinExchange::BitcoinExchange():
	_exchange(std::map<std::string, float>())
{

}

BitcoinExchange::BitcoinExchange(const BitcoinExchange & other):
	_exchange(other._exchange)
{
	
}

BitcoinExchange::~BitcoinExchange()
{}



BitcoinExchange &	BitcoinExchange::operator=(const BitcoinExchange & other)

{
	if (this != &other)
	{
		new (this) BitcoinExchange(other);
	}
	return (*this);
}

BitcoinExchange::BitcoinExchange(std::map<std::string, float> map):
	_exchange(map)
{

}

BitcoinExchange::BitcoinExchange(std::string dataFileName):
	_exchange(std::map<std::string, float>())
{
	std::map<std::string, float>	data;
	std::fstream					dataFile(dataFileName.c_str());

	if (dataFile.fail())
		throw	invalidFileException();

	std::string	buffer;
	while (getline(dataFile, buffer))
	{
		if (buffer == "date,exchange_rate")
			continue;
		
		std::size_t	commaPos = buffer.find(',');
		std::string	dateStr(buffer.substr(0, commaPos));
		std::string	priceStr(buffer.substr(commaPos + 1, buffer.length()));
		std::pair<std::string, float>	pair;
		pair = make_pair(dateStr, atof(priceStr.c_str()));
		data.insert(pair);
	}
	dataFile.close();
	new (this) BitcoinExchange(data);
	// for(std::map<std::string, float>::const_iterator it = this->_exchange.begin();
	// 	it != this->_exchange.end(); ++it)
	// {
	// 	std::cout << it->first << " " << it->second << "\n";
	// }
}

void BitcoinExchange::print(float result, float value, std::string date)
{
	float output;
	output = value * result;
	size_t end = date.find_last_not_of(" ");
    date = (end == std::string::npos) ? "" : date.substr(0, end + 1);
	std:: cout << date << " | " << output << std::endl;
}

float BitcoinExchange::find(std::string date)
{
	float value;
	value = -1;
	size_t end = date.find_last_not_of(" ");
    date = (end == std::string::npos) ? "" : date.substr(0, end + 1);
	std::cout << date << "END" <<std::endl;
	std::cout << this->_exchange.begin()->first << std::endl;
	if (date < this->_exchange.begin()->first)
	{
		throw	precedeException();
	}
	std::map<std::string, float>::const_iterator end_it = this->_exchange.end();
	end_it--;
	std::cout << "DATE" << date << "END FIRST" << end_it->first << std::endl;
	std::map<std::string, float>::const_iterator iter = this->_exchange.find(date);
    if (iter != this->_exchange.end()) {
        value = iter->second;
    }
    else {
        iter = this->_exchange.upper_bound(date);
        iter--;
        value = iter->second;
    }
	return value;
}


const char*	BitcoinExchange::invalidFileException::what() const throw()
{
	return ("Error: BitcoinExchange: invalid data file.");
}

const char*	BitcoinExchange::precedeException::what() const throw()
{
	return ("Error: Date preceeds exchange data");
}

//	MEMBER FUNCTIONS

void	BitcoinExchange::printMap()
{
	std::map<std::string, float>::iterator it2;
	std::cout << "PRINT BITCH" << std::endl;
	for (it2 = this->_exchange.begin(); it2 != this->_exchange.end(); it2++)
	{
		std::cout << "DATE:" << it2->first << std::endl;
	}
}
