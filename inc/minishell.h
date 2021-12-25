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

typedef struct	s_env
{
	char			*var;
	struct s_env	*next;
}				t_env;

typedef	struct	s_struct
{
	t_env	*my_env;
	char	**arr_env;
	int		echo_flag;
	char	**commands;
	int		count;
	int		double_rev_flag;
}				t_struct;

void	init_env(char **env, t_struct *p);
void	display_message(t_struct *p);
int		build_cd(char **str, t_struct *p);
int		input_is_empty(char *check);
char	*build_pwd(char **str);
int		find_str(const char *s1,const char *s2);
int		build_export(char **str, t_struct *p);
int		build_unset(char **str, t_struct *p);
void	init_env_list(t_struct *p, char *content);
int		parse_cmd(char *line, t_struct *p);
int		builtin_echo(char **str, t_struct *p);
int		builtin_env(t_struct *p);
char	*get_env_var(char *str, t_struct *p);
char	**write_in_2_dim(char *command,char **commands);
int		env_len(char **env);
void	ft_free(char **commands);
char	*ft_realloc_ch(char *command, char ch);
char	*parse_revert(char *command, char *line, int i, t_struct *p);
char	*parse_double_revert(char *command, char *line, int i, t_struct *p);
char	*dollar(char *command, char *line, int i, t_struct *p);


#endif