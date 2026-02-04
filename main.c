#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

#define W 31
#define H 21

char maze[H][W];
int px = 1, py = 1;

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
}

void play_game() {
    px = py = 1;
    generate_maze();

    while (1) {
        draw_maze();
        int ch = _getch();

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
            printf("YOU WIN!\nPress any key to return to menu...\n");
            _getch();
            break;
        }
    }
}

void menu() {
    int choice = 0;
    const char *items[] = {
        "1. Start Game",
        "2. Leaders",
        "3. About",
        "4. Exit"
    };

    while (1) {
        clear_screen();
        printf("=== MAZE GAME ===\n\n");
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
            if (choice == 0) play_game();
            if (choice == 1) {
                clear_screen();
                printf("Leaders are not implemented yet.\n");
                _getch();
            }
            if (choice == 2) {
                clear_screen();
                printf("Maze Game\n");
                printf("Language: C\n");
                printf("Controls: Arrow keys\n");
                printf("Goal: Reach the exit (X)\n");
                _getch();
            }
            if (choice == 3) break;
        }
    }
}

int main() {
    srand((unsigned)time(NULL));
    menu();
    return 0;
}
