#include "../include/RPN.hpp"

//	CONSTRUCTORS | DESTRUCTOR

RPN::RPN():_result(-1), _numbers(std::stack<int>())
{}

void RPN::operateStack(char op)
{
	int op2;
	op2 = this->_numbers.top(); this->_numbers.pop();
	int op1;
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
			throw divideByZero();
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

RPN::RPN(std::string expression): _result(-1), _numbers(std::stack<int>())
{
	std::string valid = "0123456789+-*/ ";
	std::string::iterator ite = expression.end();
	ite --;
	for (std::string::iterator it = expression.begin(); it != expression.end(); it++)
	{
		if (valid.find(*it) == std::string::npos)
		{
			throw invalidString();
		}
		if (*it == ' ')
		{
			continue;
		}	
		if (isdigit(*it))
		{
			std::string::iterator it_next = it;
			it_next++;
			if (it != ite && *it_next != ' ')
				throw numberNext();
			this->_numbers.push(*it - '0');
		}
		else if (this->_numbers.size() > 1)
		{
			std::string::iterator it_next = it;
			it_next++;
			if (it != ite && *it_next != ' ')
				throw operatorNext();
			operateStack(*it);
		}
		else
			throw notEnoughNumbers();
	}
	if (this->_numbers.size() > 1)
		throw tooManyNumbers();
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

int	RPN::getResult()
{
	return this->_result;
}

const char*	RPN::invalidOperator::what() const throw()
{
	return ("Error: Invalid Operator");
}

const char*	RPN::invalidString::what() const throw()
{
	return ("Error: Invalid String, special characters detected");
}

const char*	RPN::divideByZero::what() const throw()
{
	return ("Error: Can not divide by Zero my guy");
}

const char*	RPN::numberNext::what() const throw()
{
	return ("Error: Number next not space");
}

const char*	RPN::operatorNext::what() const throw()
{
	return ("Error: operator next not space");
}

const char*	RPN::notEnoughNumbers::what() const throw()
{
	return ("Error: Not Enough numbers for operation");
}

const char*	RPN::tooManyNumbers::what() const throw()
{
	return ("Error: still too many numbers in stack");
}
