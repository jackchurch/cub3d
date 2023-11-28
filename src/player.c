#include <stdbool.h>
#include <fcntl.h>
#include <sys/time.h>
#include <float.h>
#include "../inc/cub3d.h"

void setup(t_player *player)
{
	player->x = WINDOW_WIDTH / 2;
	player->y = WINDOW_HEIGHT / 2;
	player->width = 1;
	player->height = 1;
	player->turnDirection = 0;
	player->walkDirection = 0;
	player->rotationAngle = HALF_PI;
	player->walkSpeed = 0.5;
	player->turnSpeed = ONE_PI / 180 * player->walkSpeed;
}

void	movePlayer(t_game *game, t_player *player)
{
	if (!game)
		return ;
	player->rotationAngle += player->turnDirection * player->turnSpeed;
	float moveStep = player->walkDirection * player->walkSpeed;
	float newPlayerX = player->x + cos(player->rotationAngle) * moveStep;
	float newPlayerY = player->y + sin(player->rotationAngle) * moveStep;


	if (!mapHasWallAt(newPlayerX, newPlayerY))
	{
		player->x = newPlayerX;
		player->y = newPlayerY;
	}
}

void	renderPlayer(t_game *game, t_player *player)
{
	t_rectangle playerRect = {
		player->x * MINIMAP_SCALE,
		player->y * MINIMAP_SCALE,
		player->width * MINIMAP_SCALE,
		player->height * MINIMAP_SCALE,
		0x00E0B0FF
	};
	drawRect(game, &playerRect);

	t_line playerLine = {
		player->x * MINIMAP_SCALE,
		player->y * MINIMAP_SCALE,
		(player->x + cos(player->rotationAngle) * 40) * MINIMAP_SCALE,
		(player->y + sin(player->rotationAngle) * 40) * MINIMAP_SCALE,
		0x00E0B0FF
	};
	drawLine(game, &playerLine);
}