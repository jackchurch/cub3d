#include "../inc/cub3d.h"


void	renderPlayer(t_game *game)
{
	t_rectangle playerRect = {
		t_player.x * MINIMAP_SCALE,
		t_player.y * MINIMAP_SCALE,
		t_player.width * MINIMAP_SCALE,
		t_player.height * MINIMAP_SCALE,
		0x00E0B0FF
	};
	drawRect(game, &playerRect);

	t_line playerLine = {
		t_player.x * MINIMAP_SCALE,
		t_player.y * MINIMAP_SCALE,
		(t_player.x + cos(t_player.rotationAngle) * 40) * MINIMAP_SCALE,
		(t_player.y + sin(t_player.rotationAngle) * 40) * MINIMAP_SCALE,
		0x00E0B0FF
	};
	drawLine(game, &playerLine);
}




void drawCeling(t_game *game)
{
	t_rectangle celing = {
		.x = 0,
		.y = 0,
		.width = WINDOW_WIDTH,
		.height = WINDOW_HEIGHT / 2,
		.color = 0x00FAF0E6
	};
	drawRect(game, &celing);

	t_rectangle floor = {
		.x = 0,
		.y = WINDOW_HEIGHT / 2,
		.width = WINDOW_WIDTH,
		.height = WINDOW_HEIGHT / 2,
		.color = 0x008B9E8A
	};
	drawRect(game, &floor);

}

