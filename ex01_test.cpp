#include <iostream>
#include <stack>

int main()
{
	std::stack<int> intings;
	intings.push(5);
	intings.push(7);
	int a;
	// a = intings.pop();
	// pop removes from stack, but is not assignable: doesnt return an element, just does the operation
	std::cout << a << std::endl;
}