/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_external_functions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamghar <eamghar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 16:34:47 by eamghar           #+#    #+#             */
/*   Updated: 2023/01/18 18:21:13 by eamghar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

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

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ns;
	size_t	range;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		exit(1);
	range = ft_strlen (s1) + ft_strlen (s2);
	ns = (char *)malloc(sizeof(char) * (range + 1));
	if (!ns)
		exit(1);
	while (i < ft_strlen (s1))
	{
		ns[i] = s1[i];
		i++;
	}
	while (j < ft_strlen (s2))
	{
		ns[i + j] = s2[j];
		j++;
	}
	ns[i + j] = '\0';
	return (ns);
}
