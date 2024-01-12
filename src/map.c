#include "../inc/cub3d.h"
#include "../inc/draw.h"
#include "../inc/map.h"

static const int	map[MAP_NUM_ROWS][MAP_NUM_COLS] = {
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

int	mapContentAt(float x, float y)
{
	int	mapGridIndexY;
	int	mapGridIndexX;

	mapGridIndexY = (int)floor(y / TILE_SIZE);
	mapGridIndexX = (int)floor(x / TILE_SIZE);
	return (map[mapGridIndexY][mapGridIndexX]);
}

int	getMapAt(int i, int j)
{
	return (map[i][j]);
}

bool	isInsideMap(float x, float y)
{
	return (x >= 0 && x <= MAP_NUM_COLS * TILE_SIZE
		&& y >= 0 && y <= MAP_NUM_ROWS * TILE_SIZE);
}

// bool mapHasWallAt(float x, float y)
// {
// 	// IF out of bounds return true. 
// 	if (x < 0 || x > WINDOW_WIDTH || y < 0 || y > WINDOW_HEIGHT)
// 		return (true);
// 	int mapGridIndexX = floor(x / TILE_SIZE);
// 	int mapGridIndexY = floor(y / TILE_SIZE);
// 	// IF wall collision, return true
// 	if (map[mapGridIndexY][mapGridIndexX] != 0)
// 		return (true);
// 	return (false);
// }

void	renderMap(t_game *game)
{
	int	i;
	int	j;
	t_tile	tile;
	t_rectangle mapTileRect;

	i = -1;
	while (++i < MAP_NUM_ROWS)
	{
		j = -1;
		while (++j < MAP_NUM_COLS)
		{
			tile.x = j * TILE_SIZE; 
			tile.y = i * TILE_SIZE;
			if (getMapAt(i, j) != 0)
				tile.color = 0x000000FF;
			else
				tile.color = 0x00FFFFFF;
			mapTileRect =
			{
				tile.x * MINIMAP_SCALE, tile.y * MINIMAP_SCALE,
				TILE_SIZE * MINIMAP_SCALE, TILE_SIZE * MINIMAP_SCALE,
				tile.color
			};
			drawRect(game, &mapTileRect);
		}
	}
}
