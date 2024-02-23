#include "cub3d.h"
#include "structs.h"

int update(t_game *game)
{
	if (game->update.refresh_rate < 30)
		game->update.refresh_rate += 0.1;
	else if (game->update.end_game < 1)
	{
		render(game);
		game->update.refresh_rate = 0;
		if (game->update.animate < 90)
			game->update.animate++;
		else
			game->update.animate = 0;
	}
	return (0);
}