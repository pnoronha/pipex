/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnoronha <pnoronha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 14:07:21 by pnoronha          #+#    #+#             */
/*   Updated: 2022/06/14 20:43:27 by pnoronha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	join_path_to_cmds(void)
{
	char	*aux_path;
	char	*cmd;
	int		index[2];

	index[0] = -1;
	while (ppx()->cmds[++index[0]] != NULL)
	{
		index[1] = -1;
		while (ppx()->path[++index[1]] != NULL)
		{
			aux_path = ft_strjoin(ppx()->path[index[1]], "/");
			cmd = ft_strjoin(aux_path, ppx()->cmds[index[0]][0]);
			if (access(cmd, F_OK) != -1)
			{
				free(ppx()->cmds[index[0]][0]);
				ppx()->cmds[index[0]][0] = ft_strdup(cmd);
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
	int	here_doc;

	here_doc = 2 + doc()->here_doc;
	i = here_doc;
	ppx()->cmds = malloc(sizeof(char *) * (argc - here_doc));
	while (i < (argc - 1))
	{
		(ppx())->cmds[i - here_doc] = ft_split(argv[i], ' ');
		i++;
	}
	ppx()->cmds[i - here_doc] = NULL;
}

static void	check_args(int argc, char **argv)
{
	if (argc < 5)
		exit_error("Arguments number");
	if (!ft_strncmp("here_doc", argv[1], 9))
	{
		if (argc < 6)
			exit_error("Arguments number");
		doc()->here_doc = 1;
		doc()->limiter = argv[2];
	}
	else
	{
		if (argc < 5)
			exit_error("Arguments number");
		doc()->here_doc = 0;
	}
}

void	parsing(int argc, char **argv, char **envp)
{
	check_args(argc, argv);
	ppx()->envp = envp;
	ppx()->nbr_cmd = argc - 3 - doc()->here_doc;
	get_path(envp);
	get_cmds(argc, argv);
	join_path_to_cmds();
	open_files(argc, argv);
}
