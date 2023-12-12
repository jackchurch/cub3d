#include "../inc/render.h"
#include "../inc/draw.h"
#include "../inc/constance.h"
#include "../inc/cub3d.h"
#include "../inc/ray.h"

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

void	generate3DProjection(t_game *game)
{
	drawCeling(game);
	for (int i = 0; i < NUM_RAYS; i++)
	{
		float correctedDistance = rays[i].distance * cos(rays[i].rayAngle - t_player.rotationAngle);
		float distanceProjPlane = (WINDOW_WIDTH / 2) / tan(FOV_ANGLE / 2);
		float projectedWallHeight = (TILE_SIZE / correctedDistance) * distanceProjPlane;
		int wallStripHeight = (int)projectedWallHeight;

		int wallTopPixel = (WINDOW_HEIGHT / 2) - (wallStripHeight / 2);
		wallTopPixel = wallTopPixel < 0 ? 0 : wallTopPixel;


		int wallBottomPixel = (WINDOW_HEIGHT / 2) + (wallStripHeight / 2);
		wallBottomPixel = wallTopPixel > WINDOW_HEIGHT ? WINDOW_HEIGHT : wallBottomPixel;

		int _color;
		if (rays[i].isRayFacingDown && !rays[i].wasHitVertical)
			_color = 0x0000FFFF;
		if (rays[i].isRayFacingUp && !rays[i].wasHitVertical)
			_color = 0x00FFFF00;
		if (rays[i].isRayFacingLeft && rays[i].wasHitVertical)
			_color = 0x00FF00FF;
		if (rays[i].isRayFacingRight && rays[i].wasHitVertical)
			_color = 0x0000FF00;
		t_rectangle rect = {
			.x = i,
			.y = WINDOW_HEIGHT / 2 - wallStripHeight / 2, 
			.width = 1,
			.height = wallStripHeight,
			.color = _color
		};
		drawRect(game, &rect);
	}
}