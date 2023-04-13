#include <ncurses.h>
#include <stdio.h>
#include <unistd.h>
#define X 25
#define Y 80

int input(int arr[X][Y], int initial[X][Y], int x, int y);
void output(int arr[X][Y], int x, int y);
int any_alive(int arr[X][Y], int x, int y);
int not_the_same(int map[X][Y], int initial[X][Y], int x, int y);
int get_neighbors_count(int arr[X][Y], int x1, int y1, int x, int y);
int main() {
    int map[X][Y], temp[X][Y], initial[X][Y], delay = 200000, is_initial = 1, is_same = 1;
    for (int i = 0; i < X; i++)
        for (int j = 0; j < Y; j++) temp[i][j] = 0;
    input(map, initial, X, Y);
    initscr();
    halfdelay(1);
    noecho();
    while ((any_alive(map, X, Y) == 1) && (is_same == 1) && (is_initial == 1)) {
        char button;
        output(map, X, Y);
        for (int i = 0; i < X; i++)
            for (int j = 0; j < Y; j++) {
                int count = get_neighbors_count(map, i, j, X, Y);
                if (map[i][j] == 0) {
                    if (count == 3)
                        temp[i][j] = 1;
                    else
                        temp[i][j] = 0;
                } else {
                    if ((count < 2) || (count > 3))
                        temp[i][j] = 0;
                    else
                        temp[i][j] = 1;
                }
            }
        is_same = not_the_same(map, temp, X, Y);
        for (int i = 0; i < X; i++)
            for (int j = 0; j < Y; j++) map[i][j] = temp[i][j];
        is_initial = not_the_same(map, initial, X, Y);
        button = getch();
        if (button == 'a')
            if (delay > 1) delay -= 100000;
        if (button == 'z')
            if (delay < 1000000) delay += 100000;
        usleep(delay);
    }
    endwin();
    return 0;
}
int input(int arr[X][Y], int initial[X][Y], int x, int y) {
    for (int i = 0; i < x; i++)
        for (int j = 0; j < y; j++) {
            scanf("%d", &arr[i][j]);
            initial[i][j] = arr[i][j];
        }
    return 0;
}
void output(int arr[X][Y], int x, int y) {
    clear();
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            if (arr[i][j] == 0)
                printw(" ");
            else
                printw("*");
        }
        printw("\n");
    }
}
int any_alive(int arr[X][Y], int x, int y) {
    for (int i = 0; i < x; i++)
        for (int j = 0; j < y; j++)
            if (arr[i][j] == 1) return 1;
    return 0;
}
int not_the_same(int map[X][Y], int initial[X][Y], int x, int y) {
    for (int i = 0; i < x; i++)
        for (int j = 0; j < y; j++)
            if (map[i][j] != initial[i][j]) return 1;
    return 0;
}
int get_neighbors_count(int arr[X][Y], int x1, int y1, int x, int y) {
    int count = 0;
    int x_top, x_bot, y_left, y_right;
    if (x1 == 0)
        x_top = x - 1;
    else
        x_top = x1 - 1;
    if (x1 == x - 1)
        x_bot = 0;
    else
        x_bot = x1 + 1;
    if (y1 == 0)
        y_left = y - 1;
    else
        y_left = y1 - 1;
    if (y1 == y - 1)
        y_right = 0;
    else
        y_right = y1 + 1;
    count += arr[x_top][y_left];
    count += arr[x_top][y1];
    count += arr[x_top][y_right];
    count += arr[x1][y_left];
    count += arr[x1][y_right];
    count += arr[x_bot][y_left];
    count += arr[x_bot][y1];
    count += arr[x_bot][y_right];
    return count;
}
