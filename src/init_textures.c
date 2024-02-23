/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkabzins <rkabzins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 17:41:38 by rkabzins          #+#    #+#             */
/*   Updated: 2024/02/23 17:41:39 by rkabzins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_wall	init_textures(t_game *game)
{
	t_wall	wall;

	ft_memset(&wall, 0, sizeof(t_wall));
	init_wall(game, &wall);
	return (wall);
}

void	init_wall(t_game *game, t_wall *wall)
{
	ft_memset(&wall->north, 0, sizeof(t_image));
	wall->north.img = mlx_xpm_file_to_image(game->mlx,
			game->input.north_path, &game->tile_size, &game->tile_size);
	wall->north.addr = mlx_get_data_addr(wall->north.img, &wall->north.bpp,
			&wall->north.line_length, &wall->north.endian);
	ft_memset(&wall->south, 0, sizeof(t_image));
	wall->south.img = mlx_xpm_file_to_image(game->mlx,
			game->input.south_path, &game->tile_size, &game->tile_size);
	wall->south.addr = mlx_get_data_addr(wall->south.img, &wall->south.bpp,
			&wall->south.line_length, &wall->south.endian);
	ft_memset(&wall->east, 0, sizeof(t_image));
	wall->east.img = mlx_xpm_file_to_image(game->mlx,
			game->input.east_path, &game->tile_size, &game->tile_size);
	wall->east.addr = mlx_get_data_addr(wall->east.img, &wall->east.bpp,
			&wall->east.line_length, &wall->east.endian);
	ft_memset(&wall->west, 0, sizeof(t_image));
	wall->west.img = mlx_xpm_file_to_image(game->mlx,
			game->input.west_path, &game->tile_size, &game->tile_size);
	wall->west.addr = mlx_get_data_addr(wall->west.img, &wall->west.bpp,
			&wall->west.line_length, &wall->west.endian);
}
