#include "../inc/cub3d.h"
#include "../inc/draw.h"
#include "../inc/map.h"
#include "../inc/render.h"
#include "../inc/maths.h"
#include "../inc/ray.h"
#include "../inc/constance.h"
#include <math.h>

t_player	player;

	// Add wall textrues here?
void	setup(t_game *game)
{
	player.x = game->input.map.spawn_loc.x * TILE_SIZE + TILE_SIZE / 2;
	player.y = game->input.map.spawn_loc.y * TILE_SIZE + TILE_SIZE / 2;
	player.width = 1;
	player.height = 1;
	player.turn_direction = 0;
	player.walk_direction = 0;
	player.strafe_direction = 0;
	player.rotation_angle = game->input.map.rot_angle;
	player.walk_speed = 10;
	player.turn_speed = M_PI / 180 * player.walk_speed;
	ft_memset(&game->update, 0, sizeof(t_update));
}

void	safe_exit(t_game *game)
{
	int	i;

	i = 0;
	if (game->win)
		free(game->win);
	if (game->mlx)
		free(game->mlx);
	if (game->rays)
		free(game->rays);
	if (game->input.map.content)
	{
		while (i < game->input.map.rows && game->input.map.content[i])
		{
			free(game->input.map.content[i]);
			game->input.map.content[i] = NULL;
			i++;
		}
		free(game->input.map.content);
	}
	if (game)
		free(game);
	exit(0);
}

void	move_player(t_game *game)
{
	float	move_step;
	float	side_step;
	float	new_player_x;
	float	new_player_y;

	if (!game)
		return ;
	move_step = player.walk_direction * player.walk_speed;
	side_step = player.strafe_direction * player.walk_speed;
	player.rotation_angle += player.turn_direction * player.turn_speed;
	new_player_x = player.x + cos(player.rotation_angle) * move_step;
	new_player_y = player.y + sin(player.rotation_angle) * move_step;
	if (side_step > 0)
	{
		new_player_x = player.x + cos(player.rotation_angle
			+ (player.strafe_direction * player.turn_speed * 9)) * side_step;
		new_player_y = player.y + sin(player.rotation_angle
			+ (player.strafe_direction * player.turn_speed * 9)) * side_step;
	}
	if (side_step < 0)
	{
		new_player_x = player.x + cos(player.rotation_angle
			+ (player.strafe_direction * player.turn_speed * 27)) * side_step;
		new_player_y = player.y + sin(player.rotation_angle 
		+ (player.strafe_direction * player.turn_speed * 27)) * side_step;
	}
	if (map_content_at(game, new_player_x, new_player_y) != '1')
	{
		player.x = new_player_x;
		player.y = new_player_y;
	}
}

// 320 pixls window width
// 60 deg FOV -> must convert to rads
//
// while (column < 320width)
// {
// 	cast a ray
// 	trace the ray until it intersects with a wall (map[i][j] == 1)
// 	record the intersection x,y and ray distance
// 	add angle increment to go to the next ray (ray_angle += 60/320)to rads
// }

void	render(t_game *game)
{
	move_player(game);
	cast_all_rays(game);
	generate_3d_projection(game);
	render_map(game);
	render_rays(game);
	render_player(game);
	mlx_put_image_to_window(game->mlx, game->win, game->data.img, 0, 0);
}

int	main(int argc, char **argv)
{
	t_game	*game;

	if (argc != 2)
		return (printf("Error: Please execute with only 1 argument.\n"));
	game = (t_game *)ft_calloc(1, sizeof(t_game));
	game->input = init_cub_file(argv[1]);
	game->win_width = game->input.map.longest_row * TILE_SIZE;
	game->win_height = game->input.map.rows * TILE_SIZE;
	init_window(game);
	setup(game);
	game->num_rays = game->win_width;
	game->data = (t_data){0};
	game->rays = (t_ray *)ft_calloc(game->num_rays, sizeof(t_ray));
	game->data.img = mlx_new_image(game->mlx,
			game->win_width, game->win_height);
	game->data.addr = mlx_get_data_addr(game->data.img, &game->data.bpp,
			&game->data.line_length, &game->data.endian);
	// process_input(); // See keyhooks
	// update(game); // Add FPS if have time.
	render(game);
	//mlx_loop_hook(game->mlx, update, &game);
	mlx_loop(game->mlx);
	return (0);
}
