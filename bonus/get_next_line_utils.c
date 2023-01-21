/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamghar <eamghar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 14:26:08 by eamghar           #+#    #+#             */
/*   Updated: 2023/01/21 23:18:17 by eamghar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

size_t	ft_strlen_get(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr_get(char *s, int cc)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (cc == '\0')
		return ((char *)&s[ft_strlen_get(s)]);
	while (s[i] != '\0')
	{
		if (s[i] == (char)cc)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}

char	*ft_strjoin_get(char *str_left, char *buff)
{
	size_t	i;
	size_t	j;
	char	*s;

	if (!str_left)
	{
		str_left = (char *)malloc(1);
		str_left[0] = '\0';
	}
	if (!str_left || !buff)
		return (NULL);
	s = malloc((ft_strlen_get(str_left) + ft_strlen_get(buff)) + 1);
	if (!s)
		exit(1);
	i = -1;
	j = 0;
	while (str_left[++i] != '\0')
		s[i] = str_left[i];
	while (buff[j] != '\0')
		s[i++] = buff[j++];
	s[ft_strlen_get(str_left) + ft_strlen_get(buff)] = '\0';
	free(str_left);
	str_left = NULL;
	return (s);
}

char	*ft_get_line_get(char *str_left)
{
	int		i;
	char	*s;

	i = 0;
	if (!str_left[i])
		return (NULL);
	while (str_left[i] && str_left[i] != '\n')
		i++;
	s = (char *)malloc(i + 2);
	if (!s)
		exit(1);
	i = 0;
	while (str_left[i] && str_left[i] != '\n')
	{
		s[i] = str_left[i];
		i++;
	}
	if (str_left[i] == '\n')
	{
		s[i] = str_left[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

char	*ft_new_str_left_get(char *str_left)
{
	int		i;
	int		j;
	char	*s;

	i = 0;
	while (str_left[i] && str_left[i] != '\n')
		i++;
	if (!str_left[i])
	{
		free(str_left);
		return (NULL);
	}
	s = (char *)malloc(ft_strlen_get(str_left) - i + 1);
	if (!s)
		exit(1);
	i++;
	j = 0;
	while (str_left[i])
		s[j++] = str_left[i++];
	s[j] = '\0';
	free(str_left);
	str_left = NULL;
	return (s);
}
