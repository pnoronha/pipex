/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnoronha <pnoronha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 18:07:04 by pnoronha          #+#    #+#             */
/*   Updated: 2022/06/06 22:27:46 by pnoronha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	run_command(t_pipex *p, char **cmd_arr)
{
	char	*cmd;
	char	*cmd_aux;
	int		i;

	if (cmd_arr[0][0] == '/')
	{
		if (access(cmd_arr[0], F_OK) != -1)
			execve(cmd_arr[0], cmd_arr, NULL);
		exit_error("execve > Failed to execute the command");
	}
	i = -1;
	while (p->path[++i] != NULL)
	{
		cmd_aux = ft_strjoin(p->path[i], "/");
		cmd = ft_strjoin(cmd_aux, cmd_arr[0]);
		if (access(cmd, F_OK) != -1)
			execve(cmd, cmd_arr, NULL);
		free(cmd);
	}
	exit_error("execve > Failed to execute the command");
}

static void	first_cmd(t_pipex *p)
{
	if (dup2(p->file_in, STDIN_FILENO) < 0)
		exit_error("dup2 > Failed to duplicate File Descriptor");
	if (dup2(ppx()->fd[1], STDOUT_FILENO) < 0)
		exit_error("dup2 > Failed to duplicate File Descriptor");
	close(ppx()->fd[0]);
	close(p->file_in);
	run_command(p, p->cmd1);
}

static void	exec_second(t_pipex *p)
{

	if (dup2(p->file_out, STDOUT_FILENO) < 0)
		exit_error("dup2 > Failed to duplicate File Descriptor");
	if (dup2(ppx()->fd[0], STDIN_FILENO) < 0)
		exit_error("dup2 > Failed to duplicate File Descriptor");
	close(ppx()->fd[1]);
	close(p->file_out);
	run_command(p, p->cmd2);
}

static void	second_cmd(t_pipex *p)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit_error("fork > Failed to fork the process");
	if (!pid)
		exec_second(p);
}

void	pipex(t_pipex *p)
{
	pid_t	pid;
	int		status;

	if (pipe(ppx()->fd) == -1)
		exit_error("pipe > Failed to allocate file descriptors");
	pid = fork();
	if (pid == -1)
		exit_error("fork > Failed to fork the process");
	if (!pid)
		first_cmd(p);
	waitpid(-1, &status, 0);
	second_cmd(p);
}
