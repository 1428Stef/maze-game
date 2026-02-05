#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

#define W 31
#define H 21

char maze[H][W];
int px = 1, py = 1;
int difficulty = 1; // 1 - Easy, 2 - Medium, 3 - Hard
int speed = 100; 

void clear_screen() {
    system("cls");
}

void init_maze() {
    for (int y = 0; y < H; y++)
        for (int x = 0; x < W; x++)
            maze[y][x] = '#';
}

void shuffle(int dirs[4][2]) {
    for (int i = 0; i < 4; i++) {
        int r = rand() % 4;
        int tx = dirs[i][0];
        int ty = dirs[i][1];
        dirs[i][0] = dirs[r][0];
        dirs[i][1] = dirs[r][1];
        dirs[r][0] = tx;
        dirs[r][1] = ty;
    }
}

void carve(int x, int y) {
    int dirs[4][2] = {{2,0},{-2,0},{0,2},{0,-2}};
    shuffle(dirs);

    for (int i = 0; i < 4; i++) {
        int nx = x + dirs[i][0];
        int ny = y + dirs[i][1];
        if (nx > 0 && ny > 0 && nx < W-1 && ny < H-1 && maze[ny][nx] == '#') {
            maze[ny][nx] = ' ';
            maze[y + dirs[i][1]/2][x + dirs[i][0]/2] = ' ';
            carve(nx, ny);
        }
    }
}

void generate_maze() {
    init_maze();
    maze[1][1] = ' ';
    carve(1, 1);
    maze[H-2][W-2] = 'X';
}

void draw_maze() {
    clear_screen();
    for (int y = 0; y < H; y++) {
        for (int x = 0; x < W; x++) {
            if (x == px && y == py)
                putchar('@');
            else
                putchar(maze[y][x]);
        }
        putchar('\n');
    }
    printf("\nDifficulty: ");
    if (difficulty == 1) printf("Easy (Speed: Slow)");
    else if (difficulty == 2) printf("Medium (Speed: Normal)");
    else printf("Hard (Speed: Fast)");
    printf(" | ESC - Menu | P - Pause\n");
}

void pause_game() {
    clear_screen();
    printf("=== GAME PAUSED ===\n\n");
    printf("Press any key to continue...\n");
    _getch();
}

void play_game() {
    px = py = 1;
    generate_maze();

    while (1) {
        draw_maze();
        
        if (_kbhit()) {
            int ch = _getch();

            // Escape to menu
            if (ch == 27) {
                clear_screen();
                printf("Returning to menu...\n");
                Sleep(500);
                break;
            }

            // Pause
            if (ch == 'P' || ch == 'p') {
                pause_game();
                continue;
            }

            int nx = px, ny = py;

            if (ch == 224) { // arrow keys
                ch = _getch();
                if (ch == 72) ny--; // up
                if (ch == 80) ny++; // down
                if (ch == 75) nx--; // left
                if (ch == 77) nx++; // right
            }

            if (maze[ny][nx] != '#') {
                px = nx;
                py = ny;
            }

            if (maze[py][px] == 'X') {
                clear_screen();
                printf("YOU WIN!\n");
                printf("Difficulty: ");
                if (difficulty == 1) printf("Easy");
                else if (difficulty == 2) printf("Medium");
                else printf("Hard");
                printf("\n\nPress any key to return to menu...\n");
                _getch();
                break;
            }
        }
        Sleep(speed);
    }
}

void difficulty_menu() {
    int choice = 0;
    const char *items[] = {
        "1. Easy (Slow)",
        "2. Medium (Normal)",
        "3. Hard (Fast)",
        "4. Back"
    };

    while (1) {
        clear_screen();
        printf("=== SELECT LEVEL ===\n\n");
        for (int i = 0; i < 4; i++) {
            if (i == choice)
                printf(" > %s\n", items[i]);
            else
                printf("   %s\n", items[i]);
        }

        int ch = _getch();

        if (ch == 224) {
            ch = _getch();
            if (ch == 72 && choice > 0) choice--;
            if (ch == 80 && choice < 3) choice++;
        }
        else if (ch >= '1' && ch <= '4') {
            choice = ch - '1';
        }
        else if (ch == 13) { // Enter
            if (choice == 0) {
                difficulty = 1;
                speed = 150;
            }
            else if (choice == 1) {
                difficulty = 2;
                speed = 100;
            }
            else if (choice == 2) {
                difficulty = 3;
                speed = 50;
            }
            else if (choice == 3) {
                break;
            }
            if (choice < 3) {
                clear_screen();
                printf("Difficulty set to: ");
                if (difficulty == 1) printf("Easy\n");
                else if (difficulty == 2) printf("Medium\n");
                else printf("Hard\n");
                Sleep(800);
                break;
            }
        }
    }
}

void leaders_menu() {
    clear_screen();
    printf("=== LEADERBOARD ===\n\n");
    printf("Feature not implemented yet.\n\n");
    printf("This menu will display the best players\n");
    printf("and their completion times.\n\n");
    printf("Press any key to return...\n");
    _getch();
}

void about_menu() {
    clear_screen();
    printf("=== ABOUT GAME ===\n\n");
    printf("Maze Game v1.0\n");
    printf("Language: C\n");
    printf("Platform: Windows\n\n");
    printf("Controls:\n");
    printf("  - Arrow keys or numeric keys (1-5): Move\n");
    printf("  - P: Pause game\n");
    printf("  - ESC: Return to menu\n\n");
    printf("Goal: Reach the exit (X) to win!\n");
    printf("Navigate through the randomly generated maze.\n\n");
    printf("Press any key to return...\n");
    _getch();
}

void menu() {
    int choice = 0;
    const char *items[] = {
        "1. Start Game",
        "2. Level",
        "3. Leaders",
        "4. About",
        "5. Exit"
    };

    while (1) {
        clear_screen();
        printf("=== MAZE GAME ===\n\n");
        for (int i = 0; i < 5; i++) {
            if (i == choice)
                printf(" > %s\n", items[i]);
            else
                printf("   %s\n", items[i]);
        }
        printf("\nUse arrow keys or numbers to navigate\n");
        printf("Press ENTER to select\n");

        int ch = _getch();

        if (ch == 224) {
            ch = _getch();
            if (ch == 72 && choice > 0) choice--;
            if (ch == 80 && choice < 4) choice++;
        }
        else if (ch >= '1' && ch <= '5') {
            choice = ch - '1';
        }
        else if (ch == 13) { // Enter
            switch (choice) {
                case 0:
                    play_game();
                    break;
                case 1:
                    difficulty_menu();
                    break;
                case 2:
                    leaders_menu();
                    break;
                case 3:
                    about_menu();
                    break;
                case 4:
                    clear_screen();
                    printf("Thanks for playing!\n");
                    Sleep(800);
                    return;
            }
        }
    }
}

int main() {
    srand((unsigned)time(NULL));
    menu();
    return 0;
}