/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnoronha <pnoronha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 21:03:25 by pnoronha          #+#    #+#             */
/*   Updated: 2022/06/14 22:08:38 by pnoronha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_pipex(void)
{
	int	i;

	if (ppx())
	{
		if (ppx()->path)
			ft_free_dptr((void **)ppx()->path);
		if (ppx()->cmds)
		{
			i = -1;
			while (ppx()->cmds[++i] != NULL)
				ft_free_dptr((void **)ppx()->cmds[i]);
			free(ppx()->cmds);
		}
	}
}

void	exit_error(char *error_msg)
{
	free_pipex();
	perror(error_msg);
	exit(EXIT_FAILURE);
}
