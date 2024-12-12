#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <cmath>

using namespace std;

#define N 4  // 4x4 puzzle for 15-puzzle

// Structure for puzzle state
struct PuzzleState {
    vector<vector<int>> board;
    int x, y;        // Position of the empty tile
    int g, h;        // g: moves from start, h: heuristic
    string moves;    // Moves to reach this state from start
    
    // Operator overload to compare states in priority queue
    bool operator>(const PuzzleState& other) const {
        return (g + h) > (other.g + other.h);
    }
};

// Goal state of the puzzle
vector<vector<int>> goalState = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12},
    {13, 14, 15, 0}
};

// Calculate Manhattan distance heuristic
int calculateManhattanDistance(const vector<vector<int>>& board) {
    int dist = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (board[i][j] != 0) {
                int targetX = (board[i][j] - 1) / N;
                int targetY = (board[i][j] - 1) % N;
                dist += abs(i - targetX) + abs(j - targetY);
            }
        }
    }
    return dist;
}

// Check if a board is the goal state
bool isGoal(const vector<vector<int>>& board) {
    return board == goalState;
}

// Check if a move is valid within the puzzle bounds
bool isValidMove(int x, int y) {
    return x >= 0 && x < N && y >= 0 && y < N;
}

// Branch and Bound approach to solve the 15-puzzle
string solve15Puzzle(vector<vector<int>>& startBoard) {
    int startX, startY;
    
    // Find the empty tile's position
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (startBoard[i][j] == 0) {
                startX = i;
                startY = j;
            }
        }
    }
    
    // Priority queue for branch and bound
    priority_queue<PuzzleState, vector<PuzzleState>, greater<PuzzleState>> pq;
    unordered_set<string> visited;

    int h = calculateManhattanDistance(startBoard);
    pq.push({startBoard, startX, startY, 0, h, ""});
    
    // Possible moves: left, right, up, down
    vector<int> dx = {0, 0, -1, 1};
    vector<int> dy = {-1, 1, 0, 0};
    string dir = "LRUD";

    while (!pq.empty()) {
        PuzzleState curr = pq.top();
        pq.pop();

        // Convert board state to string for checking if visited
        string boardStr;
        for (auto& row : curr.board) {
            for (int val : row) {
                boardStr += to_string(val) + ",";
            }
        }

        if (visited.find(boardStr) != visited.end()) continue;
        visited.insert(boardStr);

        // If goal state reached, return the moves
        if (isGoal(curr.board)) return curr.moves;

        // Explore possible moves
        for (int i = 0; i < 4; ++i) {
            int newX = curr.x + dx[i];
            int newY = curr.y + dy[i];

            if (isValidMove(newX, newY)) {
                // Create new state after moving the empty tile
                vector<vector<int>> newBoard = curr.board;
                swap(newBoard[curr.x][curr.y], newBoard[newX][newY]);

                int newH = calculateManhattanDistance(newBoard);
                int newG = curr.g + 1;

                pq.push({newBoard, newX, newY, newG, newH, curr.moves + dir[i]});
            }
        }
    }

    return "No solution found";
}

// Driver code
int main() {
    vector<vector<int>> startBoard = {
        {1, 2, 3, 4},
        {5, 6, 0, 8},
        {9, 10, 7, 12},
        {13, 14, 11, 15}
    };
    
    string result = solve15Puzzle(startBoard);
    cout << "Solution Moves: " << result << endl;
    return 0;
}
