# Gluttonous-Snake
这是一个使用c语言写的贪吃蛇游戏
# 🧑‍💻 游戏方式
键盘方向：
- w-代表向上走
- a-向左走
- d-向右走
- s-向下走
- 按下"x"键退出游戏
# 实现思路
1. 定义数据结构：通过结构体定义了蛇的身体坐标数组和长度，以及食物的坐标
```c
// 定义蛇的数据结构
struct Snake {
    struct Coordinate body[MAX_LENGTH];  // 蛇身体的坐标数组
    int length;                          // 蛇的长度
    int direction;                       // 蛇的移动方向（0：上，1：下，2：左，3：右）
};

```
2.初始化游戏：在initialize()函数中，设置了蛇的初始位置和长度，以及食物的随机位置。
```
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
```
3. 绘制游戏界面：通过在控制台输出字符来表示游戏界面。使用嵌套的循环遍历游戏区域的每个位置，并根据蛇的身体坐标和食物的位置来输出相应的字符。
4. 处理用户输入：使用_kbhit()函数检查是否有键盘输入，如果有则使用_getch()函数获取输入的字符。根据不同的输入字符来改变蛇的移动方向，或退出游戏。
```
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

```
5. 更新游戏状态：在update()函数中，首先移动蛇的身体，通过循环将每个身体部分的坐标更新为上一个身体部分的坐标。然后根据蛇的移动方向，更新蛇头的坐标。接着检查蛇是否吃到食物，如果蛇头的坐标与食物坐标相同，则增加蛇的长度、生成新的食物位置，并增加得分。最后，检查蛇是否撞墙或撞到自己，如果是则游戏结束。
```
// 移动蛇的身体
    for (int i = snake.length - 1; i > 0; i--) {
        snake.body[i].x = snake.body[i - 1].x;
        snake.body[i].y = snake.body[i - 1].y;
    }
```
```
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
```
```
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
```

6. 主循环：在main()函数中，使用一个无限循环来不断执行以下步骤：绘制游戏界面、处理用户输入、更新游戏状态，并通过Sleep()函数控制游戏的速度。
```
 while (1) {
        draw();
        handleInput();
        update();
        Sleep(100);  // 控制游戏速度，单位为毫秒
    }
```





