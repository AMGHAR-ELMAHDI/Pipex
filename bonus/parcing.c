/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamghar <eamghar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 16:09:35 by eamghar           #+#    #+#             */
/*   Updated: 2023/01/19 12:37:45 by eamghar          ###   ########.fr       */
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
	ft_parcing_bonus(ac, av, envp);
	return (0);
}

void	ft_parcing_bonus(int ac, char **av, char **envp)
{
	t_list	pipex;

	pipex.i = -1;
	pipex.cmdb = ft_calloc((ac - 2) , sizeof(char *));
	pipex.pathb = ft_calloc((ac - 2) , sizeof(char *));
	if(!pipex.cmdb || !pipex.pathb)
		exit(1);
	while(++pipex.i < ac - 3)
		pipex.cmdb[pipex.i] = ft_strtrim(av[2 + pipex.i], " ");
	pipex.i = -1;
	while(pipex.cmdb[++pipex.i])
		pipex.pathb[pipex.i] = ft_check_valid_path(pipex.cmdb[pipex.i], envp);
	pipex.fd[0] = open(av[1], O_RDONLY, 0777);
	if (pipex.fd[0] == -1)
		exit(1);
	pipex.fd[1] = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (pipex.fd[1] == -1)
		exit(1);
	pipex.i = -1;
	while(pipex.cmdb[++pipex.i])
	{
		if(pipex.i != ac - 4)
		{
			if (pipe(pipex.pfd) == -1)
				exit(1);
		}
		if((pipex.pid = fork()) == -1)
			exit(1);
		if(pipex.i == 0)
		{
			if (dup2(pipex.fd[0], 0) == -1)
				exit(1);
			if(pipex.i != ac -4)
			{
				if (dup2(pipex.pfd[1], 1) == -1)
					exit(1);
			}
			else
			{
				if (dup2(pipex.fd[1], 1) == -1)
					exit(1);
			}
			close(pipex.fd[1]);
			close(pipex.fd[0]);
			if (execve(pipex.pathb[pipex.i], &pipex.cmdb[pipex.i], envp) == -1)
				exit(1);
		}
	}
}

void	if_child(t_ppx ppx, int ac, char **env)
{
	if (ppx.id == 0)
	{
		if (ppx.i == 0)
			dup2(ppx.fd1, 0);
		if (ppx.i == ac - 4)
			dup2(ppx.fd2, 1);
		else
			dup2(ppx.fd[1], 1);
		close(ppx.fd[1]);
		close(ppx.fd[0]);
		execve(ppx.exe[ppx.i], ft_split(ppx.cmds[ppx.i], ' '), env);
	}
}

void	exe_cmds(t_ppx ppx, int ac, char **env)
{
	ppx.i = -1;
	while (++ppx.i < ac - 3)
	{
		if (ppx.i != ac - 4)
		{
			if (pipe(ppx.fd) < 0)
				ft_error();
		}
		ppx.id = fork();
		if (ppx.id < 0)
			ft_error();
		if_child(ppx, ac, env);
		dup2(ppx.fd[0], 0);
		close(ppx.fd[1]);
		close(ppx.fd[0]);
		wait(NULL);
	}
}

void	first_child_b(char **av, char **envp, t_list *pipex)
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
		if (execve(pipex->pathb[pipex->i], &pipex->cmdb[pipex->i], envp) == -1)
			exit(1);
	}
}

void	second_child_b(char **av, char **envp, t_list *pipex)
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
		if (execve(pipex->pathb[pipex->i+1], &pipex->cmdb[pipex->i+1], envp) == -1)
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


