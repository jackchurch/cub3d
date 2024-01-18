/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchurch <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 11:05:51 by jchurch           #+#    #+#             */
/*   Updated: 2022/06/09 11:44:27 by jchurch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*reduce_static_string(char *static_string)
{
	char	*return_string;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (static_string[i] != '\n' && static_string[i])
		i++;
	if (!static_string[i])
	{
		free(static_string);
		return (NULL);
	}
	if (!static_string)
		return (NULL);
	return_string = malloc(sizeof(char) * ((ft_strlen(static_string) - i)));
	if (!return_string)
		return (NULL);
	i++;
	while (static_string[i])
		return_string[j++] = static_string[i++];
	return_string[j] = '\0';
	free(static_string);
	return (return_string);
}

char	*read_file(int fd, char *static_string)
{
	int		read_number;
	char	*buffer;

	read_number = 1;
	buffer = (char *)malloc(100 + 1);
	if (!buffer)
		return (NULL);
	while (!ft_strchr(static_string, '\n'))
	{
		read_number = read(fd, buffer, 100);
		if (read_number <= 0)
			break ;
		buffer[read_number] = '\0';
		static_string = ft_strjoin(static_string, buffer);
	}
	free(buffer);
	if (!static_string)
		return (NULL);
	return (static_string);
}

char	*find_new_line(char *static_string)
{
	char	*return_string;
	int		i;

	i = 0;
	while (static_string[i] && static_string[i] != '\n')
		i++;
	if (static_string[i] == '\n')
	{
		return_string = malloc(sizeof(char) * (i + 2));
		if (!return_string)
			return (NULL);
		return_string[i + 1] = '\0';
	}
	else
	{
		return_string = malloc(sizeof(char) * (i + 1));
		if (!return_string)
			return (NULL);
	}
	while (i >= 0)
	{
		return_string[i] = static_string[i];
		i--;
	}
	return (return_string);
}

char	*get_next_line(int fd)
{
	static char	*static_string;
	char		*return_string;

	if (fd < 0 || 100 < 1)
		return (NULL);
	static_string = read_file(fd, static_string);
	if (!static_string)
		return (NULL);
	if (static_string[0])
		return_string = find_new_line(static_string);
	else
		return_string = (NULL);
	static_string = reduce_static_string(static_string);
	if (static_string && !*return_string)
	{
		free(return_string);
		return (NULL);
	}
	return (return_string);
}
