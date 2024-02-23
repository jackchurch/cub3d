/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkabzins <rkabzins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 17:18:32 by rkabzins          #+#    #+#             */
/*   Updated: 2024/02/23 17:18:34 by rkabzins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

extern t_player	g_player;

void	strafe(float side_step, float *new_player_x, float *new_player_y)
{
	if (side_step > 0)
	{
		*new_player_x = g_player.x + cos(g_player.rotation_angle
				+ (g_player.strafe_direction
					* g_player.turn_speed * 9)) * side_step;
		*new_player_y = g_player.y + sin(g_player.rotation_angle
				+ (g_player.strafe_direction
					* g_player.turn_speed * 9)) * side_step;
	}
	if (side_step < 0)
	{
		*new_player_x = g_player.x + cos(g_player.rotation_angle
				+ (g_player.strafe_direction
					* g_player.turn_speed * 27)) * side_step;
		*new_player_y = g_player.y + sin(g_player.rotation_angle
				+ (g_player.strafe_direction
					* g_player.turn_speed * 27)) * side_step;
	}
}

void	move_player(t_game *game)
{
	float	move_step;
	float	side_step;
	float	new_player_x;
	float	new_player_y;

	if (!game)
		return ;
	move_step = g_player.walk_direction * g_player.walk_speed;
	side_step = g_player.strafe_direction * g_player.walk_speed;
	g_player.rotation_angle += g_player.turn_direction * g_player.turn_speed;
	new_player_x = g_player.x + cos(g_player.rotation_angle) * move_step;
	new_player_y = g_player.y + sin(g_player.rotation_angle) * move_step;
	strafe(side_step, &new_player_x, &new_player_y);
	if (map_content_at(game, new_player_x, new_player_y) != '1')
	{
		g_player.x = new_player_x;
		g_player.y = new_player_y;
	}
}
