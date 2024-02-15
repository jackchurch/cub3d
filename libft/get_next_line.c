/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkabzins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 03:11:48 by rkabzins          #+#    #+#             */
/*   Updated: 2024/02/15 14:51:24 by rkabzins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*read_file_to_memory(int fd, char *output)
{
	char	*buff;
	int		read_bytes;

	read_bytes = 1;
	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	while (!ft_strchr(output, '\n') && read_bytes != 0)
	{
		read_bytes = read(fd, buff, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[read_bytes] = '\0';
		output = ft_strjoin(output, buff);
	}
	free(buff);
	return (output);
}

char	*ft_save(char *save)
{
	int		i;
	int		j;
	char	*s;

	i = 0;
	j = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (!save[i])
	{
		free(save);
		return (NULL);
	}
	s = malloc(ft_strlen(save) - i + 1);
	if (!s)
		return (NULL);
	i++;
	while (save[i])
		s[j++] = save[i++];
	s[j] = '\0';
	free(save);
	return (s);
}

char	*copy_line(char *input)
{
	int		i;
	char	*output;

	i = 0;
	if (!input[i])
		return (NULL);
	while (input[i] && input[i] != '\n')
		i++;
	output = malloc(i + 2);
	if (!output)
		return (NULL);
	i = 0;
	while (input[i] && input[i] != '\n')
	{
		output[i] = input[i];
		i++;
	}
	if (input[i] == '\n')
	{
		output[i] = input[i];
		i++;
	}
	output[i] = '\0';
	return (output);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*save;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	save = read_file_to_memory(fd, save);
	if (!save)
		return (NULL);
	line = copy_line(save);
	save = ft_save(save);
	return (line);
}
