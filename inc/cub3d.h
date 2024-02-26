/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkabzins <rkabzins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:20:53 by rkabzins          #+#    #+#             */
/*   Updated: 2024/02/23 16:20:55 by rkabzins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdbool.h>
# include "structs.h"
# include <math.h>
# include "../libft/libft.h"
# include "../mlx_linux/mlx.h"
# include "../mlx_mac/mlx.h"
# include "constance.h"
# include "ray.h"
# include "cub_file.h"
# include "map.h"

//error
int		err_i(char *str);
void	err_v(char *str);
void	*err_p(char *str);

// init
bool	init_window(t_game *game);
int		init_textures(t_game *game);
void	fill_textures(t_game *game, int i);

// main.c
int		safe_exit(t_game *game);

// To sort
int		render(t_game *game);
int		update(t_game *game);
void	strafe(float side_step, float *new_player_x, float *new_player_y);
void	move_player(t_game *game);

#endif
