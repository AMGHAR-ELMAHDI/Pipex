/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_external_functions2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamghar <eamghar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 18:58:12 by eamghar           #+#    #+#             */
/*   Updated: 2023/01/18 21:30:30 by eamghar          ###   ########.fr       */
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

char	*ft_strdup(const char *s1)
{
	char	*p1;
	char	*p2;
	size_t	i;

	i = 0;
	p1 = (char *)s1;
	p2 = (char *)malloc((ft_strlen(p1) + 1) * sizeof(char));
	if (!p2)
		return (NULL);
	while (i < ft_strlen(p1))
	{
		p2[i] = p1[i];
		i++;
	}
	p2[i] = '\0';
	return (p2);
}
