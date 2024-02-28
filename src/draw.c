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
	dst = (game->data.addr + (y * game->data.line_length
				+ x * game->data.bpp / 8));
	*(unsigned int *)dst = color;
}

int	find_texture_pixel(t_game *game, int dir,int x, int y)
{
	char	*dest;

	dest = (game->data.addr + (y * game->data.line_length
				+ x * game->data.bpp / 8));
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

void	draw_walls(t_game *game, t_image *wall, int dir)
{
	int	i;
	int	j;
	int	color;

	i = wall->loc.x;
	while (i <= (wall->loc.x + wall->width))
	{

		//printf("loc.x = %d\nwall->width = %d\n", wall->loc.x, wall->width);
		j = wall->loc.y;
		while (j <= (wall->loc.y + wall->height))
		{
			color = find_texutre_pixel(game, i, j);
			//printf("loc.y = %d\nwall->height = %d\n", wall->loc.y, wall->height);
			// mlx_put_image_to_window(game->mlx, game->win, wall->img,
			// 	wall->loc.x, wall->loc.y);
			my_mlx_pixel_put(game, wall->loc.x, wall->loc.y, color);
			j++;
		}
		i++;
	}
	return ;
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
