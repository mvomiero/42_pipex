/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 15:37:10 by mvomiero          #+#    #+#             */
/*   Updated: 2023/02/13 18:43:25 by mvomiero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// fd [0] ---> STDIN  ---> here is read
// fd [1] ---> STDOUT ---> here is written

// *** CHILD
// create a int fd for infile and open it
// 		fd opening protection
// dup2 -> we set fd[1] as STDOUT (so in the same time we close fd[1])
// 		doesen't need to output (read) here, so we can close it
//		so redirects the STDOUT to our current pipe
// dup2 -> we set fd infile as STDIN
// 		so the pipe reads from the file we have
// close fd[0] (was still open)
//		once you read, you can close it
// execute function

void	child_process(char **argv, char **envp, int *fd)
{
	int	infile;

	infile = open(argv[1], O_RDONLY, 0777);
	if (infile == -1)
		error();
	dup2(fd[1], STDOUT_FILENO);
	dup2(infile, STDIN_FILENO);
	close(fd[0]);
	execute(argv[2], envp);
}

void	parent_process(char **argv, char **envp, int *fd)
{
	int	outfile;

	outfile = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (outfile == -1)
		error();
	dup2(fd[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close(fd[1]);
	execute(argv[3], envp);
}

// *** PARENT
// create a int fd for outfile and open it
// 		fd opening protection
// dup2 -> we set fd[0] as STDIN (so in the same time we close fd[0])
// 		doesen't need to input (write) here, so we can close it
// dup2 -> we set fd infile as STDOUT
// 		so the pipe writes from the file we have
// close fd[0] (was still open)
//		once you read, you can close it
// execute function

// in open() -> O_TRUNC is meant to truncate the file if already eisting

// ***** MAIN

// declare fd, declare pid
// condition 5 argc
// call pipe on fd
// assign pid = fork()
// call child_process on pid=0
// wait for child process
// execute parent process


int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid1;
	
		//printf("completed\n");
	if (argc == 5)
	{
		//printf("ciao\n");
		if (pipe(fd) == -1)
			error();
		//printf("pipe done\n");
		pid1 = fork();
		if (pid1 == -1)
			error();
		if (pid1 == 0)
			child_process(argv, envp, fd);
		waitpid(pid1, NULL, 0);
		//printf("chil process done\n");
			parent_process(argv, envp, fd);
		//printf("parent process done\n");
	}
	// still have to do the else statement
}

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