/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkabzins <rkabzins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:16:22 by rkabzins          #+#    #+#             */
/*   Updated: 2024/02/23 16:16:23 by rkabzins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include "../inc/draw.h"

void	my_mlx_pixel_put(t_game *game, int x, int y, unsigned int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= game->win_width || y >= game->win_height)
		return ;
	dst = ((char *)game->data.addr + (y * game->data.line_length
				+ x * game->data.bpp / 8));
	*(unsigned int *)dst = color;
}

int	find_texture_pixel(t_game *game, int dir, int x, int y)
{
	char	*dest;

	dest = (((char *)game->walls[dir].addr) + (y * game->walls[dir].line_length
				+ x * game->walls[dir].bpp / 8));
	return (*(unsigned int *)dest);
}

void	draw_rect(t_game *game, t_rectangle *rect)
{
	int	i;
	int	j;

	i = rect->x;
	while (i <= (rect->x + rect->width))
	{
		j = rect->y;
		while (j <= (rect->y + rect->height))
		{
			my_mlx_pixel_put(game, i, j, rect->color);
			j++;
		}
		i++;
	}
	return ;
}

void	draw_walls(t_game *game, t_image *wall, int dir, int ray)
{
	float	x;
	int		j;
	int		color;

	x = game->rays[ray].wall_hit_x / TILE_SIZE;
	if (game->rays[ray].was_hit_vertical)
		x = game->rays[ray].wall_hit_y / TILE_SIZE;
	x = x - floor(x);
	j = 0;
	while (j < wall->height)
	{
		color = find_texture_pixel(game, dir,
				(int)(x * TILE_SIZE), ((float)j / wall->height) * TILE_SIZE);
		my_mlx_pixel_put(game, wall->loc.x, j + wall->loc.y, color);
		j++;
	}
}

void	draw_line(t_game *game, const t_line *line)
{
	t_line_math	drawn;
	int			i;

	drawn.delta_x = (line->x1 - line->x0);
	drawn.delta_y = (line->y1 - line->y0);
	drawn.abs_x = abs(drawn.delta_x);
	drawn.abs_y = abs(drawn.delta_y);
	if (drawn.abs_x >= drawn.abs_y)
		drawn.longest_side_length = drawn.abs_x;
	else
		drawn.longest_side_length = drawn.abs_y;
	drawn.x_increment = drawn.delta_x / (float)drawn.longest_side_length;
	drawn.y_increment = drawn.delta_y / (float)drawn.longest_side_length;
	drawn.current_x = line->x0;
	drawn.current_y = line->y0;
	i = -1;
	while (++i < drawn.longest_side_length)
	{
		my_mlx_pixel_put(game, round(drawn.current_x),
			round(drawn.current_y), line->color);
		drawn.current_x += drawn.x_increment;
		drawn.current_y += drawn.y_increment;
	}
}
