/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrudge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 17:45:25 by mrudge            #+#    #+#             */
/*   Updated: 2022/01/12 18:30:39 by mrudge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	char			*value;
	int				is_blank;
	struct s_env	*next;
}				t_env;

typedef struct s_redirect
{
	char	*type;
	char	*file;
	int		number_command;
	struct	s_redirect	*next;
}				t_redirect;

typedef	struct	s_struct
{
	t_env	*my_env;
	char	**trim_env;
	char	**arr_env;
	int		echo_flag;
	int		revert_flag;
	int		count;
	char	*point_r;
	char	*point_f;
	t_redirect	*redirect;
	int		error;
	int		error_code;
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
int		builtin_echo(char **str, t_struct *p);
int		builtin_env(t_struct *p);
char	*get_env_var(char *str, t_struct *p);

void	build_exit(char **str, t_struct *p);
void	free_list(t_struct *p);
void	clean_split_tmp(char **clean);

char	**write_in_2_dim(char *command,char **commands);
int  	env_len(char **env);
void	ft_free(char **commands);
char	*ft_realloc_ch(char *command, char ch);
char	*parse_revert(char *array, int i, t_struct *p);
int		parse_cmd(char *line, t_struct *p);
char	*parse_double_revert(char *command, char *line, int i, t_struct *p);
char	*write_in_arr(char *line, char *command, int i, t_struct *p);
char	**parse_pipe(char *line, t_struct *p);
void	printr(char **commands);
char	**parse_redirect(char **commands, t_struct *p);
void	add_to_list_redirect(t_struct *p, char *type, char *file, int num);
char	*parse_revert(char *array, int i, t_struct *p);
char	*parse_dollar_with_quote(char *array, t_struct *p);
char	*parse_dollar_without_quote(char *array, t_struct *p);
void	print_list(t_struct *p);
char	**parse_strings(char **commands, t_struct *p);

char	*trim_and_find(char *array, int i, t_struct *p);
void	trim_env(t_struct *p);
int		check_ones(char *array, int flag);
char	*find_end_dollar(char *end);
int		end_of_quote(char *array, int i);
char    **ft_split_quotes(char const *s, char c);
char	*concat_and_free(char *first, char *second);


int		correct_check(t_struct *p);
int	check_string(char *array, t_struct *p);
void	freed(t_struct *p);


#endif