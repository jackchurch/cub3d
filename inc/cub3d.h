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
# include "../mlx_mac/mlx.h"
# include "constance.h"
# include "ray.h"
# include "cub_file.h"
# include "map.h"

//error
int		err_i(char *str, int i);
void	err_v(char *str);
void	*err_p(char *str);
int		check_more_vars(t_input *input, int err);
int		check_vars(t_input *input);

// init
bool	init_window(t_game *game);
int		init_textures(t_game *game);
void	fill_textures(t_game *game, int i);

// main.c
int		bad_file(t_game *game);
int		safe_exit(t_game *game);

// To sort
void	mouse_rotate(t_game *game);
int		render(t_game *game);
int		update(t_game *game);
void	strafe(float side_step, float *new_player_x, float *new_player_y);
void	move_player(t_game *game);

//eff norm, honestly. Let us COOK.
bool	any_invalid_chars(const char *str);
bool	color_range(int *rgb);
void	eff_norm(t_input *input);
int		seriously_hate_norm(char **values);
void	fuck_norm(int i, char **values);
void	free_shit(char *str, int *rgb);
#endif
