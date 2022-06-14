/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnoronha <pnoronha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 21:03:25 by pnoronha          #+#    #+#             */
/*   Updated: 2022/06/14 22:02:48 by pnoronha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_pipex.h"

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
	if (doc())
	{
		if (doc()->here_input)
			free(doc()->here_input);
		if (doc()->here_doc)
			unlink(".infile_tmp");
	}
}

void	exit_error(char *error_msg)
{
	free_pipex();
	perror(error_msg);
	exit(EXIT_FAILURE);
}
