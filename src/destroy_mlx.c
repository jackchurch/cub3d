
#include <stdbool.h>
#include <fcntl.h>

#include "../inc/cub3d.h"

void	deallocate_mlx(t_game *game)
{
	printf("deallocate_mlx\n");
	free(game->win);
	free(game->mlx);
	return ;
}

void	deallocate_map(t_game *game)
{
	int	i;
	printf("deallocate_map\n");
	i = 0;
	while (i < game->map_num_rows)
		free(game->map[i++]);
	free(game->map);
	return ;
}

int	safe_exit(t_game *game)
{
	printf("safe_exit\n");
	deallocate_map(game);
	deallocate_mlx(game);
	free(game);
	exit(0);
}
