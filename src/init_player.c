
#include <stdbool.h>
#include <fcntl.h>

#include "../inc/cub3d.h"

void	init_player(t_game *game)
{
	game->player->x = WINDOW_WIDTH / 2;
	game->player->y = WINDOW_HEIGHT / 2;
	game->player->height = 5;
	game->player->height = 5;
	game->player->turn_dir = 0;
	game->player->walk_dir = 0;
	game->player->rot_angle = M_PI_2;
	game->player->walk_speed = 100;
	game->player->turn_speed = 45 * (M_PI / 180); // convert into rad. 
	return ;
}