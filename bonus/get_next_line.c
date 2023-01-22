/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamghar <eamghar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 14:26:11 by eamghar           #+#    #+#             */
/*   Updated: 2023/01/22 17:53:16 by eamghar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*get_next_line_get(int fd)
{
	static char	*str_left;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str_left = ft_read_str_get(fd, str_left);
	if (!str_left)
		return (NULL);
	line = ft_get_line_get(str_left);
	str_left = ft_new_str_left_get(str_left);
	return (line);
}

char	*ft_read_str_get(int fd, char *str_left)
{
	char	*buff;
	int		bytes_read;

	buff = (char *)malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr_get(str_left, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buff);
			free(str_left);
			return (NULL);
		}
		buff[bytes_read] = '\0';
		str_left = ft_strjoin_get(str_left, buff);
	}
	free(buff);
	return (str_left);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
