#include <stdbool.h>
#include <fcntl.h>
#include <sys/time.h>
#include "../inc/cub3d.h"

const int map[MAP_NUM_ROWS][MAP_NUM_COLS] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
	{1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1},
	{1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

struct Player {
	float x;
	float y;
	float width;
	float height;
	int turnDirection;
	int walkDirection;
	float rotationAngle;
	float walkSpeed;
	float turnSpeed;
} player;

int	player_x, player_y;

void	drawRect(t_game *game, t_rectangle *rect)
{
	int	i;
	int	j;
	
	i = rect->x;
	while (i <= (rect->x + rect->width))
	{
		j = rect->y;
		while (j <= (rect->y + rect->height))
		{
			mlx_pixel_put(game->mlx, game->win, i, j, rect->color);
			j++;
		}
		i++;
	}
	return ;
}

void drawLine(t_game *game, t_line *line) {
    
	int x0 = line->x0;
	int y0 = line->y0;
	int x1 = line->x1;
	int y1 = line->y1;
	int color = line->color;
	int deltaX = (x1 - x0);
    int deltaY = (y1 - y0);

    int longestSideLength = (abs(deltaX) >= abs(deltaY)) ? abs(deltaX) : abs(deltaY);

    float xIncrement = deltaX / (float)longestSideLength;
    float yIncrement = deltaY / (float)longestSideLength;

    float currentX = x0;
    float currentY = y0;

    for (int i = 0; i < longestSideLength; i++) {
		mlx_pixel_put(game->mlx, game->win, round(currentX), round(currentY), color);
        currentX += xIncrement;
        currentY += yIncrement;
    }
}

void	safe_exit(t_game *game)
{
	if (game->win)
		free(game->win);
	if (game->mlx)
		free(game->mlx);
	if (game)
		free(game);
	exit(0);
}

void	renderPlayer(t_game *game)
{
	t_rectangle playerRect = {
		player.x * MINIMAP_SCALE,
		player.y * MINIMAP_SCALE,
		player.width * MINIMAP_SCALE,
		player.height * MINIMAP_SCALE,
		0x00E0B0FF
	};
	drawRect(game, &playerRect);

	t_line playerLine = {
		player.x * MINIMAP_SCALE,
		player.y * MINIMAP_SCALE,
		(player.x + cos(player.rotationAngle) * 40) * MINIMAP_SCALE,
		(player.y + sin(player.rotationAngle) * 40) * MINIMAP_SCALE,
		0x00E0B0FF
	};
	drawLine(game, &playerLine);
}

void	movePlayer(t_game *game)
{
	if (!game)
		return ;
	player.rotationAngle += player.turnDirection * player.turnSpeed;
	float moveStep = player.walkDirection * player.walkSpeed;
	float newPlayerX = player.x + cos(player.rotationAngle) * moveStep;
	float newPlayerY = player.y + sin(player.rotationAngle) * moveStep;

	// Wall collision here

	player.x = newPlayerX;
	player.y = newPlayerY;
}


void renderMap(t_game *game)
{
	for (int i = 0; i < MAP_NUM_ROWS; i++)
	{
		for (int j = 0; j < MAP_NUM_COLS; j++)
		{
			int tileX = j * TILE_SIZE; 
			int tileY = i * TILE_SIZE;
			int tileColor = (map[i][j] != 0 ? 0x000000FF : 0x00FFFFFF);
			t_rectangle mapTileRect = {
				tileX * MINIMAP_SCALE, 
				tileY * MINIMAP_SCALE, 
				TILE_SIZE * MINIMAP_SCALE, 
				TILE_SIZE * MINIMAP_SCALE, 
				tileColor
			};
			drawRect(game, &mapTileRect);
		}
	}
}

int	key_hook(int keycode, t_game *game)
{
	if (keycode == LEFT)
		player.turnDirection = -1;
	else if (keycode == RIGHT)
		player.turnDirection = 1;
	else if (keycode == UP)
		player.walkDirection = 1;
	else if (keycode == DOWN)
		player.walkDirection = -1;
	else if (keycode == ESC)
		safe_exit(game);
	// renderPlayer(game);
	movePlayer(game);
	renderMap(game);
	renderPlayer(game);
	// render(game);
	return (0);
}

int	key_release(int keycode)
{
	if (keycode == LEFT)
		player.turnDirection = 0;
	else if (keycode == RIGHT)
		player.turnDirection = 0;
	else if (keycode == UP)
		player.walkDirection = 0;
	else if (keycode == DOWN)
		player.walkDirection = 0;
	return (0);
}

bool	init_window(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		safe_exit(game);
	game->win = mlx_new_window(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Legally Distinct Slï'mę Game");
	if (!game->win)
		safe_exit(game);
	mlx_hook(game->win, 2, 0, key_hook, game);
	mlx_hook(game->win, 3, 0, key_release, game);

	return (true);
}

void update(t_game *game)
{
	// Add FPS here if have time. 
	movePlayer(game);
}

void setup()
{
	player.x = WINDOW_WIDTH / 2;
	player.y = WINDOW_HEIGHT / 2;
	player.width = 1;
	player.height = 1;
	player.turnDirection = 0;
	player.walkDirection = 0;
	player.rotationAngle = HALF_PI;
	player.walkSpeed = 5;
	player.turnSpeed = ONE_PI / 180 * player.walkSpeed;
}

void	render(t_game *game)
{

	renderMap(game);
	renderPlayer(game);
	// render_rays()

	t_rectangle rect = {
		.x = player_x,
		.y = player_y,
		.width = 20,
		.height = 20,
		.color = 0x00FF0000
	};
	drawRect(game, &rect);

}

int	main(void)
{
	t_game *game;

	game = (t_game *)ft_calloc(1, sizeof(t_game));
	init_window(game);
	setup();

	// process_input(); // See keyhooks
	update(game); // Add FPS if have time. 
	render(game);
	mlx_loop(game->mlx);
	return (0);
}
