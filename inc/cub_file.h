/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_file.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkabzins <rkabzins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:20:44 by rkabzins          #+#    #+#             */
/*   Updated: 2024/02/23 16:20:46 by rkabzins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_FILE_H
# define CUB_FILE_H

# include <math.h>
# include <stdbool.h>
# include "../libft/libft.h"
# include "mlx.h"
# include "cub3d.h"
# include "constance.h"
# include "structs.h"

t_input	init_cub_file(char *file_name);
int		open_cub_file(char *file_name);
bool	is_xpm_file(char *file_name);
char	*remove_tail_whitespace(char *in_string);
//void	find_first_char(char *current_line, int *i);
bool	is_white_space(char c);
int		is_only_one(char *line);
char	*isolate_element_path(char *str);
int		ceiling_floor_branch(t_input *input,
			char *current_line, int element_type);

#endif
