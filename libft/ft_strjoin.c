/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkabzins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 01:36:07 by rkabzins          #+#    #+#             */
/*   Updated: 2022/02/18 01:36:44 by rkabzins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char			*dest;
	unsigned int	s2_index;
	unsigned int	s1_index;

	if (!s1)
	{
		s1 = malloc(1);
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	s1_index = -1;
	s2_index = 0;
	dest = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!dest)
		return (NULL);
	while (s1[++s1_index])
		dest[s1_index] = s1[s1_index];
	while (s2[s2_index])
		dest[s1_index++] = s2[s2_index++];
	dest[s1_index] = 0;
	free(s1);
	return (dest);
}
