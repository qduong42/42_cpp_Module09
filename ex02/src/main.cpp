#include "../include/PmergeMe.hpp"
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char **argv)
{
	PmergeMe<std::vector<int>, std::vector<std::pair<int, int > > > seq;
	try
	{
		PmergeMe<std::vector<int>, std::vector<std::pair<int, int > > > try_create(argc, argv);
		seq = try_create;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
