#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "queue.h"

static std::vector<int> neighbors(const std::vector<std::string> &maze,
                                  int row, int col)
{
    const int rows = static_cast<int>(maze.size());
    const int cols = static_cast<int>(maze[0].size());
    std::vector<int> result;

    const auto add = [&](int r, int c)
    {
        if (r >= 0 && r < rows && c >= 0 && c < cols && maze[r][c] != '#')
        {
            result.push_back(r * cols + c);
        }
    };

    add(row, col - 1);
    add(row, col + 1);
    add(row - 1, col);
    add(row - 1, col + 1);
    add(row + 1, col - 1);
    add(row + 1, col);

    return result;
}

static int expand_level(Queue *queue, std::vector<int> &parent,
                        const std::vector<int> &other_parent,
                        const std::vector<std::string> &maze, int &level_size)
{
    int next_level_size = 0;
    for (int i = 0; i < level_size; ++i)
    {
        const int cell = queue_get(queue);
        queue_remove(queue);
        const int cols = static_cast<int>(maze[0].size());
        for (int next : neighbors(maze, cell / cols, cell % cols))
        {
            if (parent[next] == -1)
            {
                parent[next] = cell;
                queue_insert(queue, next);
                ++next_level_size;
                if (other_parent[next] != -1)
                {
                    level_size = next_level_size;
                    return next;
                }
            }
        }
    }
    level_size = next_level_size;
    return -1;
}

static void print_maze(const std::vector<std::string> &maze)
{
    const int rows = static_cast<int>(maze.size());
    const int cols = static_cast<int>(maze[0].size());
    std::cout << " ";
    for (int col = 0; col < cols; ++col)
    {
        std::cout << '/' << ' ' << '\\';
        if (col + 1 < cols) std::cout << ' ';
    }
    std::cout << '\n';

    for (int row = 0; row < rows; ++row)
    {
        std::cout << std::string(static_cast<std::size_t>(2 * row), ' ') << '|';
        for (int col = 0; col < cols; ++col)
        {
            const char cell = maze[row][col] == '.' ? ' ' : maze[row][col];
            std::cout << ' ' << cell << " |";
        }
        std::cout << '\n' << std::string(static_cast<std::size_t>(2 * row + 1), ' ');
        for (int col = 0; col < cols; ++col)
        {
            std::cout << '\\' << ' ' << '/';
            if (col + 1 < cols) std::cout << ' ';
        }
        if (row + 1 < rows)
        {
            std::cout << ' ' << '\\';
        }
        std::cout << '\n';
    }
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        return 1;
    }

    std::ifstream input(argv[1]);
    std::vector<std::string> maze;
    std::string line;
    while (std::getline(input, line))
    {
        if (!line.empty() && line.back() == '\r')
        {
            line.pop_back();
        }
        if (!line.empty())
        {
            maze.push_back(line);
        }
    }

    const int rows = static_cast<int>(maze.size());
    const int cols = static_cast<int>(maze[0].size());
    int start = -1;
    int finish = -1;
    for (int row = 0; row < rows; ++row)
    {
        for (int col = 0; col < cols; ++col)
        {
            if (maze[row][col] == 'S') start = row * cols + col;
            if (maze[row][col] == 'E') finish = row * cols + col;
        }
    }

    std::vector<int> from_start(static_cast<std::size_t>(rows * cols), -1);
    std::vector<int> from_finish(static_cast<std::size_t>(rows * cols), -1);
    Queue *start_queue = queue_create();
    Queue *finish_queue = queue_create();
    from_start[start] = start;
    from_finish[finish] = finish;
    queue_insert(start_queue, start);
    queue_insert(finish_queue, finish);
    int start_level_size = 1;
    int finish_level_size = 1;
    int meeting = -1;

    while (meeting == -1 && !queue_empty(start_queue) && !queue_empty(finish_queue))
    {
        meeting = expand_level(start_queue, from_start, from_finish,
                               maze, start_level_size);
        if (meeting == -1)
        {
            meeting = expand_level(finish_queue, from_finish, from_start,
                                   maze, finish_level_size);
        }
    }

    queue_delete(start_queue);
    queue_delete(finish_queue);

    if (meeting != -1)
    {
        for (int cell = meeting; cell != start; cell = from_start[cell])
        {
            if (cell != finish) maze[cell / cols][cell % cols] = 'x';
        }
        for (int cell = meeting; cell != finish; cell = from_finish[cell])
        {
            if (cell != start) maze[cell / cols][cell % cols] = 'x';
        }
    }

    print_maze(maze);
    return meeting == -1 ? 1 : 0;
}
