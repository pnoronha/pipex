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

t_pipex	*base(void)
{
	static t_pipex	p;

	return (&p);
}

static void	child_process(t_pipex *p)
{
	char	*cmd;
	int		i;

	if (dup2(p->file_in, STDIN_FILENO) < 0)
		perror("dup2");
	if (dup2(p->end[1], STDOUT_FILENO) < 0)
		perror("dup2");
	close (p->end[0]);
	close (p->file_in);
	i = -1;
	while (base()->path[++i] != NULL)
	{
		cmd = ft_strjoin(base()->path[i], base()->cmd1[0]);
		printf("%s\n", cmd);
		execve(cmd, p->cmd1, NULL);
		free(cmd);
	}
	exit(EXIT_FAILURE);
}

static void	parent_process(t_pipex *p)
{
	char	*cmd;
	int		status;
	int		i;

	waitpid(-1, &status, 0);
	if (dup2(p->file_out, STDOUT_FILENO) < 0)
		perror("dup2");
	if (dup2(p->end[0], STDIN_FILENO) < 0)
		perror("dup2");
	close (p->end[1]);
	close (p->file_out);
	i = -1;
	while (base()->path[++i])
	{
		cmd = ft_strjoin(base()->path[i], base()->cmd2[0]);
		// printf("%s\n", cmd);
		execve(cmd, p->cmd2, NULL);
		free(cmd);
	}
	exit(EXIT_FAILURE);
}

static void	pipex(t_pipex *p)
{
	pid_t	pid;

	if(pipe(base()->end) == -1)
		perror("Pipe");
	pid = fork();
	if (pid == -1)
		perror("Fork");
	if (!pid)
		child_process(p);
	else
		parent_process(p);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc != 5)
	{
		perror("Args number");
		exit(EXIT_FAILURE);
	}
	parsing(argv, envp);
	pipex(base());
	return (EXIT_SUCCESS);
}
