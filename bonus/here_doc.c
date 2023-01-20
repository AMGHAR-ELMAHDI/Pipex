/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamghar <eamghar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 15:40:36 by eamghar           #+#    #+#             */
/*   Updated: 2023/01/20 16:51:46 by eamghar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	parcing_here_doc(int ac, char **av, char **envp)
{
	t_list	pipex;

	if (ac != 6 || !envp[0])
	{
		write(2, "WRONG NUMBER OF ARGUMENTS\n", 26);
		exit (1);
	}
	pipex.cmd1 = ft_split(av[3], ' ');
	if (!pipex.cmd1)
		exit(1);
	pipex.cmd2 = ft_split(av[4], ' ');
	if (!pipex.cmd2)
		exit(1);
	pipex.path1 = ft_check_valid_path(pipex.cmd1[0], envp);
	pipex.path2 = ft_check_valid_path(pipex.cmd2[0], envp);
	pipex.fd[0] = open("tmp", O_CREAT | O_RDWR | O_APPEND, 0777);
	if (pipex.fd[0] == -1)
		exit(1);
	pipex.fd[1] = open(av[5], O_CREAT | O_WRONLY, 0777);
	if (pipex.fd[1] == -1)
		exit(1);
	pipex.limiter = ft_strjoin(av[2], "\n");
	pipex.s = get_next_line_get(0);
	while (ft_strcmp(pipex.s, pipex.limiter) != 0)
	{
		ft_putstr_fd(pipex.s, pipex.fd[0]);
		free(pipex.s);
		pipex.s = get_next_line_get(0);
	}
	// if (pipe(pipex.pfd) == -1)
	// 	exit(1);
	// first_child(av, envp, &pipex);
	// second_child(av, envp, &pipex);
	// close(pipex.pfd[0]);
	// close(pipex.pfd[1]);
	// close(pipex.fd[0]);
	// close(pipex.fd[1]);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (fd < 0 || !s)
		return ;
	while (s[i])
	{
		ft_putchar_fd (s[i], fd);
		i++;
	}
}

void	ft_putchar_fd(char c, int fd)
{
	write (fd, &c, 1);
}