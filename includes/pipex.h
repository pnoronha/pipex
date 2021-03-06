/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnoronha <pnoronha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 18:22:16 by pnoronha          #+#    #+#             */
/*   Updated: 2022/06/14 22:25:25 by pnoronha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <fcntl.h>
# include "libft.h"

typedef struct s_pipex
{
	char	**envp;
	char	**path;
	char	***cmds;
	int		nbr_cmd;
	int		file_in;
	int		file_out;
	int		fd[2];

}	t_pipex;

t_pipex		*ppx(void);

void		pipex(t_pipex *p);

void		parsing(int argc, char **argv, char **envp);
void		open_files(int argc, char **argv);

void		free_pipex(void);
void		exit_error(char *error_msg);

#endif
