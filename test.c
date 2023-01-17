/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamghar <eamghar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 22:53:18 by eamghar           #+#    #+#             */
/*   Updated: 2023/01/17 23:16:25 by eamghar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}


char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ns;
	size_t	range;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	range = ft_strlen (s1) + ft_strlen (s2);
	ns = (char *)malloc(sizeof(char) * (range + 1));
	if (!ns)
		return (0);
	while (i < ft_strlen (s1))
	{
		ns[i] = s1[i];
		i++;
	}
	while (j < ft_strlen (s2))
	{
		ns[i + j] = s2[j];
		j++;
	}
	ns[i + j] = '\0';
	return (ns);
}


char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*str1;
	char	*str2;
	size_t	i;
	size_t	j;
	size_t	needle_len;

	i = 0;
	needle_len = ft_strlen(needle);
	str1 = (char *)haystack;
	str2 = (char *)needle;
	if (!*str2)
		return (str1);
	while (i < len && haystack[i])
	{
		j = 0;
		while (str1[i + j] == str2[j] && len - i >= needle_len)
		{
			if (!str2[j + 1])
				return (str1 + i);
			else
				j++;
		}
		i++;
	}
	return (NULL);
}

static	char	**error_malloc(char **tab)
{
	unsigned int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
	return (NULL);
}

static	int	word_count(const char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			i++;
		else
		{
			count++;
			while (str[i] != c && str[i])
				i++;
		}
	}
	return (count);
}

static	char	*get_word(const char *s1, int *index, char c)
{
	char	*copy;
	int		word_len;
	int		i;

	word_len = 0;
	while (s1[*index] == c)
		(*index)++;
	i = *index;
	while (s1[i] && s1[i] != c)
	{
		word_len++;
		i++;
	}
	copy = malloc(sizeof(char) * (word_len + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (s1[*index] && s1[*index] != c)
		copy[i++] = s1[(*index)++];
	copy[i] = '\0';
	return (copy);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		index;
	int		wc;
	int		i;

	index = 0;
	i = 0;
	if (!s)
		return (NULL);
	wc = word_count(s, c);
	arr = malloc(sizeof(char *) * (wc + 1));
	if (!arr)
		return (NULL);
	while (i < wc)
	{
		arr[i] = get_word(s, &index, c);
		if (!arr[i])
			return (error_malloc(arr));
		i++;
	}
	arr[i] = 0;
	return (arr);
}


char    *find_path(char *cmd, char **envp)
{
    char        **array_of_paths;
    char        *path_ultime;
    int         i;
    char        *temp;

    i = 0;
    while (ft_strnstr(envp[i], "PATH=", 5) == 0)
        i++;
    array_of_paths = ft_split(envp[i] + 5, ':');
    i = 0;
    while (array_of_paths[i])
    {
        temp = ft_strjoin(array_of_paths[i], "/");
        path_ultime = ft_strjoin(temp, cmd);
        free(temp);
        if (access(path_ultime, F_OK | X_OK) == 0)
            return (path_ultime);
        i++;
    }
    return (0);
}

void    ft_first_child(char **argv, char **envp, int pipefd[2], int fd[2])
{
    char    **cmd_and_options1;
    char    *path_ultime1;
    int     pid1;

    pipefd = open(argv[1], O_RDONLY);
    pid1 = fork();
    if (pid1 == -1)
        exit(1);
    if (pid1 == 0)
    {
        if(dup2(fd[1], STDOUT_FILENO) == -1)
			exit(1);
        if(dup2(pipefd, STDIN_FILENO) == -1)
			exit(1);
        close(pipefd[0]);
        close(fd[1]);
        execve(path_ultime1, cmd_and_options1, envp);
    }
}

void    ft_second_child(char **argv, char **envp, int pipefd, int fd[2])
{
    char    **cmd_and_options2;
    char    *path_ultime2;
    int     pid2;

    pipefd = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if(pipefd == -1)
		exit(1);
    pid2 = fork();
    if (pid2 == -1)
        exit(1);
    if (pid2 == 0)
    {
        if(dup2(fd[0], STDIN_FILENO) == -1)
			exit(1);
        if(dup2(pipefd, STDOUT_FILENO) == -1)
			exit(1);
        close(pipefd);
        close(fd[0]);
        execve(path_ultime2, cmd_and_options2, envp);
    }
}

int main(int argc, char *argv[], char **envp)
{
    int     pipefd[2];
    int     fd[2];
    char    **cmd_and_options1;
    char    **cmd_and_options2;
    char    *path_ultime1;
    char    *path_ultime2;

    (void)argc;
    cmd_and_options1 = ft_split(argv[2], ' ');
    cmd_and_options2 = ft_split(argv[3], ' ');
    path_ultime1 = find_path(cmd_and_options1[0], envp);
    path_ultime2 = find_path(cmd_and_options2[0], envp);
    if (pipe(fd) == -1)
        exit(1);
    ft_first_child(&argv[1], envp, pipefd[0], fd[0]);
    ft_second_child(&argv[4], envp, pipefd[1], fd[1]);
    close(pipefd[0]);
    close(pipefd[1]);
    close(fd[0]);
    close(fd[1]);
    waitpid(-1, NULL, 0);
    waitpid(-1, NULL, 0);
	printf("here\n");
    return (0);
}

