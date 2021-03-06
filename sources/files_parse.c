/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnoronha <pnoronha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 22:30:51 by pnoronha          #+#    #+#             */
/*   Updated: 2022/06/14 22:30:19 by pnoronha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	check_opened_files(void)
{
	if (ppx()->file_in == -1 || ppx()->file_out == -1)
	{
		if (ppx()->file_out == -1)
			close(ppx()->file_in);
		if (ppx()->file_in == -1)
			close(ppx()->file_out);
		exit_error("open");
	}
}

void	open_files(int argc, char **argv)
{
	(ppx())->file_in = open(argv[1], O_RDONLY);
	(ppx())->file_out = open(argv[argc - 1], \
		O_CREAT | O_RDWR | O_TRUNC, 0644);
	check_opened_files();
}
