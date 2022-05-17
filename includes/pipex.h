/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnoronha <pnoronha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 18:22:16 by pnoronha          #+#    #+#             */
/*   Updated: 2022/05/04 16:37:03 by pnoronha         ###   ########.fr       */
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

enum	e_exit_code
{
	ARGS_NUMBER,
	MEMORY_FAIL,
	FORK_FAIL,
	BUFF_NOT_SET,
	BUFF_ADDR_NOT_SET
};

typedef struct s_pipex
{
	char	**args;
	char	**path;
	char	**cmds;
	int		file_in;
	int		file_out;

}	t_pipex;

t_pipex	*base(void);

void	pipex(int f1, int f2, t_pipex *p);

void	parsing(int argc, char **argv, char **envp);

int		exit_error(int error_code);

#endif
