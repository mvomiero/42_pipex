/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 11:33:40 by mvomiero          #+#    #+#             */
/*   Updated: 2023/02/15 12:24:06 by mvomiero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	use(void)
{
	ft_putstr_fd("Error: Bad argument\n", 2);
	ft_putstr_fd("Ex: ./pipex <file1> <cmd1> <cmd2> <...> <file2>\n", 1);
	ft_putstr_fd("./pipex \"here_doc\" <LIMITER> <cmd> <cmd1> <file>\n", 1);
	exit(EXIT_SUCCESS);
}

/* during the main function this function is called iteratively.
It creates child processes, set the pipe for the parent and says to wait...
because all the new projects will be be "child of child" processes. the 
execution of the first parent project is then done in the main.
 */

static void	child_process(char *argv, char **envp)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		error();
	pid = fork();
	if (pid == -1)
		error();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		execute(argv, envp);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}

/* function to open in the right way the different files depending from the 
char flag. file protection at the end.
 */

static int	open_file(char *argv, char c)
{
	int	file;

	file = 0;
	if (c == 'a')
		file = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (c == 't')
		file = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (c == 'r')
		file = open(argv, O_RDONLY, 0777);
	if (file == -1)
		error();
	return (file);
}

/* here_doc function gets the input with get next line in the child project.
It reads it in the STDIN until it doesent find the limiter string, then writes
it to the STDOUT and with that the process is finished. Then in parent process
sets the STDIN as the pipe IN. 
 */

static void	here_doc(char *limiter, int argc)
{
	pid_t	reader;
	int		fd[2];
	char	*line;

	if (argc < 6)
		use();
	if (pipe(fd) == -1)
		error();
	reader = fork();
	if (reader == 0)
	{
		close(fd[0]);
		while (1)
		{
			line = get_next_line(STDIN_FILENO);
			if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
				exit(EXIT_SUCCESS);
			write(fd[1], line, ft_strlen(line));
		}
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		wait(NULL);
	}
}

/* main function, sets a particular condition for the "here_doc" flag that you 
can find in case of << --> you set skip one argv (i = 3), the outfile will be 
opened in the append mode ('a'), you call the here_doc function.
Else, it sets the normal opening of in- and outfile like in the mandatory part.
After that, it calls the child function ad long as argc -2 (the outfile).
 */

int	main(int argc, char **argv, char **envp)
{
	int	i;
	int	infile;
	int	outfile;

	if (argc >= 5)
	{
		if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		{
			i = 3;
			outfile = open_file(argv[argc - 1], 'a');
			here_doc(argv[2], argc);
		}
		else
		{
			i = 2;
			outfile = open_file(argv[argc - 1], 't');
			infile = open_file(argv[1], 'r');
			dup2(infile, STDIN_FILENO);
		}
		while (i < argc - 2)
			child_process(argv[i++], envp);
		dup2(outfile, STDOUT_FILENO);
		execute(argv[argc - 2], envp);
	}
	use();
}