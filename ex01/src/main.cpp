#include "../include/RPN.hpp"
#include <iostream>
#include <string>

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Enter 2 args" << std::endl;
		return (EXIT_FAILURE);
	}
	RPN exp;
	try
	{
		RPN expression(argv[1]);
		exp = expression;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return (EXIT_FAILURE);
	}
	std::cout << exp.getResult() << std::endl;
	return (EXIT_SUCCESS);
}
