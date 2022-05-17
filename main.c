/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnoronha <pnoronha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 18:21:32 by pnoronha          #+#    #+#             */
/*   Updated: 2022/05/04 16:35:23 by pnoronha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	exit_error(int error_code)
{
	if (error_code == ARGS_NUMBER)
		perror("Wrong number of arguments");
	if (error_code == MEMORY_FAIL)
		perror("Malloc");
	if (error_code == FORK_FAIL)
		perror("Fork");
	exit(EXIT_FAILURE);
}

t_pipex	*base(void)
{
	static t_pipex	p;

	return (&p);
}

// int	child_process(int f1, int cmd1)
// {
// 	if (dup2 < 0)
// 	dup2(f1, STDIN_FILENO);
// 	dup2(end[1], cmd1);

// 	close(f1);
// 	exit(EXIT_FAILURE);
// }

// void	pipex(int f1, int f2, t_pipex *p)
// {
// 	int		end[2];
// 	pid_t	parent;

// 	pipe(end);
// 	parent = fork();
// 	if (parent < 0)
// 		exit_error(FORK_FAIL);
// 	if (!parent)
// 		child_process(f1, cmd1);
// 	else
// 		parent_process(f2, cmd2);
// }

int	main(int argc, char **argv, char **envp)
{
	if (argc != 5)
		exit_error(ARGS_NUMBER);
	parsing(argc, argv, envp);
	
	// pipex(f1, f2, base());
	return (EXIT_SUCCESS);
}
