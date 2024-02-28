/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constance.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkabzins <rkabzins@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:20:36 by rkabzins          #+#    #+#             */
/*   Updated: 2024/02/23 16:20:37 by rkabzins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANCE_H
# define CONSTANCE_H

# include <math.h>
# include <stdbool.h>
# include "../libft/libft.h"
//# include "../mlx_linux/mlx.h"
# include "../mlx_mac/mlx.h"

# ifndef M_PI
#  define M_PI 3.13159265358979323846
# endif

# define FLT_MAX 340282346638528859811704183484516925440.000000

# define TILE_SIZE 64

# define MINIMAP_SCALE 0.2

# define FOV_ANGLE 1.047197666666667

# define NUM_OF_ELEMENTS 6

# define MAC_W 13
# define MAC_S 1
# define MAC_A 0
# define MAC_D 2
# define MAC_LEFT 123
# define MAC_RIGHT 124
# define MAC_ESC 53
# define LINUX_A 97
# define LINUX_S 115
# define LINUX_D 100
# define LINUX_W 119
# define LINUX_ESC 65307

# define NORTH 0
# define SOUTH 1
# define EAST 2
# define WEST 3
# define CEILING 4
# define FLOOR 5
# define MAP 6

//Regular text
# define BLK "\e[0;30m"
# define RED "\e[0;31m"
# define GRN "\e[0;32m"
# define YEL "\e[0;33m"
# define BLU "\e[0;34m"
# define MAG "\e[0;35m"
# define CYN "\e[0;36m"
# define WHT "\e[0;37m"

//Regular bold text
# define BBLK "\e[1;30m"
# define BRED "\e[1;31m"
# define BGRN "\e[1;32m"
# define BYEL "\e[1;33m"
# define BBLU "\e[1;34m"
# define BMAG "\e[1;35m"
# define BCYN "\e[1;36m"
# define BWHT "\e[1;37m"

//Regular underline text
# define UBLK "\e[4;30m"
# define URED "\e[4;31m"
# define UGRN "\e[4;32m"
# define UYEL "\e[4;33m"
# define UBLU "\e[4;34m"
# define UMAG "\e[4;35m"
# define UCYN "\e[4;36m"
# define UWHT "\e[4;37m"

//Reset
# define CRESET "\e[0m"

#endif
