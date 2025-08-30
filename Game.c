#include "Game.h"
void Draw_Map()
{
	for (int y = 0; y < HIGH; y++)
	{
		for (int x = 0; x < WIEGH; x++)
		{
			if (x == 0 || y == 0 || x == WIEGH - 1 || y == HIGH - 1)
			{
				printf("#");
			}
			else
			{
				printf(" ");
			}
		}
		printf("\n");
	}
}

void Init_Snake(PGame game)
{
	PSnake snake = NULL;
	PSnake Slength = NULL;
	Slength = malloc(sizeof(Snake));
	srand(time(NULL));
	Slength->length = rand() % 5 + 2;
	for (int i = 0; i < Slength->length; i++)
	{
		snake = malloc(sizeof(Snake));
		if (!snake)
			return;
		snake->x = WIEGH / 2 + i;
		snake->y = HIGH / 2;
		snake->next = NULL;
		if (game->_snake == NULL)
		{
			game->_snake = snake;
		}
		else
		{
			snake->next = game->_snake;
			game->_snake = snake;
		}
		PSnake drawSnake = game->_snake;
		while (drawSnake)
		{
			printf("\033[%d;%dH", drawSnake->y, drawSnake->x);
			printf("@");
			drawSnake = drawSnake->next;
		}
	}
	free(Slength);
	Slength = NULL;
}

void Init_Food(PGame game)
{
	bool scussess = false;
	while (!scussess)
	{
		game->food.x = (rand() % WIEGH-2) + 1;
		game->food.y = (rand() % HIGH-2) + 1;
		PSnake check = game->_snake;
		scussess = true;
		while (check)
		{
			if (game->food.x == check->x && game->food.y == check->y)
			{
				scussess = 0;
				break;
			}
			check = check->next;
		}
	}
	printf("\033[%d;%dH", game->food.y, game->food.x);
	printf("@");
}

void WASD(PGame game)
{
	char ch = getchar();
	switch (ch)
	{
	case 'w':
		if (game->dir != DOWN)
			game->dir = UP;
		break;
	case 'd':
		if (game->dir != LEFT)
			game->dir = RIGHT;
		break;
	case 's':
		if (game->dir != UP)
			game->dir = DOWN;
		break;
	case 'a':
		if (game->dir != RIGHT)
			game->dir = LEFT;
		break;
	}
}



void GameCheck(PGame game)
{
	int nextX = 0;
	int nextY = 0;
	switch (game->dir)
	{
	case UP:
		nextX = (game->_snake->x);
		nextY = (game->_snake->y) - 1;
		break;
	case RIGHT:
		nextX = (game->_snake->x) + 1;
		nextY = (game->_snake->y);
		break;
	case DOWN:
		nextX = (game->_snake->x);
		nextY = (game->_snake->y) + 1;
		break;
	case LEFT:
		nextX = (game->_snake->x) - 1;
		nextY = (game->_snake->y);
		break;
	}
	if (nextX == game->food.x && nextY == game->food.y)
	{
		PSnake food = malloc(sizeof(Snake));
		food->x = nextX;
		food->y = nextY;
		food->next = game->_snake;
		game->_snake = food;
		printf("\033[%d;%dH", nextY, nextX);
		printf("@");
		Init_Food(game);
	}
	if (nextX == 1 || nextX == WIEGH || nextY == 1 || nextY == HIGH)
	{
		game->state = DEATH_WALL;
		printf("\033[%d;%dH", HIGH / 2, WIEGH / 2 - 5);
		printf("彩笔，别玩了");
		fflush(stdout);
		while (game->_snake)
		{
			PSnake temp = game->_snake;
			game->_snake = game->_snake->next;
			free(temp);
		}
		game->_snake = NULL;
	}
	PSnake self = game->_snake->next;
	while (self)
	{
		if (self->x == nextX && self->y == nextY)
		{
			game->state = DEATH_SELF;
			printf("\033[%d;%dH", HIGH / 2, WIEGH / 2 - 5);
			printf("彩笔，别玩了");
			fflush(stdout);
			 while (game->_snake)
			{
				PSnake temp = game->_snake;
				game->_snake = game->_snake->next;
				free(temp);
			}
			game->_snake = NULL;
		}
		self = self->next;
	}
	PSnake newHead = malloc(sizeof(Snake));
	newHead->x = nextX;
	newHead->y = nextY;
	newHead->next = game->_snake;
	game->_snake = newHead;
	PSnake end = game->_snake;
	while (end->next->next)
	{
		end = end->next;
	}
	printf("\033[%d;%dH", end->next->y, end->next->x);
	printf(" ");
	free(end->next);
	end->next = NULL;
	printf("\033[%d;%dH", newHead->y, newHead->x);
	printf("@");
	fflush(stdout);

}