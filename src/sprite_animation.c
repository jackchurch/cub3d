/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_animation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkabzins <rkabzins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:03:53 by rkabzins          #+#    #+#             */
/*   Updated: 2024/03/01 16:03:55 by rkabzins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "constance.h"

t_sprite	sprite_init(char **map)
{
	int			x;
	int			y;
	t_sprite	sprite;

	y = 0;
	sprite.color = 0xFFD700;
	while (map[y] && !sprite.direction)
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '0')
			{
				sprite.x = x;
				sprite.y = y;
				if (map[y][x + 1] == '1' || map[y][x + 1] == 'D')
					sprite.direction = SOUTH;
				else
					sprite.direction = EAST;
				return (sprite);
			}
		}
	}
}

int	sprite_direction_ew(t_sprite *sprite, char **map)
{
	if (sprite->direction == EAST)
	{
		if (map[(int)sprite->y - 1][(int)sprite->x] == '0')
			return (NORTH);
		if (map[(int)sprite->y][(int)sprite->x + 1] == '1')
			return (SOUTH);
	}
	if (sprite->direction == WEST)
	{
		if (map[(int)sprite->y + 1][(int)sprite->x] == '0')
			return (SOUTH);
		if (map[(int)sprite->y][(int)sprite->x - 1] == '1')
			return (NORTH);
	}
	return (sprite->direction);
}

int	sprite_direction_ns(t_sprite *sprite, char **map)
{
	if (sprite->direction == NORTH)
	{
		if (map[(int)sprite->y][(int)sprite->x - 1] == '0')
			return (WEST);
		if (map[(int)sprite->y - 1][(int)sprite->x] == '1')
			return (EAST);
	}
	if (sprite->direction == SOUTH)
	{
		if (map[(int)sprite->y][(int)sprite->x + 1] == '0')
			return (EAST);
		if (map[(int)sprite->y + 1][(int)sprite->x] == '1')
			return (WEST);
	}
	return (sprite->direction);
}

void	sprite_move(t_game *game)
{
	if (game->sprite.direction == NORTH || game->sprite.direction == SOUTH)
		sprite_direction_ns(game->sprite, game->input.map.content);
	else if (game->sprite.direction == EAST || game->sprite.direction == WEST)
		sprite_direction_ew(game->sprite, game->input.map.content);
}
