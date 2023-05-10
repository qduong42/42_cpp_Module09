#include <iostream>
#include <sstream>
#include <stack>

int main(int argc, char* argv[])
{
  std::stack<float> s;
    std::stringstream ss(argv[1]);
    char token;
    if (ss >> token)
    {
      std::cout << "Token:" << token << std::endl;
        s.push(token);
    }
    else
    {
        float operand2 = s.top();
        s.pop();
        float operand1 = s.top();
        s.pop();
        float result;
        if (token == '+')
        {
            result = operand1 + operand2;
        }
        else if (token == '-')
        {
            result = operand1 - operand2;
        }
        else if (token == '*')
        {
            result = operand1 * operand2;
        }
        else if (token == '/')
        {
            if (operand2 == 0) {
                std::cout << "Error: division by zero" << std::endl;
                return 1;
            }
            result = operand1 / operand2;
        }
        else
        {
            std::cout << "Error: invalid operator" << std::endl;
            return 1;
        }
        s.push(result);
    }
    std::cout << result << std::endl;
  return EXIT_SUCCESS;
}
