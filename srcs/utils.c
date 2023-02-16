/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:50:05 by mvomiero          #+#    #+#             */
/*   Updated: 2023/02/16 16:58:27 by mvomiero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

// frees an array of strings

static void	free_array_strings(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

// **** FIND PATH (char *cmd, char **envp)
// iterates trough envp untile finds the string starting with "PATH" (strnstr)
// ft_splits the string starting from + 5 ("PATH="), separator is :
// once it has the array of strings with all the paths, you have for each add / 
// and the command name (cmd, passed as argument of the function)
// if you have access, you return the first path you encounter

/* char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	
	for (int i = 0; paths[i]; i++)
		printf("\n%s\n\n", paths[i]);
	//char ** prova = ft_split("ciao marco come va", ' ');
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(path, cmd);
		if (access(path, F_OK) == 0)
		{
			free_array_strings(paths);
			return (path);
		}
		free(path);
		i++;
	}
	free_array_strings(paths);
	//free(paths);
	return (0);
} */

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (0);
}

void	error(void)
{
	perror("Error");
	exit(EXIT_FAILURE);
}

// emulates the behavior of bash for command not found

static void	cmd_not_found(char **cmd)
{
	if (cmd[0])
	{
		write(2, cmd[0], ft_strlen(cmd[0]));
		write(2, ": command not found\n", 20);
	}
	free_array_strings(cmd);
	exit(EXIT_FAILURE);
}

// **** EXECUTE (char *argv, char **envp)
// stores ft_split of argv in array of strings (separator is ' ')
// stores the parth in a variable after calling the function
// if there is no path, you have to free the array of strings
// launch and protect the execve function (if -1 then is error)

void	execute(char *argv, char **envp)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(argv, ' ');
	if (!cmd[0])
		cmd_not_found(cmd);
	path = find_path(cmd[0], envp);
	if (!path)
	{
		free(path);
		cmd_not_found(cmd);
	}
	if (execve(path, cmd, envp) == -1)
	{
		free(path);
		error();
	}
}
