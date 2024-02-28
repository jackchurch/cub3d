/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_movement.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkabzins <rkabzins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 19:50:13 by rkabzins          #+#    #+#             */
/*   Updated: 2024/02/28 19:50:15 by rkabzins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

extern t_player	g_player;

void	mouse_rotate(t_game *game)
{
	int	x;
	int	y;

	mlx_mouse_get_pos(game->mlx, &x, &y);
	g_player.rotation_angle += (float)x / 4000 * g_player.turn_speed;
	mlx_mouse_move(game->mlx, game->win_width / 2, game->win_height / 2);
}