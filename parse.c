/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnoronha <pnoronha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 14:07:21 by pnoronha          #+#    #+#             */
/*   Updated: 2022/05/12 14:11:25 by pnoronha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	get_path(char **envp)
{
	int		i;
	char	*env_path;

	i = 0;
	while (ft_strncmp("PATH=", envp[i], 4) && envp[i++])
	env_path = ft_substr(envp[i], 5, ft_strlen(envp[i]));
	base()->path = ft_split(env_path, ':');
	i = -1;
	while(base()->path[++i] != NULL)
		base()->path[i] = ft_strjoin(base()->path[i], "/");
}

void	get_cmds(int argc, char **argv)
{
	int		i;

	base()->cmds = malloc(sizeof(char *) * (argc - 2));
	if (!base()->cmds)
		exit_error(MEMORY_FAIL);
	i = -1;
	while (++i < argc - 3)
		base()->cmds[i] = ft_strdup(argv[i + 2]);
	base()->cmds[i] = NULL;
}

void	parse_files(char **argv)
{
	base()->file_in = open(argv[1], O_RDONLY);
	base()->file_out = open(argv[4], O_CREAT | O_RDWR | O_TRUNC | 0644);
	if (base()->file_in < 0 || base()->file_out < 0)
		exit(EXIT_FAILURE);
}

void	parsing(int argc, char **argv, char **envp)
{
	get_cmds(argc, argv);
	get_path(envp);
	parse_files(argv);
}