#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <string>
# include <map>
# include <exception>

bool	validDateFormat(std::string);

bool	validDate(std::string);

class	BitcoinExchange
{
	private:
		std::map<std::string, float>	_exchange;
	
	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &);
		~BitcoinExchange();
		BitcoinExchange&	operator=(const BitcoinExchange &);


		BitcoinExchange(std::map<std::string, float>);
		BitcoinExchange(std::string);

		float		find(std::string);
		void		printMap();
		void		print(float, float, std::string);
		// std::string	firstDate();
		// std::string	lastDate();

	class	invalidFileException : public std::exception
	{
		const char *	what() const throw();
	};

	class	precedeException : public std::exception
	{
		const char *	what() const throw();
	};

};

#endif
