/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkabzins <rkabzins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:19:05 by rkabzins          #+#    #+#             */
/*   Updated: 2024/02/23 16:19:07 by rkabzins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "structs.h"

// #include <sys/time.h>

// long long	time_get_ms(void)
// {
// 	long long		ms;
// 	struct timeval	time;

// 	gettimeofday(&time, NULL);
// 	ms = time.tv_sec * 1000.0;
// 	ms += time.tv_usec / 1000.0;
// 	return (ms);
// }

// void	measure_frame_rate()
// {
// 	static long long	timeprev = 0;
// 	const int			fps = (int)(1.0 / ((time_get_ms() - timeprev) / 1000.0));

// 	printf("\033[2Jfps: %d\n", fps);
// 	timeprev = time_get_ms();
// }
//		measure_frame_rate();

int	update(t_game *game)
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
	else
		safe_exit(game);
	return (0);
}
