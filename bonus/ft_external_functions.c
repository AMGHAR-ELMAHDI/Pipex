/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_external_functions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamghar <eamghar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 16:34:47 by eamghar           #+#    #+#             */
/*   Updated: 2023/01/20 16:19:50 by eamghar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;

	if (count == SIZE_MAX && size == SIZE_MAX)
		return (NULL);
	p = malloc(count * size);
	if (!p)
		return (NULL);
	ft_bzero (p, size * count);
	return (p);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*str1;
	char	*str2;
	size_t	i;
	size_t	j;
	size_t	needle_len;

	i = 0;
	needle_len = ft_strlen(needle);
	str1 = (char *)haystack;
	str2 = (char *)needle;
	if (!*str2)
		return (str1);
	while (i < len && haystack[i])
	{
		j = 0;
		while (str1[i + j] == str2[j] && len - i >= needle_len)
		{
			if (!str2[j + 1])
				return (str1 + i);
			else
				j++;
		}
		i++;
	}
	return (NULL);
}

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*p;

	i = 0;
	p = (char *)s;
	while (i < n)
	{
		*p++ = '\0';
		i++;
	}
}
