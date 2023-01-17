/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamghar <eamghar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 16:09:35 by eamghar           #+#    #+#             */
/*   Updated: 2023/01/17 23:44:15 by eamghar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	main(int ac, char **av, char **envp)
{
	if (ac != 5 || !envp)
	{
		write(2, "ERROR\n", 6);
		return (0);
	}
	ft_parcing(av, envp);
	return(0);
}

void	ft_parcing(char **av, char **envp)
{
	char	**cmd1;
	char	**cmd2;
	char	*path_cmd1;
	char	*path_cmd2;
	int		pfd[2];
	int		fd[2];
	int		pid1;
	int		pid2;

	cmd1 = ft_split(av[2], ' ');
	if (!cmd1)
		exit(1);
	cmd2 = ft_split(av[3], ' ');
	if (!cmd2)
		exit(1);
	path_cmd1 = ft_check_valid_path(cmd1[0], envp);
	path_cmd2 = ft_check_valid_path(cmd2[0], envp);
   	if (pipe(pfd) == -1)
        exit(1);
    first_child(&av[1], envp, &pfd[0], &fd[0], path_cmd1, cmd1);
    second_child(&av[4], envp, &pfd[1], &fd[1], path_cmd2, cmd2);
    close(pfd[0]);
    close(pfd[1]);
    close(fd[0]);
    close(fd[1]);
    waitpid(-1, NULL, 0);
    waitpid(-1, NULL, 0);
}

void    first_child(char **argv, char **envp, int pfd[2], int fd[2], char *path1, char **cmd1)
{
    int     pid1;

    pfd[0] = open(argv[1], O_RDONLY);
	if(pfd[0] == -1)
	{
		write(2, "OPEN ERROR\n", 11);
		exit(1);
	}
    pid1 = fork();
    if (pid1 == -1)
        exit(1);
    if (pid1 == 0)
    {
        dup2(fd[1], STDOUT_FILENO);
        dup2(pfd[0], STDIN_FILENO);
        close(pfd[0]);
        close(fd[1]);
        execve(path1, cmd1, envp);
    }
}

void    second_child(char **argv, char **envp, int pfd[2], int fd[2], char *path2, char **cmd2)
{
    int     pid2;

    pfd[1] = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if(pfd[1] == -1)
	{
		write(2, "OPEN ERROR\n", 11);
		exit(1);
	}
    pid2 = fork();
    if (pid2 == -1)
        exit(1);
    if (pid2 == 0)
    {
        dup2(fd[0], STDIN_FILENO);
        dup2(pfd[1], STDOUT_FILENO);
        close(pfd[1]);
        close(fd[0]);
        execve(path2, cmd2, envp);
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
