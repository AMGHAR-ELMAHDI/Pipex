/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamghar <eamghar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 16:09:35 by eamghar           #+#    #+#             */
/*   Updated: 2023/01/17 20:52:06 by eamghar          ###   ########.fr       */
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
	int		status;

	cmd1 = ft_split(av[2], ' ');
	if (!cmd1)
		exit(1);
	cmd2 = ft_split(av[3], ' ');
	if (!cmd2)
		exit(1);
	path_cmd1 = ft_check_valid_path(cmd1[0], envp);
	path_cmd2 = ft_check_valid_path(cmd2[0], envp);
	if (pipe(fd) == -1)
	{
		write(2, "PIPE ERROR\n", 11);
		exit(1);
	}
	if((pid1 = fork()) == -1)
	{
		write(2, "FORK ERROR\n", 11);
		exit(1);
	}
	else if (pid1 == 0)
	{
		fd[1] = open(av[1], O_RDONLY);
		if(pfd[0] == -1)
			exit(1);
		dup2(fd[1], STDOUT_FILENO);
		// dup2(pfd[0], STDIN_FILENO);
		close()
		execve(path_cmd1, cmd1, envp);
		write(2, "EXECVE ERROR\n", 14);
		exit(1);
}~
	if((pid2 = fork()) == -1)
	{
		write(2, "FORK ERROR\n", 11);
		exit(1);
	}
	else if(pid2 == 0)
	{
		pfd[1] = open(av[4], O_CREAT | O_WRONLY | O_TRUNC , 0777);
		if(pfd[1] == -1)
			exit(1);
		dup2(fd[0], STDIN_FILENO);
		dup2(pfd[1], STDOUT_FILENO);
		execve(path_cmd2, cmd2, envp);
		write(2, "EXECVE ERROR\n", 14);
		exit(1);
	}
	close(pfd[0]);
	close(pfd[1]);
	close(fd[0]);
	close(fd[1]);
	// waitpid(-1, &pid2, 0);
	// waitpid(-1, &pid1, 0);		

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
