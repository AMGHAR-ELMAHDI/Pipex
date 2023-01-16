/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamghar <eamghar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 16:09:35 by eamghar           #+#    #+#             */
/*   Updated: 2023/01/16 23:32:02 by eamghar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	main(int ac, char **av, char **envp)
{
	if (ac != 5)
	{
		write(2, "ERROR\n", 6);
		return (0);
	}
	ft_parcing(av, envp);
}

void	ft_parcing(char **av, char **envp)
{
	char	**cmd1;
	char	**cmd2;
	char	*path_cmd1;
	char	*path_cmd2;

	cmd1 = ft_split(av[2], ' ');
	if (!cmd1)
		exit(1);
	cmd2 = ft_split(av[3], ' ');
	if (!cmd2)
		exit(1);
	path_cmd1 = ft_check_valid_path(cmd1[0], envp);
	path_cmd2 = ft_check_valid_path(cmd2[0], envp);
	ft_parcing2(av, envp);
}

void	ft_parcing2(char **av, char **envp)
{
	int		pfd[2];
	int		fd[2];

	if (pipe(fd) == -1)
	{
		write(2, "ERROR\n", 21);
		exit(1);
	}
	ft_first_child(&av[1], envp, pfd[0], fd[0]);
	ft_second_child(&av[4], envp, pfd[1], fd[1]);
}

void	ft_first_child(char **av, char **envp, int pfd[2], int fd[2])
{
	pid_t	pid;
	char	**cmd1;
	char	*path1;

	pfd[0] = open(av[1], O_RDONLY);
	if(pfd[0] == -1 )
		exit(1);
	pid = fork();
	if (pid == -1)
	{
		write(2, "Fork error\n",11);
		exit(1);
	}
	else if (pid == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		dup2(pfd[0], STDOUT_FILENO);
		if(execve(path1, cmd1,envp) == -1)
			exit(1);
	}	
}

void	ft_second_child(char **av, char **envp, int pfd[2], int fd[2])
{
	pid_t	pid2;
	char	**cmd2;
	char	*path2;

	pfd[1] = open(av[4], O_CREAT | O_WRONLY | O_TRUNC);
	if(pfd[0] == -1 )
		exit(1);
	pid2 == fork();
	if(pid2 == -1)
	{
		write(2, "Fork error\n",11);
		exit(1);
	}
	else if(pid2 == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		dup2(pfd[1], STDOUT_FILENO);
		if(execve(path2, cmd2, envp) == -1)
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
