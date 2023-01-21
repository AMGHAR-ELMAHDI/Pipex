/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamghar <eamghar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 16:07:09 by eamghar           #+#    #+#             */
/*   Updated: 2023/01/20 23:46:28 by eamghar          ###   ########.fr       */
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

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

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
	char	*limiter;
	int		pid;
	char	*s;
}				t_list;

char	**ft_split(char const *s, char c);
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
//-------------bonus multiple pipes-------------------------
void	ft_parcing_bonus(int ac, char **av, char **envp);
char	*ft_strdup(const char *s1);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	first_child_b(char **av, char **envp, t_list *pipex);
void	second_child_b(char **av, char **envp, t_list *pipex);
void	ft_children(t_list *pipex, int ac, char **envp);
void	ft_children2(t_list *pipex, int ac, char **envp);
//--------------bonus here_doc-------------------------------
void	parcing_here_doc(int ac, char **av, char **envp);
char	*get_next_line_get(int fd);
char	*ft_read_str_get(int fd, char *str_left);
size_t	ft_strlen_get(char *s);
char	*ft_strchr_get(char *s, int cc);
char	*ft_strjoin_get(char *str_left, char *buff);
char	*ft_get_line_get(char *str_left);
char	*ft_new_str_left_get(char *str_left);
int		ft_strcmp(char *s1, char *s2);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
void	first_child_here_doc(char **envp, t_list *pipex);
void	second_child_here_doc(char **av, char **envp, t_list *pipex);
#endif