#include "../include/RPN.hpp"

//	CONSTRUCTORS | DESTRUCTOR

RPN::RPN():_result(-1), _numbers(std::stack<float>())
{}

void RPN::operateStack(char op)
{
	float op2;
	op2 = this->_numbers.top(); this->_numbers.pop();
	float op1;
	op1 = this->_numbers.top();this->_numbers.pop();
	switch (op)
	{
	case '+':
		this->_numbers.push(op1+op2);
		break;
	case '-':
		this->_numbers.push(op1-op2);
		break;
	case '/':
		if (op2 == 0)
			throw divideByZeroException();
		else
		{
			this->_numbers.push(op1/op2);
			break;
		}
	case '*':
		this->_numbers.push(op1*op2);
		break;
	}
}

RPN::RPN(std::string expression): _result(-1), _numbers(std::stack<float>())
{
	std::string valid = "0123456789+-*/ ";
	std::string::iterator last_element_it = expression.end();
	last_element_it --;
	for (std::string::iterator it = expression.begin(); it != expression.end(); it++)
	{
		if (valid.find(*it) == std::string::npos)
		{
			throw invalidStringException();
		}
		if (*it == ' ')
			continue;
		if (isdigit(*it))
		{
			std::string::iterator it_next = it;
			it_next++;
			if (it != last_element_it && *it_next != ' ')
				throw numberNextException();
			this->_numbers.push(*it - '0');
		}
		else if (this->_numbers.size() > 1)
		{
			std::string::iterator it_next = it;
			it_next++;
			if (it != last_element_it && *it_next != ' ')
				throw operatorNextException();
			operateStack(*it);
		}
		else
			throw notEnoughNumbersException();
	}
	if (this->_numbers.size() > 1)
		throw tooManyNumbersException();
	else
		_result = this->_numbers.top();
}

RPN::RPN(RPN const& obj):  _result(obj._result),
_numbers(obj._numbers)
{
}

RPN& RPN::operator=(RPN const& obj)
{
	if (this != &obj)
	{
	new (this) RPN(obj);
	}
	return (*this);
}

RPN::~RPN()
{}

//	MEMBER FUNCTIONS

float	RPN::getResult()
{
	return this->_result;
}

const char*	RPN::invalidStringException::what() const throw()
{
	return ("Error: Invalid String, special characters detected");
}

const char*	RPN::divideByZeroException::what() const throw()
{
	return ("Error: Can not divide by Zero my guy");
}

const char*	RPN::numberNextException::what() const throw()
{
	return ("Error: Number next not space");
}

const char*	RPN::operatorNextException::what() const throw()
{
	return ("Error: operator next not space");
}

const char*	RPN::notEnoughNumbersException::what() const throw()
{
	return ("Error: Not Enough numbers for operation");
}

const char*	RPN::tooManyNumbersException::what() const throw()
{
	return ("Error: still too many numbers in stack");
}
