/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnoronha <pnoronha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 18:21:32 by pnoronha          #+#    #+#             */
/*   Updated: 2022/06/14 21:03:02 by pnoronha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_pipex	*ppx(void)
{
	static t_pipex	p;

	return (&p);
}

t_heredoc	*doc(void)
{
	static t_heredoc	doc;

	return (&doc);
}

int	main(int argc, char **argv, char **envp)
{
	parsing(argc, argv, envp);
	pipex(ppx());
	free_pipex();
	return (EXIT_SUCCESS);
}
