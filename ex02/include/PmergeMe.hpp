#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include <iomanip>

#define SEC_TO_MS 1000000

class PmergeMe
{
	private:

	int _straggler;
	double getProcessorTime() const;
	int binarySearch(const std::vector<int>&, const int&, const int, const int)const;

	public:
		PmergeMe();
		PmergeMe(const int, char **);
		PmergeMe(PmergeMe const& obj);
		PmergeMe& operator=(PmergeMe const& obj);
		~PmergeMe();
		int getStraggler()const;
	class	invalidInputException : public std::exception
	{
		const char *	what() const throw();
	};
	class	isSortedException : public std::exception
	{
		const char *	what() const throw();
	};
};

#endif
