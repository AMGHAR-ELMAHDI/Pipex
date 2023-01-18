/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamghar <eamghar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 16:09:35 by eamghar           #+#    #+#             */
/*   Updated: 2023/01/18 21:44:48 by eamghar          ###   ########.fr       */
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

	pipex.i = 0;
	pipex.cmd = ft_calloc((ac - 2) , sizeof(char *));
	if(!pipex.cmd)
		exit(1);
	while(pipex.i < ac - 3)
	{
		pipex.cmd[pipex.i] = ft_strtrim(av[2 + pipex.i], " ");
		pipex.i++;
	}
	// pipex.path1 = ft_check_valid_path(pipex.cmd[0], envp);
	// if (pipe(pipex.pfd) == -1)
	// 	exit(1);
	// first_child(av, envp, &pipex);
	// second_child(av, envp, &pipex);
	// close(pipex.pfd[0]);
	// close(pipex.pfd[1]);
	// close(pipex.fd[0]);
	// close(pipex.fd[1]);
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
