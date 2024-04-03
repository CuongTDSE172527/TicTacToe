#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BOARD_SIZE 3
#define MAX_NAME_LENGTH 50

// Function prototypes
void initializeBoard(char board[][BOARD_SIZE]);
void displayBoard(char board[][BOARD_SIZE]);
int isMoveValid(char board[][BOARD_SIZE], int row, int col);
int checkForWinner(char board[][BOARD_SIZE], char player);
int isBoardFull(char board[][BOARD_SIZE]);
void saveScore(int playerScore, int computerScore);
void displayScoreboard();

int main() {
    char board[BOARD_SIZE][BOARD_SIZE];
    char playerName[MAX_NAME_LENGTH];
    int playerScore = 0, computerScore = 0;
    char choice;
    int row, col;
    int difficulty;

    while (1) {
        printf("\n\n====== Tic Tac Toe Game ======\n");
        printf("1. Start Game\n");
        printf("2. Display Scoreboard\n");
        printf("3. Quit\n");
        printf("Enter your choice: ");
        scanf(" %c", &choice);
        getchar(); // Consume newline

        switch (choice) {
            case '1':
                // Load scoreboard
                displayScoreboard();

                // Prompt for player name
                printf("\nEnter your name: ");
                fgets(playerName, MAX_NAME_LENGTH, stdin);
                playerName[strcspn(playerName, "\n")] = 0; // Remove newline character

                while (1) {
                    // Initialize the board
                    initializeBoard(board);

                    // Prompt for difficulty level
                    printf("\nSelect difficulty level:\n");
                    printf("1. Easy\n");
                    printf("2. Hard\n");
                    printf("Enter your choice (1 or 2): ");
                    scanf("%d", &difficulty);
                    getchar(); // Consume newline

                    while (1) {
                        // Player's move
                        displayBoard(board);
                        printf("\n%s's turn (X). Enter row and column numbers (e.g., 1 2): ", playerName);
                        scanf("%d %d", &row, &col);
                        getchar(); // Consume newline

                        if (isMoveValid(board, row - 1, col - 1)) {
                            board[row - 1][col - 1] = 'X';
                            if (checkForWinner(board, 'X')) {
                                displayBoard(board);
                                printf("\nCongratulations, %s! You win!\n", playerName);
                                playerScore++;
                                break;
                            }
                            if (isBoardFull(board)) {
                                displayBoard(board);
                                printf("\nThe game is a draw!\n");
                                break;
                            }

                            // Computer's move
                            if (difficulty == 1) {
                                do {
                                    row = rand() % BOARD_SIZE;
                                    col = rand() % BOARD_SIZE;
                                } while (!isMoveValid(board, row, col));
                            } else { // Hard difficulty
                                // Implement AI logic for hard difficulty here (optional)
                                // For simplicity, let's just make random moves
                                do {
                                    row = rand() % BOARD_SIZE;
                                    col = rand() % BOARD_SIZE;
                                } while (!isMoveValid(board, row, col));
                            }

                            board[row][col] = 'O';
                            if (checkForWinner(board, 'O')) {
                                displayBoard(board);
                                printf("\nComputer wins!\n");
                                computerScore++;
                                break;
                            }
                            if (isBoardFull(board)) {
                                displayBoard(board);
                                printf("\nThe game is a draw!\n");
                                break;
                            }
                        } else {
                            printf("\nInvalid move! Try again.\n");
                        }
                    }

                    // Ask if the player wants to play again
                    printf("\nDo you want to play again? (y/n): ");
                    scanf(" %c", &choice);
                    getchar(); // Consume newline

                    if (choice != 'y' && choice != 'Y')
                        break;
                }

                // Save the final scores
                saveScore(playerScore, computerScore);
                break;

            case '2':
                // Display the scoreboard
                displayScoreboard();
                break;

            case '3':
                // Quit the game
                exit(0);
                break;

            default:
                printf("\nInvalid choice! Please enter a valid option.\n");
        }
    }

    return 0;
}

// Function to initialize the board with empty spaces
void initializeBoard(char board[][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = ' ';
        }
    }
}

// Function to display the current board state
void displayBoard(char board[][BOARD_SIZE]) {
    printf("\n");
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            printf(" %c ", board[i][j]);
            if (j != BOARD_SIZE - 1)
                printf("|");
        }
        printf("\n");
        if (i != BOARD_SIZE - 1) {
            printf("---|---|---\n");
        }
    }
}

// Function to check if a move is valid
int isMoveValid(char board[][BOARD_SIZE], int row, int col) {
    return (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE && board[row][col] == ' ');
}

// Function to check if there is a winner
int checkForWinner(char board[][BOARD_SIZE], char player) {
    // Check rows and columns
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
            return 1;
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player)
            return 1;
    }
    // Check diagonals
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
        return 1;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
        return 1;
    return 0;
}

// Function to check if the board is full
int isBoardFull(char board[][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == ' ')
                return 0; // Board is not full
        }
    }
    return 1; // Board is full
}

// Function to save the player and computer scores
void saveScore(int playerScore, int computerScore) {
    FILE *file = fopen("scoreboard.txt", "w");
    if (file != NULL) {
        fprintf(file, "Player: %d\nComputer: %d\n", playerScore, computerScore);
        fclose(file);
    }
}

// Function to display the scoreboard
void displayScoreboard() {
    FILE *file = fopen("scoreboard.txt", "r");
    if (file != NULL) {
        char line[100];
        while (fgets(line, sizeof(line), file)) {
            printf("%s", line);
        }
        fclose(file);
    }
}
