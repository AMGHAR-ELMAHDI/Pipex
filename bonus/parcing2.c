/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamghar <eamghar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 17:57:05 by eamghar           #+#    #+#             */
/*   Updated: 2023/01/22 17:57:08 by eamghar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h" 

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
