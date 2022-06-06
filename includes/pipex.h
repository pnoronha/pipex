/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnoronha <pnoronha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 18:22:16 by pnoronha          #+#    #+#             */
/*   Updated: 2022/06/06 21:36:07 by pnoronha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <fcntl.h>
# include "libft.h"

enum	e_boolean
{
	false,
	true
};

typedef struct s_pipex
{
	char	**args;
	char	**path;
	char	**cmd1;
	char	**cmd2;
	int		file_in;
	int		file_out;
	int		fd[2];

}	t_pipex;

t_pipex	*ppx(void);

void	parsing(int argc, char **argv, char **envp);
void	pipex(t_pipex *p);
void	free_pipex(void);
void	exit_error(char *error_msg);

#endif
