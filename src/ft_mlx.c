/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkabzins <rkabzins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:16:30 by rkabzins          #+#    #+#             */
/*   Updated: 2024/02/23 16:16:32 by rkabzins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_mlx.h"
#include "../inc/constance.h"

extern t_player	g_player;

int	key_release(int keycode)
{
	if (keycode == MAC_LEFT || keycode == MAC_RIGHT)
		g_player.turn_direction = 0;
	if (keycode == MAC_W || keycode == LINUX_W
		|| keycode == MAC_S || keycode == LINUX_S)
		g_player.walk_direction = 0;
	if (keycode == MAC_A || keycode == MAC_D)
		g_player.strafe_direction = 0;
	return (0);
}

int	key_hook(int keycode, t_game *game)
{
	if (keycode == MAC_LEFT)
		g_player.turn_direction = -1;
	if (keycode == MAC_RIGHT)
		g_player.turn_direction = 1;
	if (keycode == MAC_A || keycode == LINUX_A)
		g_player.strafe_direction = -1;
	if (keycode == MAC_D || keycode == LINUX_D)
		g_player.strafe_direction = 1;
	if (keycode == MAC_W || keycode == LINUX_W)
		g_player.walk_direction = 1;
	if (keycode == MAC_S || keycode == LINUX_S)
		g_player.walk_direction = -1;
	if (keycode == MAC_ESC || keycode == LINUX_ESC)
		safe_exit(game);
	render(game);
	return (0);
}

bool	init_window(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		safe_exit(game);
	game->win = mlx_new_window(game->mlx, game->win_width, game->win_height,
			"Legally Distinct Slï'mę Game");
	if (!game->win)
		safe_exit(game);
	mlx_hook(game->win, 2, 1L << 0, key_hook, game);
	mlx_hook(game->win, 3, 1L << 1, key_release, game);
	return (true);
}
