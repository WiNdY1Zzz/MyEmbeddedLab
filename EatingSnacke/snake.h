#ifndef SNAKE_H

#define SNAKE_H
#define MAP_LEN 25
#define MAP_WID 25
#define MAX_SNAKE_LEN 30

typedef struct
{
    int x;
    int y;
}Point; //坐标点

typedef struct
{
    int length;     //蛇身长度
    Point body[MAX_SNAKE_LEN]; //蛇身坐标数组(最大长度暂定30)
                               //body[0]蛇头 body[length-1]蛇尾
    int direction;  //当前方向(0上 1下 2左 3右)
}Snake;

typedef struct
{
    int map[MAP_WID][MAP_LEN]; //0空地 1墙 2食物 3蛇身
    Snake snake;
    Point food;
    int score;
}Game;

#endif