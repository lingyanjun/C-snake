#include "Game.c"
int main()
{
	// 蛇的初始状态
	Game game = { 0 };
	game.state = NORMAL;
	game.dir = RIGHT;
	printf("\033[?25l");
	// 游戏地图
	Draw_Map();
	// 蛇的位置
	Init_Snake(&game);
	// 食物位置
	Init_Food(&game);
	printf("\033[%d;1H", HIGH + 1);
    printf("WASD移动");
    fflush(stdout);
	// 运行
	while (game.state == NORMAL)
	{
		if (kbhit())
		{
			WASD(&game);
		}
		GameCheck(&game);
		printf("\033[%d;1H", HIGH + 4);
        fflush(stdout);
		usleep(80000);
	}
}