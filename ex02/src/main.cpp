#include "../include/PmergeMe.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <deque>

int main(int argc, char **argv)
{
	PmergeMe<std::vector<int>, std::vector<std::pair<int, int > > > vector_container;
	try
	{
		PmergeMe<std::vector<int>, std::vector<std::pair<int, int > > > try_create(argc, argv);
		vector_container = try_create;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return (EXIT_FAILURE);
	}
	PmergeMe<std::deque<int>, std::deque<std::pair<int, int> > > deque_container;
	try
	{
		PmergeMe<std::deque<int>, std::deque<std::pair<int, int> > > try_create(argc, argv);
		deque_container = try_create;
	}
	catch(const std::exception&e)
	{
		std::cerr << e.what() << std::endl;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
