#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <string>
#include <stack>

class RPN
{
	private:

		int				_result;
		std::stack<int> _numbers;
	public:

		RPN();
		RPN(std::string);
		RPN(RPN const& obj);
		RPN& operator=(RPN const& obj);
		~RPN();

		void operateStack(char);
		int getResult();

	class	invalidOperator : public std::exception
	{
		const char *	what() const throw();
	};
	class	invalidString : public std::exception
	{
		const char *	what() const throw();
	};
	class	divideByZero : public std::exception
	{
		const char *	what() const throw();
	};
	class	numberNext : public std::exception
	{
		const char *	what() const throw();
	};
	class	operatorNext : public std::exception
	{
		const char *	what() const throw();
	};
	class	notEnoughNumbers : public std::exception
	{
		const char *	what() const throw();
	};
	class	tooManyNumbers : public std::exception
	{
		const char *	what() const throw();
	};
};

#endif
