#include <iostream>
#include <cstring>

using namespace std;

const int ROWS = 5;
const int COLS = 5;

void display_grid(char grid[ROWS][COLS]);
bool move_player(char grid[ROWS][COLS], int &player_row, int &player_col, char direction);

int main()
{

    // initialize 5x5 grid with empty spaces
    char grid[ROWS][COLS] = {
        {'P', '.', '.', '.', '.'},
        {'0', '.', '.', 'O', '.'},
        {'.', '.', '.', 'O', '.'},
        {'.', 'O', '.', '.', '.'},
        {'.', '.', '.', 'O', 'G'} // Goal at the bottom-right corner
    };
    int goal_row = 4;
    int goal_col = 4;
    int player_row, player_col;
    // Player's initial position
    bool validPosition = false;
    while (!validPosition)
    {
        cout << "Choose starting coordinates (row col): ";
        cin >> player_row >> player_col;

        // Validate input
        if (player_row >= 0 && player_row < ROWS && player_col >= 0 && player_col < COLS &&
            grid[player_row][player_col] != 'O' && grid[player_row][player_col] != 'G')
        {
            validPosition = true;
            grid[player_row][player_col] = 'P'; // Place the player
        }
        else
        {
            cout << "Invalid position. Please try again." << endl;
        }
    }

    // Game loop
    char direction;
    bool reached_goal = false;

    cout << "Welcome to the Grid Game!" << endl;
    cout << "Move using W (up), A (left), S (down), D (right). Reach the goal (G)." << endl;

    while (!reached_goal)
    {
        // Display the current grid
        display_grid(grid);

        // Get the player's move
        cout << "Enter direction (W/A/S/D): ";
        cin >> direction;

        // Move the player
        if (move_player(grid, player_row, player_col, direction))
        {
            // Check if the player has reached the goal
            if (grid[goal_row][goal_col] == 'P')
            {
                display_grid(grid);
                reached_goal = true;
                cout << "Congratulations! You've reached the goal!" << endl;
                return 0;
            }
        }
        else
        {
            cout << "Invalid move. Try again!" << endl;
        }
    }

    return 0;
}

// Function to display the grid
void display_grid(char grid[ROWS][COLS])
{
    for (int i = 0; i < ROWS; ++i)
    {
        for (int j = 0; j < COLS; ++j)
        {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// Function to move the player
bool move_player(char grid[ROWS][COLS], int &player_row, int &player_col, char direction)
{
    // Calculate the new position based on the direction
    int new_row = player_row;
    int new_col = player_col;

    switch (toupper(direction))
    {
    case 'W':
        new_row--;
        break; // Up
    case 'A':
        new_col--;
        break; // Left
    case 'S':
        new_row++;
        break; // Down
    case 'D':
        new_col++;
        break; // Right
    case 'E':  // Diagonal Down-Right (Southeast)
        new_row++;
        new_col++;
        break;
    case 'Q': // Diagonal Up-Left (Northwest)
        new_row--;
        new_col--;
        break;
    default:
        return false; // Invalid direction
    }

    // Check if the new position is out of bounds
    if (new_row < 0 || new_row >= ROWS || new_col < 0 || new_col >= COLS)
    {
        return false;
    }

    // Check if the new position is an obstacle
    if (grid[new_row][new_col] == 'O')
    {
        return false;
    }

    // Move the player to the new position
    grid[player_row][player_col] = '.'; // Clear the old position
    player_row = new_row;
    player_col = new_col;
    grid[player_row][player_col] = 'P'; // Place the player at the new position

    return true;
}
