//
// Created by arnisfet on 02.12.2021.
//

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <dirent.h>
# include "../libft/libft.h"
# include <stdio.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>


typedef	struct	s_struct
{
	char **arr_env;
}				t_struct;

void	init_env(char **env, t_struct *p);
void	display_message(t_struct *p);
int		build_cd(char **str, t_struct *p);
int		input_is_empty(char *check);
char	*get_env_var(char *str, t_struct *p);

#endif