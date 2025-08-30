#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>
#include <stdbool.h>
#include <conio.h>
/**
 * @brief  用于贪吃蛇在手机上游玩
 * @author 凌烟
 * @date   2025-07-22
 * @license MIT开源协议
 */
// 游戏地图数据
#define HIGH 40
#define WIEGH 60

// 蛇的方向
enum dir
{
	UP = 0,
	RIGHT,
	DOWN,
	LEFT
};

// 蛇的状态
enum state
{
	NORMAL = 1,
	DEATH_SELF,
	DEATH_WALL
};

// 蛇的结构
typedef struct _Snake
{
	int x;
	int y;
	size_t length;
	struct _Snake *next;
} Snake, *PSnake;

// 食物结构
typedef struct _Food
{
	int x;
	int y;
} Food, *PFood;

// 游戏结构
typedef struct _Game
{
	PSnake _snake;
	Food food;
	int state;
	int dir;
} Game, *PGame;

// 绘制地图
void Draw_Map();

// 初始化蛇
void Init_Snake(PGame game);

// 初始化食物
void Init_Food(PGame game);

// 操作控制
void WASD(PGame game);

// 运行检测
void GameCheck(PGame game);