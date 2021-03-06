/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnoronha <pnoronha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 14:07:21 by pnoronha          #+#    #+#             */
/*   Updated: 2022/06/14 22:33:03 by pnoronha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	join_path_to_cmds(void)
{
	char	*aux_path;
	char	*cmd;
	int		i;
	int		j;

	i = -1;
	while (ppx()->cmds[++i] != NULL)
	{
		j = -1;
		while (ppx()->path[++j] != NULL)
		{
			aux_path = ft_strjoin(ppx()->path[j], "/");
			cmd = ft_strjoin(aux_path, ppx()->cmds[i][0]);
			if (access(cmd, F_OK) != -1)
			{
				free(ppx()->cmds[i][0]);
				ppx()->cmds[i][0] = ft_strdup(cmd);
				free(aux_path);
				free(cmd);
				break ;
			}
			free(aux_path);
			free(cmd);
		}
	}
}

static void	get_path(char **envp)
{
	int	i;

	i = 0;
	while (ft_strncmp("PATH=", envp[i], 5) && envp[i])
		i++;
	(ppx()->path) = ft_split((envp[i] + 5), ':');
}

static void	get_cmds(int argc, char **argv)
{
	int	i;

	i = 2;
	ppx()->cmds = malloc(sizeof(char *) * (argc - 2));
	while (i < (argc - 1))
	{
		(ppx())->cmds[i - 2] = ft_split(argv[i], ' ');
		i++;
	}
	ppx()->cmds[i - 2] = NULL;
}

void	parsing(int argc, char **argv, char **envp)
{
	if (argc != 5)
		exit_error("Arguments number");
	ppx()->envp = envp;
	ppx()->nbr_cmd = argc - 3;
	get_path(envp);
	get_cmds(argc, argv);
	join_path_to_cmds();
	open_files(argc, argv);
}
