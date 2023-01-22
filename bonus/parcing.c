/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamghar <eamghar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 16:09:35 by eamghar           #+#    #+#             */
/*   Updated: 2023/01/22 17:20:22 by eamghar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	main(int ac, char **av, char **envp)
{
	int		i;
	int		cond;

	i = 0;
	cond = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH", 4))
			cond = 1;
		i++;
	}
	if (ac < 5 || !envp[0] || cond == 0)
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
	char	*ret;
	int		i;

	i = 0;
	tmp = NULL;
	end_path = NULL;
	while (ft_strnstr(envp[i], "PATH=", 5) == 0)
		i++;
	path = ft_split(envp[i] + 5, ':');
	if (!path)
		exit(0);
	ret = ft_free(path, tmp, end_path, cmd);
	if (!ret)
	{
		write(2, "COMMAND NOT FOUND!!!\n", 21);
		exit(1);
	}
	else
		return (ret);
}

char	*ft_free(char **path, char *tmp, char *end_path, char *cmd)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		end_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(end_path, F_OK | X_OK) == 0)
		{
			while (path[j])
				free(path[j++]);
			free(path);
			return (end_path);
		}
		free(end_path);
		i++;
	}
	return (NULL);
}

void	ft_parcing_bonus(int ac, char **av, char **envp)
{
	t_list	pipex;
	char	**tmp;
	int		i;

	pipex.i = -1;
	pipex.cmdb = ft_calloc((ac - 2), sizeof(char *));
	pipex.pathb = ft_calloc((ac - 2), sizeof(char *));
	if (!pipex.cmdb || !pipex.pathb)
		exit(1);
	while (++pipex.i < ac - 3)
		pipex.cmdb[pipex.i] = ft_strtrim(av[2 + pipex.i], " ");
	pipex.i = -1;
	while (pipex.cmdb[++pipex.i])
	{
		tmp = ft_split(pipex.cmdb[pipex.i], ' ');
		pipex.pathb[pipex.i] = ft_check_valid_path(tmp[0], envp);
		i = 0;
		while (tmp[i])
			free(tmp[i++]);
		free(tmp);
	}
	pipex.fd[0] = open(av[1], O_RDONLY, 0777);
	if (pipex.fd[0] == -1)
		exit(1);
	ft_children(&pipex, ac, av, envp);
}

void	ft_children(t_list *pipex, int ac, char **av, char **envp)
{	
	pipex->fd[1] = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (pipex->fd[1] == -1)
		exit(1);
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
		if (dup2(pipex->pfd[0], 0) == -1)
			exit(1);
		close(pipex->pfd[1]);
		close(pipex->pfd[0]);
		wait(NULL);
	}
	ft_children3(pipex);
}

void	ft_children3(t_list *pipex)
{
	pipex->i = 0;
	while (pipex->cmdb[pipex->i])
		free(pipex->cmdb[pipex->i++]);
	free(pipex->cmdb);
	pipex->i = 0;
	while (pipex->pathb[pipex->i])
		free(pipex->pathb[pipex->i++]);
	free(pipex->pathb);
	close(pipex->pfd[0]);
	close(pipex->pfd[1]);
	close(pipex->fd[0]);
	close(pipex->fd[1]);
}
void	ft_children2(t_list *pipex, int ac, char **envp)
{
	if (pipex->i == 0)
	{
		if (dup2(pipex->fd[0], 0) == -1)
			exit(1);
	}
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
	if (execve(pipex->pathb[pipex->i], ft_split
			(pipex->cmdb[pipex->i], ' '), envp) == -1)
		exit(1);
}
