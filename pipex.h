/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamghar <eamghar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 16:07:09 by eamghar           #+#    #+#             */
/*   Updated: 2023/01/19 12:26:42 by eamghar          ###   ########.fr       */
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

typedef struct s_list
{
	int		fd[2];
	int		pfd[2];
	int		i;
	char	**cmd1;
	char	**cmd2;
	char	**cmdb;
	char	*path1;
	char	*path2;
	char	**pathb;
	int		pid;
}				t_list;

char	**ft_split(char const *s, char c);
int		ft_strncmp(const char *s1, const char *s2);
void	*ft_calloc(size_t count, size_t size);
size_t	ft_strlen(const char *str);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
void	ft_bzero(void *s, size_t n);
void	ft_parcing(char **av, char **envp);
int		ft_parcing2(char **av, char **envp);
char	*ft_check_valid_path(char *cmd, char **envp);
char	*ft_strjoin(char const *s1, char const *s2);
void	first_child(char **av, char **envp, t_list *pipex);
void	second_child(char **av, char **envp, t_list *pipex);
//-------------bonus-------------------------
void	ft_parcing_bonus(int ac, char **av, char **envp);
char	*ft_strdup(const char *s1);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	first_child_b(char **av, char **envp, t_list *pipex);
void	second_child_b(char **av, char **envp, t_list *pipex)
;
#endif