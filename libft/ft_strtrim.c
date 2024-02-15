/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkabzins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 08:16:02 by rkabzins          #+#    #+#             */
/*   Updated: 2022/03/24 08:16:17 by rkabzins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*static size_t	trimmed_size(char const *s1, char const *set)
{
	size_t	len;
	int		index;
	int		active;

	active = 0;
	len = 0;
	index = 0;
	while (s1[index])
	{
		if (s1[index] != set && active == 1)
			len++;
		index++;
	}
	index--;
	while (s1[index] == set)
	{
		len--;
		index--;
	}
	return (len);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t			s1_size;
	unsigned int	s1_index;
	unsigned int	trimmed_index;
	char			*trimmed_str;

	s1_size = trimmed_size(s1, set);
	s1_index = 0;
	trimmed_index = 0;
	trimmed_str = malloc((sizeof(char) * s1_size + 1));
	if (!trimmed_str)
		return (NULL);
	while (s1[s1_index] == set)
		s1_index++;
	while (s1[s1_index] != '\0' && s1_index <= s1_size)
		trimmed_str[trimmed_index++] = s1[s1_index++];
	trimmed_str[trimmed_index] = '\0';
	return (trimmed_str);
}
*/
static int	ft_getstart(const char *s1, const char *set)
{
	size_t	len;
	size_t	i;

	len = ft_strlen(s1);
	i = 0;
	while (i < len)
	{
		if (ft_strchr(set, s1[i]) == 0)
			break ;
		i++;
	}
	return (i);
}

static int	ft_getend(const char *s1, const char *set)
{
	size_t	len;
	size_t	i;

	len = ft_strlen(s1);
	i = 0;
	while (i < len)
	{
		if (ft_strchr(set, s1[len - i - 1]) == 0)
			break ;
		i++;
	}
	return (len - i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*newstr;

	if (s1 == NULL)
		return (NULL);
	if (set == NULL)
		return (ft_strdup(s1));
	start = ft_getstart(s1, set);
	end = ft_getend(s1, set);
	if (start >= end)
		return (ft_strdup(""));
	newstr = (char *)malloc(sizeof(char) * (end - start + 1));
	if (newstr == NULL)
		return (NULL);
	ft_strlcpy(newstr, s1 + start, end - start + 1);
	return (newstr);
}
