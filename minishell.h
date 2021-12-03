//
// Created by arnisfet on 02.12.2021.
//

#ifndef MINISHELL_MINISHELL_H
# define MINISHELL_MINISHELL_H

# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <dirent.h>
# include "libft/libft.h"
# include <stdio.h>

typedef	struct	s_struct
{
	char **arr_env;
}				t_struct;

void  init_env(char **env, t_struct *p);
void  display_message(t_struct *p);

#endif