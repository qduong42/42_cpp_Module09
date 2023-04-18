#include "../include/BitcoinExchange.hpp"

#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <string>

bool	validDateFormat(std::string str)
{
	std::cout << "str: " << str << std::endl;
	if (str.length() != 10)
		return (false);
	for (size_t i = 0; i < str.length(); ++i)
	{
		if ((i == 4 || i == 7) && str[i] != '-')
			return (false);
	}
	return (true);
}

bool	checkDate(std::string str)
{
	if (!validDateFormat(str))
		return (false);
	int	month = std::atoi(str.substr(5, 7).c_str());
	std::cout << "month: " << month << std::endl;
	int	day = std::atoi(str.substr(8, 10).c_str());
	std::cout << "day: " << day << std::endl;
	if (month > 12 || day > 31 || month == 0 || day == 0)
		return (false);
	return (true);
}

int checkDate(std::string buffer)
{
	int pos = 0;
	std::string year;
	std::cout << "CheckDate buffer: " << buffer << "END" << std::endl;
	size_t end = buffer.find_last_not_of(" ");
    buffer = (end == std::string::npos) ? "" : buffer.substr(0, end + 1);
	std::cout << "CheckDate buffer: " << buffer << "END" << std::endl;
	while (1)
	{
		if (buffer.find("-") == std::string::npos)
			break ;
		if (buffer.find("-"))
		{
			year = buffer.substr(pos, buffer.find("-"));
			std::cout << "Year: " << year << std::endl;
			pos = buffer.find("-") + 1;
			std::cout << "pos: " << pos << std::endl;
			buffer = buffer.substr(pos, end + 1);
			std::cout << "new buffer: " << buffer << std::endl;
			std::cout << "find value of buffer.find(\"-\"): " << buffer.find("-") << std::endl;
		}
	}
	return (true);
}

int main(int argc, char **argv)
{
	if (argc == 2)
	{
		std::fstream	inFile(argv[1]);
		if (inFile.fail())
		{
			std::cerr << "Error. could not open input file." << std::endl;
			return (EXIT_FAILURE);
		}
		std::string		dataFileName("data.csv");
		std::fstream	dataFile(dataFileName.c_str());

		if (dataFile.fail())
		{
			std::cerr << "Error. could not open database file (data.csv). Make sure data.csv is in same folder as btc" << std::endl;
			return (EXIT_FAILURE);
		}
		// std::string buffer;
		// std::getline(inFile, buffer);
		// while (buffer.length() != 0)
		// {
		// std::getline(inFile, buffer);
		// std::cout << buffer << std::endl;
		// }
		std::string	buffer;
		while (getline(inFile, buffer))
		{
			// std::cout << buffer << std::endl;
			// size_t i = 0;
			// i = buffer.find("|");
			if (buffer == "date | value")
			{
				continue;
			}
			if (buffer.find("|") == std::string::npos || buffer.find("|") == buffer.size() - 1)
			{
				std::cerr << "Error: invalid input line." << std::endl;
				continue;
			}
			int pipePos = buffer.find("|");
			std::cout << "pipePos: " << pipePos << std::endl;
			if (checkDate(buffer.substr(0, pipePos)))
				continue;
			// std:: cout << i << std::endl;
			// std::cout << buffer.size() - 1 << std::endl;
		}
		inFile.close();
	}
	else
	{
		std::cerr << "Error: invalid number of arguments." << std::endl;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}