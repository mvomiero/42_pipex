/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:50:05 by mvomiero          #+#    #+#             */
/*   Updated: 2023/02/13 17:30:45 by mvomiero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// **** FIND PATH (char *cmd, char **envp)
// iterates trough envp untile finds the string starting with "PATH" (strnstr)
// ft_splits the string starting from + 5 ("PATH="), separator is :
// once it has the array of strings with all the paths, you have for each add / 
// and the command name (cmd, passed as argument of the function)
// if you have access, you return the first path you encounter

// **** EXECUTE (char *argv, char **envp)
// stores ft_split of argv in array of strings (separator is ' ')
// stores the parth in a variable after calling the function
// if there is no path, you have to free the array of strings
// launch and protect the execve function (if -1 then is error)

// perror, access???

static void	free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
		free(paths[i++]);
	free(paths);
}

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i], '/');
		path = ft_strjoin(path, cmd);
		if (access(path, F_OK) == 0)
		{
			free_paths(paths);
			return (path);
		}
		free(path);
		i++;
	}
	free(paths);
}

