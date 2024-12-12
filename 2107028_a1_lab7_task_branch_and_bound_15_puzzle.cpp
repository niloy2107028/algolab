#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define N 4

struct puzzle_state
{
    vector<vector<int>> board;
    int x, y; // for space
    int h;    // distance
};

vector<vector<int>> goal_state = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12},
    {13, 14, 15, 0}};

bool is_goal_achieved(const vector<vector<int>> &board)
{
    return board == goal_state;
}

bool is_valid_move(int x, int y)
{
    return (x >= 0 && x < N && y >= 0 && y < N);
}

int calculate_distance(const vector<vector<int>> &board)
{
    int dist = 0;
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            if (board[i][j] != 0)
            {
                int targetX = (board[i][j] - 1) / N;
                int targetY = (board[i][j] - 1) % N;
                dist += abs(i - targetX) + abs(j - targetY);
            }
        }
    }
    return dist;
}

void solve_15_puzzle(vector<vector<int>> &start_board)
{

    int space_x;
    int space_y;

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            if (start_board[i][j] == 0)
            {
                space_x = i;
                space_y = j;
            }
        }
    }

    int total_distance = calculate_distance(start_board);

    vector<int> moves_x = {0, 0, -1, 1};
    vector<int> moves_y = {-1, 1, 0, 0};

    queue <puzzle_state> pq;
}

int main()

{
    vector<vector<int>> start_board = {{1, 2, 3, 4}, {5, 6, 0, 8}, {9, 10, 7, 12}, {13, 14, 11, 15}};

    solve_15_puzzle(start_board);

    return 0;
}