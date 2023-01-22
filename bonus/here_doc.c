/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamghar <eamghar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 15:40:36 by eamghar           #+#    #+#             */
/*   Updated: 2023/01/22 16:32:39 by eamghar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	parcing_here_doc(int ac, char **av, char **envp)
{
	t_list	pipex;

	if (ac != 6)
	{
		write(2, "WRONG NUMBER OF ARGUMENTS\n", 26);
		exit (1);
	}
	pipex.cmd1 = ft_split(av[3], ' ');
	pipex.cmd2 = ft_split(av[4], ' ');
	if (!pipex.cmd2 || !pipex.cmd1)
		exit(1);
	pipex.path1 = ft_check_valid_path(pipex.cmd1[0], envp);
	pipex.path2 = ft_check_valid_path(pipex.cmd2[0], envp);
	parcing_here_doc2(av, envp, &pipex);
}

void	parcing_here_doc2(char **av, char **envp, t_list *pipex)
{
	int		i;

	i = 0;
	pipex->fd[0] = open("tmp", O_CREAT | O_RDWR | O_APPEND, 0777);
	if (pipex->fd[0] == -1)
		exit(1);
	pipex->limiter = ft_strjoin(av[2], "\n");
	if (!pipex->limiter)
		exit(1);
	pipex->s = get_next_line_get(0);
	while (pipex->s && ft_strcmp(pipex->s, pipex->limiter) != 0)
	{
		ft_putstr_fd(pipex->s, pipex->fd[0]);
		free(pipex->s);
		pipex->s = get_next_line_get(0);
	}
	free(pipex->s);
	if (pipe(pipex->pfd) == -1)
		exit(1);
	first_child_here_doc(envp, pipex);
	second_child_here_doc(av, envp, pipex);
	waitpid(-1, NULL, 0);
	i = 0;
	while(pipex->cmd1[i])
		free(pipex->cmd1[i++]);
	free(pipex->cmd1);
	i = 0;
	while(pipex->cmd2[i])
		free(pipex->cmd2[i++]);
	free(pipex->cmd2);
	free(pipex->limiter);
	close(pipex->pfd[0]);
	close(pipex->pfd[1]);
	free(pipex->path1);
	free(pipex->path2);
	close(pipex->fd[0]);
	close(pipex->fd[1]);
	unlink("tmp");
}

void	first_child_here_doc(char **envp, t_list *pipex)
{
	int		pid1;

	pipex->fd[0] = open("tmp", O_RDONLY | O_APPEND, 0777);
	if (pipex->fd[0] == -1)
		exit(1);
	pid1 = fork();
	if (pid1 == -1)
		exit(1);
	if (pid1 == 0)
	{
		if (dup2(pipex->fd[0], 0) == -1)
			exit(1);
		if (dup2(pipex->pfd[1], 1) == -1)
			exit(1);
		close(pipex->pfd[0]);
		close(pipex->pfd[1]);
		if (execve(pipex->path1, pipex->cmd1, envp) == -1)
			exit(1);
	}
}

void	second_child_here_doc(char **av, char **envp, t_list *pipex)
{
	int	pid2;

	pipex->fd[1] = open(av[5], O_CREAT | O_RDWR | O_APPEND, 0777);
	if (pipex->fd[1] == -1)
		exit(1);
	pid2 = fork();
	if (pid2 == -1)
		exit(1);
	if (pid2 == 0)
	{
		if (dup2(pipex->fd[1], 1) == -1)
			exit(1);
		if (dup2(pipex->pfd[0], 0) == -1)
			exit(1);
		close(pipex->pfd[0]);
		close(pipex->pfd[1]);
		if (execve(pipex->path2, pipex->cmd2, envp) == -1)
			exit(1);
	}
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
