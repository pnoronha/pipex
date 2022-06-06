/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnoronha <pnoronha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 18:21:32 by pnoronha          #+#    #+#             */
/*   Updated: 2022/06/06 20:44:19 by pnoronha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_pipex	*ppx(void)
{
	static t_pipex	p;

	return (&p);
}

void	exit_error(char *error_msg)
{
	perror(error_msg);
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv, char **envp)
{
	parsing(argc, argv, envp);
	pipex(ppx());
	free_pipex();
	return (EXIT_SUCCESS);
}
