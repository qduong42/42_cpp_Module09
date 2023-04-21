#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <string>
# include <map>

bool	validDateFormat(std::string);

bool	validDate(std::string);

class	BitcoinExchange
{
	private:
		const std::map<std::string, float>	_exchange;
	
	public:
		BitcoinExchange();
		BitcoinExchange(std::map<std::string, float>);
		BitcoinExchange(const BitcoinExchange &);
		~BitcoinExchange();
		BitcoinExchange&	operator=(const BitcoinExchange &);


		BitcoinExchange(std::string);

		// double		find(std::string);
		// std::string	firstDate();
		// std::string	lastDate();

	class	invalidFileException
	{
		const char *	what() const throw();
	};
};

#endif
