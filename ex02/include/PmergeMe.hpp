#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include <iomanip>

class PmergeMe
{
	private:

	int _straggler;

	public:
		PmergeMe();
		PmergeMe(const int, char **);
		PmergeMe(PmergeMe const& obj);
		PmergeMe& operator=(PmergeMe const& obj);
		~PmergeMe();
		static bool myComparison(const std::pair<int, int> &a, const std::pair<int, int> &b);
		void make_jacobs_sequence(std::vector<std::pair<int, int > >& paired_vectr, std::vector<int>& jacobs_num);
		int getStraggler()const;
	class	invalidNumberException : public std::exception
	{
		const char *	what() const throw();
	};
	class	isSortedException : public std::exception
	{
		const char *	what() const throw();
	};
};

#endif
