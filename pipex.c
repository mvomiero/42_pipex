/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 15:37:10 by mvomiero          #+#    #+#             */
/*   Updated: 2023/02/12 18:42:52 by mvomiero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// fd [0] ---> STDIN  ---> here is read
// fd [1] ---> STDOUT ---> here is written

// *** CHILD
// create a fd for infile and open it
// 		fd opening protection
// dup2 -> we set fd[1] as STDOUT (so in the same time we close fd[1])
// 		doesen't need to output (read) here, so we can close it
//		so redirects the STDOUT to our current pipe
// dup2 -> we set fd infile as STDIN
// 		so the pipe reads from the file we have
// close fd[0] (was still open)
//		once you read, you can close it
// execute function

// *** PARENT
// create a fd for outfile and open it
// 		fd opening protection
// dup2 -> we set fd[0] as STDIN (so in the same time we close fd[0])
// 		doesen't need to input (write) here, so we can close it
// dup2 -> we set fd infile as STDOUT
// 		so the pipe writes from the file we have
// close fd[0] (was still open)
//		once you read, you can close it
// execute function

// ***** MAIN

// declare fd, declare pid
// condition 5 argc
// call pipe on fd
// assign pid = fork()
// call child_process on pid=0
// wait for child process
// execute parent process

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

// perrror, access???