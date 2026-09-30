#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "stack.h"

bool is_number(const std::string &token)
{
    if (token.empty())
        return false;

    size_t start = 0;

    if (token[0] == '-' || token[0] == '+')
        start = 1;

    if (start == token.size())
        return false;

    for (size_t i = start; i < token.size(); ++i)
    {
        if (token[i] < '0' || token[i] > '9')
            return false;
    }

    return true;
}

bool find_end(
    const std::vector<std::string> &program,
    size_t start,
    size_t &end)
{
    int depth = 0;

    for (size_t i = start; i < program.size(); ++i)
    {
        if (program[i] == "cond")
        {
            ++depth;
        }
        else if (program[i] == "end")
        {
            if (depth == 0)
            {
                end = i;
                return true;
            }

            --depth;
        }
    }

    return false;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cerr << "Usage: Lab2 <script> <input>\n";
        return 1;
    }

    std::ifstream script_file(argv[1]);
    std::ifstream input_file(argv[2]);

    if (!script_file || !input_file)
    {
        std::cerr << "Cannot open input files\n";
        return 1;
    }

    std::vector<std::string> program;
    std::string token;

    while (script_file >> token)
    {
        program.push_back(token);
    }

    Stack *stack = stack_create();

    while (input_file >> token)
    {
        if (!is_number(token))
        {
            std::cerr << "Invalid input: " << token << '\n';
            stack_delete(stack);
            return 1;
        }

        stack_push(stack, std::stoi(token));
    }

    int loop_variable = 0;
    size_t last_setr = 0;
    bool has_setr = false;

    size_t ip = 0;

    while (ip < program.size())
    {
        const std::string &command = program[ip];

        if (is_number(command))
        {
            stack_push(stack, std::stoi(command));
            ++ip;
        }

        else if (command == "peek")
        {
            if (stack_empty(stack))
            {
                std::cerr << "peek on empty stack\n";
                stack_delete(stack);
                return 1;
            }

            std::cout << stack_get(stack) << ' ';
            ++ip;
        }

        else if (command == "setr")
        {
            if (stack_empty(stack))
            {
                std::cerr << "setr on empty stack\n";
                stack_delete(stack);
                return 1;
            }

            loop_variable = stack_get(stack);
            stack_pop(stack);

            last_setr = ip;
            has_setr = true;

            ++ip;
        }

        else if (command == "repeat")
        {
            if (!has_setr)
            {
                std::cerr << "repeat without setr\n";
                stack_delete(stack);
                return 1;
            }

            if (loop_variable > 0)
            {
                --loop_variable;
                ip = last_setr + 1;
            }
            else
            {
                ++ip;
            }
        }

        else if (command == "add")
        {
            if (stack_empty(stack))
            {
                std::cerr << "add: not enough values\n";
                stack_delete(stack);
                return 1;
            }

            int a = stack_get(stack);
            stack_pop(stack);

            if (stack_empty(stack))
            {
                std::cerr << "add: not enough values\n";
                stack_delete(stack);
                return 1;
            }

            int b = stack_get(stack);
            stack_pop(stack);

            stack_push(stack, a + b);
            ++ip;
        }

        else if (command == "sub")
        {
            if (stack_empty(stack))
            {
                std::cerr << "sub: not enough values\n";
                stack_delete(stack);
                return 1;
            }

            int a = stack_get(stack);
            stack_pop(stack);

            if (stack_empty(stack))
            {
                std::cerr << "sub: not enough values\n";
                stack_delete(stack);
                return 1;
            }

            int b = stack_get(stack);
            stack_pop(stack);

            stack_push(stack, b - a);
            ++ip;
        }

        else if (command == "mul")
        {
            if (stack_empty(stack))
            {
                std::cerr << "mul: not enough values\n";
                stack_delete(stack);
                return 1;
            }

            int a = stack_get(stack);
            stack_pop(stack);

            if (stack_empty(stack))
            {
                std::cerr << "mul: not enough values\n";
                stack_delete(stack);
                return 1;
            }

            int b = stack_get(stack);
            stack_pop(stack);

            stack_push(stack, a * b);
            ++ip;
        }

        else if (command == "div")
        {
            if (stack_empty(stack))
            {
                std::cerr << "div: not enough values\n";
                stack_delete(stack);
                return 1;
            }

            int a = stack_get(stack);
            stack_pop(stack);

            if (stack_empty(stack))
            {
                std::cerr << "div: not enough values\n";
                stack_delete(stack);
                return 1;
            }

            int b = stack_get(stack);
            stack_pop(stack);

            if (a == 0)
            {
                std::cerr << "division by zero\n";
                stack_delete(stack);
                return 1;
            }

            stack_push(stack, b / a);
            ++ip;
        }

        else if (command == "sq")
        {
            if (stack_empty(stack))
            {
                std::cerr << "sq on empty stack\n";
                stack_delete(stack);
                return 1;
            }

            int value = stack_get(stack);
            stack_pop(stack);

            stack_push(stack, value * value);
            ++ip;
        }

        else if (command == "sqrt")
        {
            if (stack_empty(stack))
            {
                std::cerr << "sqrt on empty stack\n";
                stack_delete(stack);
                return 1;
            }

            int value = stack_get(stack);
            stack_pop(stack);

            if (value < 0)
            {
                std::cerr << "sqrt of negative value\n";
                stack_delete(stack);
                return 1;
            }

            stack_push(
                stack,
                static_cast<int>(std::sqrt(value))
            );

            ++ip;
        }

        else if (command == "get")
        {
            int value;

            if (!(input_file >> value))
            {
                std::cerr << "not enough input\n";
                stack_delete(stack);
                return 1;
            }

            stack_push(stack, value);
            ++ip;
        }

        else if (command == "cond")
        {
            if (stack_empty(stack))
            {
                std::cerr << "cond: not enough values\n";
                stack_delete(stack);
                return 1;
            }

            int first = stack_get(stack);
            stack_pop(stack);

            if (stack_empty(stack))
            {
                std::cerr << "cond: not enough values\n";
                stack_delete(stack);
                return 1;
            }

            int second = stack_get(stack);

            size_t end;

            if (!find_end(program, ip + 1, end))
            {
                std::cerr << "cond without end\n";
                stack_delete(stack);
                return 1;
            }

            if (first == second)
            {
                stack_pop(stack);
                ++ip;
            }
            else
            {
                ip = end + 1;
            }
        }

   
        else if (command == "end")
        {
            ++ip;
        }

        else
        {
            std::cerr << "Unknown command: " << command << '\n';
            stack_delete(stack);
            return 1;
        }
    }

    stack_delete(stack);

    std::cout << '\n';

    return 0;
}