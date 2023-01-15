/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamghar <eamghar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 16:09:35 by eamghar           #+#    #+#             */
/*   Updated: 2023/01/15 22:52:32 by eamghar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int main(int ac, char **av, char **envp)
{
    if(ac != 5)
    {
        write(1,"ERROR\n",6);
        return(0);
    }
    ft_parcing(av, envp);
}

void    ft_parcing(char **av, char **envp)
{
    int     pfd[2];
    char    **cmd1;
    char    **cmd2;
    char    *path_cmd1;
    char    *path_cmd2;
    int     i;
    
    i = 0;
    cmd1 = ft_split(av[2], ' ');
    if(!cmd1)
        exit(0);
    cmd2 = ft_split(av[3], ' ');
    if(!cmd2)
        exit(0);
    path_cmd1 = ft_check_valid_path(cmd1, envp);
    path_cmd2 = ft_check_valid_path(cmd1, envp);
    
}

char    *ft_check_valid_path(char **cmd, char **envp)
{
    char    **path;
    char    *end_path;
    char    *tmp;
    int     i;

    i = 0;
    while(ft_strnstr(envp[i], "PATH=", 5) == 0)
        i++;
    path = ft_split(envp[i] + 5, ':');
    if(!path)
        exit(0);
    i = 0;
    while(path[i])
    {
        tmp = ft_strjoin(path[i], "/");
        end_path = ft_strjoin(tmp, cmd);
        free(tmp);
        if(access(end_path, F_OK | X_OK) == 0)
            return(end_path);
        i++;
    }
    return(0);
}
