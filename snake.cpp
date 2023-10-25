#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>

// 定义游戏区域大小
#define WIDTH 20
#define HEIGHT 20

// 定义蛇的最大长度
#define MAX_LENGTH 100

// 定义蛇和食物的坐标结构体
struct Coordinate {
    int x;
    int y;
};

// 定义蛇的数据结构
struct Snake {
    struct Coordinate body[MAX_LENGTH];  // 蛇身体的坐标数组
    int length;                          // 蛇的长度
    int direction;                       // 蛇的移动方向（0：上，1：下，2：左，3：右）
};

// 全局变量
int score = 0;                // 得分
struct Snake snake;           // 蛇的实例
struct Coordinate food;       // 食物的坐标

// 设置控制台光标位置
void setCursorPosition(int x, int y) {
    COORD position;
    position.X = x;
    position.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

// 隐藏控制台光标
void hideCursor() {
    CONSOLE_CURSOR_INFO cursor_info = {100, FALSE};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

// 初始化游戏
void initialize() {
    // 初始化蛇的初始位置和长度
    snake.length = 3;
    snake.body[0].x = WIDTH / 2;
    snake.body[0].y = HEIGHT / 2;
    snake.body[1].x = WIDTH / 2 - 1;
    snake.body[1].y = HEIGHT / 2;
    snake.body[2].x = WIDTH / 2 - 2;
    snake.body[2].y = HEIGHT / 2;

    // 初始化蛇的移动方向
    snake.direction = 3;

    // 初始化食物的位置
    food.x = rand() % WIDTH;
    food.y = rand() % HEIGHT;

    // 初始化得分
    score = 0;
}

// 绘制游戏界面
void draw() {
    system("cls");  // 清屏

    // 绘制上边界
    for (int i = 0; i < WIDTH + 2; i++) {
        printf("#");
    }
    printf("\n");

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (j == 0) {
                printf("#");  // 绘制左边界
            }

            // 绘制蛇身体或食物
            if (i == snake.body[0].y && j == snake.body[0].x) {
                printf("O");  // 蛇头
            } else {
                int isBodyPart = 0;
                for (int k = 1; k < snake.length; k++) {
                    if (i == snake.body[k].y && j == snake.body[k].x) {
                        printf("o");  // 蛇身体
                        isBodyPart = 1;
                        break;
                    }
                }
                if (!isBodyPart && i == food.y && j == food.x) {
                    printf("@");  // 食物
                } else if (!isBodyPart) {
                    printf(" ");  // 空白
                }
            }

            if (j == WIDTH - 1) {
                printf("#");  // 绘制右边界
            }
        }
        printf("\n");
    }

    // 绘制下边界
    for (int i = 0; i < WIDTH + 2; i++) {
        printf("#");
    }
    printf("\n");

    // 绘制得分
    printf("Score: %d\n", score);
}

// 处理用户输入
void handleInput() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'w':
                if (snake.direction != 1)
                    snake.direction = 0;  // 上
                break;
            case 's':
                if (snake.direction != 0)
                    snake.direction = 1;  // 下
                break;
            case 'a':
                if (snake.direction != 3)
                    snake.direction = 2;  //左
                break;
            case 'd':
                if (snake.direction != 2)
                    snake.direction = 3;  // 右
                break;
            case 'x':
                exit(0);  // 按下"x"键退出游戏
                break;
        }
    }
}

// 更新游戏状态
void update() {
    // 移动蛇的身体
    for (int i = snake.length - 1; i > 0; i--) {
        snake.body[i].x = snake.body[i - 1].x;
        snake.body[i].y = snake.body[i - 1].y;
    }

    // 根据方向移动蛇头
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

    // 检查蛇是否吃到食物
    if (snake.body[0].x == food.x && snake.body[0].y == food.y) {
        // 增加蛇的长度
        snake.length++;

        // 生成新的食物位置
        food.x = rand() % WIDTH;
        food.y = rand() % HEIGHT;

        // 增加得分
        score++;
    }

    // 检查蛇是否撞墙
    if (snake.body[0].x < 0 || snake.body[0].x >= WIDTH || snake.body[0].y < 0 || snake.body[0].y >= HEIGHT) {
        printf("Game Over!\n");
        exit(0);
    }

    // 检查蛇是否撞到自己
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
        Sleep(100);  // 控制游戏速度，单位为毫秒
    }

    return 0;
}
