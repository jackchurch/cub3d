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

int	mapContentAt(float x, float y)
{
	int mapGridIndexX = (int)floor(x / TILE_SIZE);
	int mapGridIndexY = (int)floor(y / TILE_SIZE);
	return (map[mapGridIndexY][mapGridIndexX]);
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

void renderMap(t_game *game)
{
	for (int i = 0; i < MAP_NUM_ROWS; i++)
	{
		for (int j = 0; j < MAP_NUM_COLS; j++)
		{
			int tileX = j * TILE_SIZE; 
			int tileY = i * TILE_SIZE;
			int _mapContent = mapContentAt(i, j);
			int tileColor = (_mapContent != 0 ? 0x000000FF : 0x00FFFFFF);
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
