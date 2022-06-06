/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnoronha <pnoronha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 14:07:21 by pnoronha          #+#    #+#             */
/*   Updated: 2022/06/06 22:29:15 by pnoronha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	get_path(char **envp)
{
	int		i;
	char	*env_path;

	i = 0;
	while (ft_strncmp("PATH=", envp[i], 5) && envp[i])
		i++;
	env_path = envp[i] + 5;
	ppx()->path = ft_split(env_path, ':');
}

void	get_cmds(char **argv)
{
	(ppx())->cmd1 = ft_split(argv[2], ' ');
	(ppx())->cmd2 = ft_split(argv[3], ' ');
}

void	parse_files(char **argv)
{
	(ppx())->file_in = open(argv[1], O_RDONLY);
	if (ppx()->file_in < 0)
	{
		close(ppx()->file_in);
		free_pipex();
		exit_error("open > Failed to open file");
	}
	(ppx())->file_out = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (ppx()->file_out < 0)
	{
		close(ppx()->file_in);
		close(ppx()->file_out);
		free_pipex();
		exit_error("open > Failed to open file");
	}
}

void	parsing(int argc, char **argv, char **envp)
{
	if (argc != 5)
		exit_error("Arguments number");
	get_path(envp);
	get_cmds(argv);
	parse_files(argv);
}

void	free_pipex(void)
{
	ft_free_dptr((void **)ppx()->path);
	ft_free_dptr((void **)ppx()->cmd1);
	ft_free_dptr((void **)ppx()->cmd2);
}
