#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "snake.h"

void InitGame(Game *game)
{
    srand((unsigned)time(NULL));
    // //1. 清空地图（全部设为0）
    // for(int i = 0;i < MAP_LEN;i++)
    // {
    //     for(int j = 0;j < MAP_WID;j++)
    //     {
    //         game->map[i][j] = 0;
    //     }
    // }

    // //2. 设置边界（最外围一圈设置为1）
    // for(int i = 0;i < MAP_WID;i++)
    // {
    //     game->map[0][i] = 1;
    // }
    // for(int i = 0;i < MAP_LEN;i++)
    // {
    //     game->map[i][0] = 1;
    // }
    // for(int i = 0;i < MAP_LEN;i++)
    // {
    //     game->map[i][MAP_WID - 1] = 1;
    // }
    // for(int i = 0;i < MAP_WID;i++)
    // {
    //     game->map[MAP_LEN - 1][i] = 1;
    // }

    // 1. 优化版 一次性设置四周边界以及非边界
    for (int i = 0; i < MAP_LEN; i++)
    {
        for (int j = 0; j < MAP_WID; j++)
        {
            if (i == 0 || i == MAP_LEN - 1 || j == 0 || j == MAP_WID - 1)
            {
                game->map[i][j] = 1;
            }
            else
            {
                game->map[i][j] = 0;
            }
        }
    }

    // 3. 初始化蛇
    game->snake.length = 3;
    game->snake.direction = 0;

    game->snake.body[0].x = 12;
    game->snake.body[0].y = 12;

    game->snake.body[1].x = 12;
    game->snake.body[1].y = 13;

    game->snake.body[2].x = 12;
    game->snake.body[2].y = 14;

    // 4.生成第一个食物
}

void SpawnFood(Game *game)
{

    int x, y;
    while (1)
    {
        x = rand() % (MAP_LEN - 2) + 1;
        y = rand() % (MAP_WID - 2) + 1;
        if (game->map[y][x] == 0)
        {
            game->food.x = x;
            game->food.y = y;
            game->map[y][x] = 2;
            break;
        }
    }
}

void DrawMap(const Game *game)
{
    for(int y = 0;y < MAP_WID;y++)
    {
        for(int x = 0;x < MAP_LEN;x++)
        {
            switch(game->map[y][x])
            {
                case 0: printf("  "); break;
                case 1: printf("# "); break;
                case 2: printf("*"); break;
                case 3: printf("O"); break;
                default: printf("?"); break;
            }
        }
        printf("\n");
    }
}

int main(int argc, char *argv[])
{
    Game game;
    InitGame(&game);
    DrawMap(&game);

    return 0;
}