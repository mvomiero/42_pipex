/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 15:37:10 by mvomiero          #+#    #+#             */
/*   Updated: 2023/02/15 12:29:03 by mvomiero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

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
	{
		perror(argv[1]);
		exit(EXIT_FAILURE);
	}
	dup2(fd[1], STDOUT_FILENO);
	dup2(infile, STDIN_FILENO);
	close(fd[0]);
	execute(argv[2], envp);
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

	if (argc == 5)
	{
		if (pipe(fd) == -1)
			error();
		pid1 = fork();
		if (pid1 == -1)
			error();
		if (pid1 == 0)
			child_process(argv, envp, fd);
		waitpid(pid1, NULL, 0);
			parent_process(argv, envp, fd);
	}
	else
	{
		ft_putstr_fd("Error: Bad arguments\n", 2);
		ft_putstr_fd("Ex: ./pipex <file1> <cmd1> <cmd2> <file2>\n", 1);
	}
	return (0);
}
