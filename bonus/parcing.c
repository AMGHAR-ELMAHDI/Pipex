/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamghar <eamghar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 16:09:35 by eamghar           #+#    #+#             */
/*   Updated: 2023/01/20 16:37:07 by eamghar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	main(int ac, char **av, char **envp)
{
	if (ac < 5 || !envp[0])
	{
		write(2, "ERROR\n", 6);
		exit (1);
	}
	if (ft_strcmp(av[1], "here_doc") == 0)
		parcing_here_doc(ac, av, envp);
	else
		ft_parcing_bonus(ac, av, envp);
	return (0);
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
	i = -1;
	while (path[++i])
	{
		tmp = ft_strjoin(path[i], "/");
		end_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(end_path, F_OK | X_OK) == 0)
			return (end_path);
	}
	write(2, "COMMAND NOT FOUND!!!\n", 21);
	exit(1);
}

void	ft_parcing_bonus(int ac, char **av, char **envp)
{
	t_list	pipex;

	pipex.i = -1;
	pipex.cmdb = ft_calloc((ac - 2), sizeof(char *));
	pipex.pathb = ft_calloc((ac - 2), sizeof(char *));
	if (!pipex.cmdb || !pipex.pathb)
		exit(1);
	while (++pipex.i < ac - 3)
		pipex.cmdb[pipex.i] = ft_strtrim(av[2 + pipex.i], " ");
	pipex.i = -1;
	while (pipex.cmdb[++pipex.i])
		pipex.pathb[pipex.i] = ft_check_valid_path
			(ft_split(pipex.cmdb[pipex.i], ' ')[0], envp);
	pipex.fd[0] = open(av[1], O_RDONLY, 0777);
	if (pipex.fd[0] == -1)
		exit(1);
	pipex.fd[1] = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (pipex.fd[1] == -1)
		exit(1);
	pipex.i = -1;
	ft_children(&pipex, ac, envp);
}

void	ft_children(t_list *pipex, int ac, char **envp)
{
	pipex->i = -1;
	while (pipex->cmdb[++pipex->i])
	{
		if (pipex->i != ac - 4)
		{
			if (pipe(pipex->pfd) == -1)
				exit(1);
		}
		pipex->pid = fork();
		if (pipex->pid == -1)
			exit(1);
		if (pipex->pid == 0)
			ft_children2(pipex, ac, envp);
		dup2(pipex->pfd[0], 0);
		close(pipex->pfd[1]);
		close(pipex->pfd[0]);
		wait(NULL);
	}
}

void	ft_children2(t_list *pipex, int ac, char **envp)
{
	if (pipex->i == 0)
		dup2(pipex->fd[0], 0);
	if (pipex->i == ac - 4)
	{
		if (dup2(pipex->fd[1], 1) == -1)
			exit(1);
	}
	else
	{
		if (dup2(pipex->pfd[1], 1) == -1)
			exit(1);
	}
	close(pipex->pfd[1]);
	close(pipex->pfd[0]);
	execve(pipex->pathb[pipex->i], ft_split
		(pipex->cmdb[pipex->i], ' '), envp);
}
