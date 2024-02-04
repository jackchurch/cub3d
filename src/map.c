#include "../inc/cub3d.h"
#include "../inc/draw.h"
#include "../inc/map.h"

// this is a temporary global variable, used for testing instead of input maps.
/*static const int	map[MAP_NUM_ROWS][MAP_NUM_COLS] = {
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
};*/

char	map_content_at(t_game *game, float x, float y)
{
	int	map_grid_index_y;
	int	map_grid_index_x;

	printf("x = %f, y = %f\n", x, y);
	map_grid_index_y = (int)floor(y / TILE_SIZE);
	map_grid_index_x = (int)floor(x / TILE_SIZE);
	printf("map content at %f:%f is %d\n", x, y, game->input.map.content[map_grid_index_y][map_grid_index_x]);
	return (game->input.map.content[map_grid_index_y][map_grid_index_x]);
}

char	get_map_at(t_game *game, int i, int j)
{
	return (game->input.map.content[i][j]);
}

bool	is_inside_map(float x, float y)
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

void	tile_rect_init(t_rectangle *map_tile_rect, const t_tile tile)
{
	map_tile_rect->x = tile.x * MINIMAP_SCALE;
	map_tile_rect->y = tile.y * MINIMAP_SCALE;
	map_tile_rect->width = TILE_SIZE * MINIMAP_SCALE;
	map_tile_rect->height = TILE_SIZE * MINIMAP_SCALE;
	map_tile_rect->color = tile.color;
}

void	render_map(t_game *game)
{
	int			i;
	int			j;
	t_tile		tile;
	t_rectangle	map_tile_rect;

	i = -1;
	while (++i < MAP_NUM_ROWS)
	{
		j = -1;
		while (++j < MAP_NUM_COLS)
		{
			tile.x = j * TILE_SIZE;
			tile.y = i * TILE_SIZE;
			if (get_map_at(game, i, j) != '0')
				tile.color = 0x000000FF;
			else
				tile.color = 0x00FFFFFF;
			tile_rect_init(&map_tile_rect, tile);
			draw_rect(game, &map_tile_rect);
		}
	}
}
