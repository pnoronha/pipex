/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnoronha <pnoronha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 18:07:04 by pnoronha          #+#    #+#             */
/*   Updated: 2022/06/14 22:02:57 by pnoronha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_pipex.h"

static void	fd_switches(t_pipex *p, int iter)
{
	if (iter == 0)
	{
		if (dup2(p->file_in, STDIN_FILENO) == -1)
			exit_error("dup2");
		if (dup2(p->fd[1], STDOUT_FILENO) == -1)
			exit_error("dup2");
	}
	else if (iter == p->nbr_cmd - 1)
	{
		if (dup2(p->file_out, STDOUT_FILENO) == -1)
			exit_error("dup2");
	}
	else
	{
		if (dup2(p->fd[1], STDOUT_FILENO) == -1)
			exit_error("dup2");
	}
}

void	pipex(t_pipex *p)
{
	pid_t	pid;
	int		i;
	int		status;

	i = -1;
	while (++i < p->nbr_cmd)
	{
		if (pipe(p->fd) == -1)
			exit_error("pipe");
		pid = fork();
		if (pid == -1)
			exit_error("fork");
		if (!pid)
		{
			fd_switches(p, i);
			execve(p->cmds[i][0], p->cmds[i], p->envp);
		}
		if (dup2(p->fd[0], STDIN_FILENO) < 0)
			exit_error("dup2");
		close(p->fd[0]);
		close(p->fd[1]);
	}
	close(p->file_in);
	close(p->file_out);
	waitpid(-1, &status, 0);
}
