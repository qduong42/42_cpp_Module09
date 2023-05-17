#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <list>
#include <utility>

class PmergeMe
{
	private:

	int _straggler;

	public:
		int getStraggler()const;
		PmergeMe();
		PmergeMe(int, char **);
		PmergeMe(PmergeMe const& obj);
		PmergeMe& operator=(PmergeMe const& obj);
		~PmergeMe();
		// bool myComparison(const std::pair<int, int> &a, const std::pair<int, int> &b);
		static bool myComparison(const std::pair<int, int> &a, const std::pair<int, int> &b);
	class	invalidNumberException : public std::exception
	{
		const char *	what() const throw();
	};
};

#endif
