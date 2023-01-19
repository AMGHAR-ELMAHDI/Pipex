/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_external_functions2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamghar <eamghar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 18:58:12 by eamghar           #+#    #+#             */
/*   Updated: 2023/01/19 17:51:05 by eamghar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ns;
	size_t	range;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
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

char	*ft_strdup(const char *s1)
{
	char	*p1;
	char	*p2;
	size_t	i;

	i = 0;
	p1 = (char *)s1;
	p2 = (char *)malloc((ft_strlen(p1) + 1) * sizeof(char));
	if (!p2)
		exit(1);
	while (i < ft_strlen(p1))
	{
		p2[i] = p1[i];
		i++;
	}
	p2[i] = '\0';
	return (p2);
}

static	int	skip(char const c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1) - 1;
	while (s1[start] && skip(s1[start], set))
		start++;
	while (end >= 0 && skip(s1[end], set))
		end--;
	if (end == -1)
		return (ft_substr(s1, start, 0));
	return (ft_substr(s1, start, (end - start + 1)));
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return ((char *) ft_calloc(1, sizeof(char)));
	if (start + len >= ft_strlen(s))
		substr = malloc(sizeof(char) * (ft_strlen(s) - start + 1));
	else
		substr = malloc(sizeof(char) * (len + 1));
	if (!substr)
		exit(1);
	while (s[start] && i < len)
		substr[i++] = s[start++];
	substr[i] = '\0';
	return (substr);
}
