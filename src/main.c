/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkabzins <rkabzins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:16:46 by rkabzins          #+#    #+#             */
/*   Updated: 2024/02/23 16:16:48 by rkabzins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include "../inc/draw.h"
#include "../inc/map.h"
#include "../inc/render.h"
#include "../inc/maths.h"
#include "../inc/ray.h"
#include "../inc/constance.h"
#include "../inc/ft_mlx.h"
#include <math.h>

t_player	g_player;

	// Add wall textrues here?
void	setup(t_game *game)
{
	if (game->input.map.rot_angle == 0 || game->input.map.rot_angle == 1)
		safe_exit(game);
	g_player.x = game->input.map.spawn_loc.x * TILE_SIZE + TILE_SIZE / 2;
	g_player.y = game->input.map.spawn_loc.y * TILE_SIZE + TILE_SIZE / 2;
	g_player.width = 1;
	g_player.height = 1;
	g_player.turn_direction = 0;
	g_player.walk_direction = 0;
	g_player.strafe_direction = 0;
	g_player.rotation_angle = game->input.map.rot_angle;
	g_player.walk_speed = 10;
	g_player.turn_speed = M_PI / 180 * g_player.walk_speed;
	ft_memset(&game->update, 0, sizeof(t_update));
}

int	safe_exit(t_game *game)
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
	return (exit(0), 0);
}

int	render(t_game *game)
{
	draw_ceiling(game);
	move_player(game);
	cast_all_rays(game);
	generate_3d_projection(game);
	render_map(game);
	render_rays(game);
	render_player(game);
	mlx_put_image_to_window(game->mlx, game->win, game->data.img, 0, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	*game;

	if (argc != 2)
		return (err_i("Please execute with exactly 1 argument.", 0));
	game = (t_game *)ft_calloc(1, sizeof(t_game));
	game->input = init_cub_file(game, argv[1]);
	game->win_width = game->input.map.longest_row * TILE_SIZE;
	game->win_height = game->input.map.rows * TILE_SIZE;
	game->tile_size = TILE_SIZE;
	init_window(game);
	setup(game);
	if (init_textures(game) > 0)
		return (err_i("Error loading textures. Please check filepath.", 0));
	game->num_rays = game->win_width;
	game->data = (t_data){0};
	game->rays = (t_ray *)ft_calloc(game->num_rays, sizeof(t_ray));
	game->data.img = mlx_new_image(game->mlx,
			game->win_width, game->win_height);
	game->data.addr = mlx_get_data_addr(game->data.img, &game->data.bpp,
			&game->data.line_length, &game->data.endian);
	mlx_loop_hook(game->mlx, update, game);
	mlx_loop(game->mlx);
	return (0);
}
