#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>

// ������Ϸ�����С
#define WIDTH 20
#define HEIGHT 20

// �����ߵ���󳤶�
#define MAX_LENGTH 100

// �����ߺ�ʳ�������ṹ��
struct Coordinate {
    int x;
    int y;
};

// �����ߵ����ݽṹ
struct Snake {
    struct Coordinate body[MAX_LENGTH];  // ���������������
    int length;                          // �ߵĳ���
    int direction;                       // �ߵ��ƶ�����0���ϣ�1���£�2����3���ң�
};

// ȫ�ֱ���
int score = 0;                // �÷�
struct Snake snake;           // �ߵ�ʵ��
struct Coordinate food;       // ʳ�������

// ���ÿ���̨���λ��
void setCursorPosition(int x, int y) {
    COORD position;
    position.X = x;
    position.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

// ���ؿ���̨���
void hideCursor() {
    CONSOLE_CURSOR_INFO cursor_info = {100, FALSE};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

// ��ʼ����Ϸ
void initialize() {
    // ��ʼ���ߵĳ�ʼλ�úͳ���
    snake.length = 3;
    snake.body[0].x = WIDTH / 2;
    snake.body[0].y = HEIGHT / 2;
    snake.body[1].x = WIDTH / 2 - 1;
    snake.body[1].y = HEIGHT / 2;
    snake.body[2].x = WIDTH / 2 - 2;
    snake.body[2].y = HEIGHT / 2;

    // ��ʼ���ߵ��ƶ�����
    snake.direction = 3;

    // ��ʼ��ʳ���λ��
    food.x = rand() % WIDTH;
    food.y = rand() % HEIGHT;

    // ��ʼ���÷�
    score = 0;
}

// ������Ϸ����
void draw() {
    system("cls");  // ����

    // �����ϱ߽�
    for (int i = 0; i < WIDTH + 2; i++) {
        printf("#");
    }
    printf("\n");

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (j == 0) {
                printf("#");  // ������߽�
            }

            // �����������ʳ��
            if (i == snake.body[0].y && j == snake.body[0].x) {
                printf("O");  // ��ͷ
            } else {
                int isBodyPart = 0;
                for (int k = 1; k < snake.length; k++) {
                    if (i == snake.body[k].y && j == snake.body[k].x) {
                        printf("o");  // ������
                        isBodyPart = 1;
                        break;
                    }
                }
                if (!isBodyPart && i == food.y && j == food.x) {
                    printf("@");  // ʳ��
                } else if (!isBodyPart) {
                    printf(" ");  // �հ�
                }
            }

            if (j == WIDTH - 1) {
                printf("#");  // �����ұ߽�
            }
        }
        printf("\n");
    }

    // �����±߽�
    for (int i = 0; i < WIDTH + 2; i++) {
        printf("#");
    }
    printf("\n");

    // ���Ƶ÷�
    printf("Score: %d\n", score);
}

// �����û�����
void handleInput() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'w':
                if (snake.direction != 1)
                    snake.direction = 0;  // ��
                break;
            case 's':
                if (snake.direction != 0)
                    snake.direction = 1;  // ��
                break;
            case 'a':
                if (snake.direction != 3)
                    snake.direction = 2;  //��
                break;
            case 'd':
                if (snake.direction != 2)
                    snake.direction = 3;  // ��
                break;
            case 'x':
                exit(0);  // ����"x"���˳���Ϸ
                break;
        }
    }
}

// ������Ϸ״̬
void update() {
    // �ƶ��ߵ�����
    for (int i = snake.length - 1; i > 0; i--) {
        snake.body[i].x = snake.body[i - 1].x;
        snake.body[i].y = snake.body[i - 1].y;
    }

    // ���ݷ����ƶ���ͷ
    switch (snake.direction) {
        case 0:
            snake.body[0].y--;
            break;
        case 1:
            snake.body[0].y++;
            break;
        case 2:
            snake.body[0].x--;
            break;
        case 3:
            snake.body[0].x++;
            break;
    }

    // ������Ƿ�Ե�ʳ��
    if (snake.body[0].x == food.x && snake.body[0].y == food.y) {
        // �����ߵĳ���
        snake.length++;

        // �����µ�ʳ��λ��
        food.x = rand() % WIDTH;
        food.y = rand() % HEIGHT;

        // ���ӵ÷�
        score++;
    }

    // ������Ƿ�ײǽ
    if (snake.body[0].x < 0 || snake.body[0].x >= WIDTH || snake.body[0].y < 0 || snake.body[0].y >= HEIGHT) {
        printf("Game Over!\n");
        exit(0);
    }

    // ������Ƿ�ײ���Լ�
    for (int i = 1; i < snake.length; i++) {
        if (snake.body[0].x == snake.body[i].x && snake.body[0].y == snake.body[i].y) {
            printf("Game Over!\n");
            exit(0);
        }
    }
}

int main() {
    hideCursor();
    initialize();

    while (1) {
        draw();
        handleInput();
        update();
        Sleep(100);  // ������Ϸ�ٶȣ���λΪ����
    }

    return 0;
}
