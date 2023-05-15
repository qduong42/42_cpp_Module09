#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <list>

class PmergeMe
{
	public:

		PmergeMe();
		PmergeMe(int, std::string);
		PmergeMe(PmergeMe const& obj);
		PmergeMe& operator=(PmergeMe const& obj);
		~PmergeMe();

	private:


};

#endif
