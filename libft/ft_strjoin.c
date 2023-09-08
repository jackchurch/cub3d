/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchurch <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 16:26:24 by jchurch           #+#    #+#             */
/*   Updated: 2022/02/06 16:26:26 by jchurch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result_string;
	int		i;
	int		j;

	if (!s1 && !s2)
		return (NULL);
	result_string = NULL;
	i = 0;
	j = 0;
	result_string = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!result_string)
		return (NULL);
	while (s1[i])
	{
		result_string[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		result_string[i] = s2[j];
		i++;
		j++;
	}
	result_string[i] = '\0';
	return (result_string);
}
