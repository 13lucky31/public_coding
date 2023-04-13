#include <stdio.h>

void print_map(int score1, int score2, int pos1, int pos2, int ball_x, int ball_y);
int collision(int direction);
int side(int direction);
int player1_move(char button);
int player2_move(char button);
void congratulations(int score1, int score2);
int main() {
    int score1 = 0, score2 = 0, pos1 = 12, pos2 = 12, ball_x = 39, ball_y = 12, direction = 1;
    while ((score1 < 21) && (score2 < 21)) {
        char button;
        print_map(score1, score2, pos1, pos2, ball_x, ball_y);
        scanf("%c", &button);
        if ((button == 'a') || (button == 'z') || (button == 'k') || (button == 'm') || (button == ' ')) {
            pos1 =
                (((player1_move(button) == -1) && (pos1 > 1)) || ((player1_move(button) == 1) && (pos1 < 23)))
                    ? pos1 + player1_move(button)
                    : pos1;
            pos2 =
                (((player2_move(button) == -1) && (pos2 > 1)) || ((player2_move(button) == 1) && (pos2 < 23)))
                    ? pos2 + player2_move(button)
                    : pos2;
            switch (direction) {
                case 1:
                    ball_x -= 1;
                    ball_y -= 1;
                    break;
                case 2:
                    ball_x += 1;
                    ball_y -= 1;
                    break;
                case 3:
                    ball_x += 1;
                    ball_y += 1;
                    break;
                case 4:
                    ball_x -= 1;
                    ball_y += 1;
                    break;
            }
            if (ball_y == 0) direction = collision(direction);
            if (ball_y == 24) direction = collision(direction);

            if (ball_x == 0) {
                if ((ball_y < pos1 - 1) || (ball_y > pos1 + 1)) score2++;
                direction = side(direction);
            }
            if (ball_x == 79) {
                if ((ball_y < pos2 - 1) || (ball_y > pos2 + 1)) score1++;
                direction = side(direction);
            }
        }
    }
    congratulations(score1, score2);
    return 0;
}
void print_map(int score1, int score2, int pos1, int pos2, int ball_x, int ball_y) {
    printf("\33[0d\33[2J");
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 80; j++) {
            if ((j == 0) && (i >= pos1 - 1) && (i <= pos1 + 1))
                printf("|");
            else if ((i == 0) && (j == 38))
                printf("%d", score1);
            else if ((i == 0) && (j == 40))
                printf("%d", score2);
            else if ((j == 79) && (i >= pos2 - 1) && (i <= pos2 + 1))
                printf("|");
            else if ((i == ball_y) && (j == ball_x))
                printf("*");
            else if (j == 39)
                printf("|");
            else
                printf(" ");
        }
        printf("\n");
    }
}
int collision(int direction) {
    if (direction == 1)
        return 4;
    else if (direction == 2)
        return 3;
    else if (direction == 4)
        return 1;
    else
        return 2;
}
int side(int direction) {
    if (direction == 1)
        return 2;
    else if (direction == 2)
        return 1;
    else if (direction == 3)
        return 4;
    else
        return 3;
}
int player1_move(char button) {
    if (button == 'a')
        return -1;
    else if (button == 'z')
        return 1;
    else
        return 0;
}
int player2_move(char button) {
    if (button == 'k')
        return -1;
    else if (button == 'm')
        return 1;
    else
        return 0;
}

void congratulations(int score1, int score2) {
    printf("\33[0d\33[2J");
    for (int i = 0; i < 12; i++) printf("\n");
    for (int i = 0; i < 21; i++) printf(" ");
    if (score1 > score2)
        printf("Congratulations to Player 1! You win!\n");
    else
        printf("Congratulations to Player 2! You win!\n");
    for (int i = 0; i < 12; i++) printf("\n");
}
