/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamghar <eamghar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 16:09:35 by eamghar           #+#    #+#             */
/*   Updated: 2023/01/18 17:58:42 by eamghar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	main(int ac, char **av, char **envp)
{
	if (ac != 5 || !envp[0])
	{
		write(2, "ERROR\n", 6);
		exit (1);
	}
	ft_parcing(av, envp);
	return (0);
}

void	ft_parcing(char **av, char **envp)
{
	t_list	pipex;

	pipex.cmd1 = ft_split(av[2], ' ');
	if (!pipex.cmd1)
		exit(1);
	pipex.cmd2 = ft_split(av[3], ' ');
	if (!pipex.cmd2)
		exit(1);
	pipex.path1 = ft_check_valid_path(pipex.cmd1[0], envp);
	pipex.path2 = ft_check_valid_path(pipex.cmd2[0], envp);
	if (pipe(pipex.pfd) == -1)
		exit(1);
	first_child(av, envp, &pipex);
	second_child(av, envp, &pipex);
	close(pipex.pfd[0]);
	close(pipex.pfd[1]);
	close(pipex.fd[0]);
	close(pipex.fd[1]);
}

void	first_child(char **av, char **envp, t_list *pipex)
{
	int		pid1;

	if (!pipex->cmd1[0] || !pipex->path1)
		exit(1);
	pipex->fd[0] = open(av[1], O_RDONLY, 0777);
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

void	second_child(char **av, char **envp, t_list *pipex)
{
	int	pid2;

	if (!pipex->cmd2[0] || !pipex->path2)
		exit(1);
	pipex->fd[1] = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 0777);
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

char	*ft_check_valid_path(char *cmd, char **envp)
{
	char	**path;
	char	*end_path;
	char	*tmp;
	int		i;

	i = 0;
	while (ft_strnstr(envp[i], "PATH=", 5) == 0)
		i++;
	path = ft_split(envp[i] + 5, ':');
	if (!path)
		exit(0);
	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		end_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(end_path, F_OK | X_OK) == 0)
			return (end_path);
		i++;
	}
	write(2, "COMMAND NOT FOUND!!!\n", 21);
	exit(1);
}
