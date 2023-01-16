/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamghar <eamghar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 16:07:09 by eamghar           #+#    #+#             */
/*   Updated: 2023/01/16 23:41:36 by eamghar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>
# include <string.h>
# include <limits.h>
# include <math.h>
# include <fcntl.h>

char	**ft_split(char const *s, char c);
int		ft_strncmp(const char *s1, const char *s2);
void	*ft_calloc(size_t count, size_t size);
size_t	ft_strlen(const char *str);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
void	ft_bzero(void *s, size_t n);
void	ft_parcing(char **av, char **envp);
void	ft_parcing2(char **av, char **envp);
char	*ft_check_valid_path(char *cmd, char **envp);
char	*ft_strjoin(char const *s1, char const *s2);
void	ft_first_child(char **av, char **envp, int pfd[2], int fd[2]);
void	ft_second_child(char **av, char **envp, int pfd[2], int fd[2]);

#endif