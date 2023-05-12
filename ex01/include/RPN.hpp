#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <string>
#include <stack>

class RPN
{
	private:

		float				_result;
		std::stack<float> _numbers;
	public:

		RPN();
		RPN(std::string);
		RPN(RPN const& obj);
		RPN& operator=(RPN const& obj);
		~RPN();

		void operateStack(char);
		float getResult();

	class	invalidStringException : public std::exception
	{
		const char *	what() const throw();
	};
	class	divideByZeroException : public std::exception
	{
		const char *	what() const throw();
	};
	class	numberNextException : public std::exception
	{
		const char *	what() const throw();
	};
	class	operatorNextException : public std::exception
	{
		const char *	what() const throw();
	};
	class	notEnoughNumbersException : public std::exception
	{
		const char *	what() const throw();
	};
	class	tooManyNumbersException : public std::exception
	{
		const char *	what() const throw();
	};
};

#endif
