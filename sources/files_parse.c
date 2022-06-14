/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnoronha <pnoronha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 22:30:51 by pnoronha          #+#    #+#             */
/*   Updated: 2022/06/14 21:00:26 by pnoronha         ###   ########.fr       */
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

static void	get_input(int file)
{
	char	*buff;
	char	*temp;
	int		i;

	while (1)
	{
		i = 0;
		while (++i < ppx()->nbr_cmd)
			write(1, "pipe ", 6);
		write(1, "heredoc> ", 10);
		get_next_line(STDIN_FILENO, &buff);
		if (buff)
		{
			if (!ft_strncmp(buff, doc()->limiter, ft_strlen(buff) + 1))
				break ;
			temp = ft_strjoin(buff, "\n");
			write(file, temp, ft_strlen(temp));
			free(buff);
			free(temp);
		}
	}
	free(buff);
}

void	open_files(int argc, char **argv)
{
	int	file;

	if (!doc()->here_doc)
	{
		(ppx())->file_in = open(argv[1], O_RDONLY);
		(ppx())->file_out = open(argv[argc - 1], \
			O_CREAT | O_RDWR | O_TRUNC, 0644);
	}
	else
	{
		file = open(".infile_tmp", O_CREAT | O_RDWR | O_TRUNC, 0644);
		get_input(file);
		close(file);
		(ppx())->file_in = open(".infile_tmp", O_RDONLY);
		(ppx())->file_out = open(argv[argc - 1], \
			O_CREAT | O_RDWR | O_APPEND, 0644);
	}
	check_opened_files();
}
