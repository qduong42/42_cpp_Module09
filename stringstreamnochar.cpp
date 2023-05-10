#include "../include/RPN.hpp"
#include <iostream>
#include <sstream>
#include <string>

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Enter 2 args" << std::endl;
		return (EXIT_FAILURE);
	}
	std::stringstream ss(argv[1]);
	float token;
	char hwew;
	token = -1;
	while(!ss.eof())
	{
		ss >> token;
		// ss >> hwew;
		std::cout << token << std::endl;
	}
	return (EXIT_SUCCESS);
}