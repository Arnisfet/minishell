/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmacmill <jmacmill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 17:45:25 by mrudge            #+#    #+#             */
/*   Updated: 2022/01/27 20:18:17 by mrudge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define BUFFER_SIZE 1

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
# include <fcntl.h>

typedef struct s_env
{
	char			*var;
	char			*value;
	int				is_blank;
	struct s_env	*next;
}				t_env;

typedef struct s_redirect
{
	char				*type;
	char				*file;
	int					number_command;
	struct s_redirect	*next;
}				t_redirect;

typedef struct s_cmd
{
	char			**cmd;
	struct s_cmd	*next;
}				t_cmd;

typedef struct s_struct
{
	t_env		*my_env;
	char		**trim_env;
	char		**arr_env;
	int			echo_flag;
	int			revert_flag;
	int			count;
	char		*point_r;
	char		*point_f;
	int			total_cmd;
	int			in_file;
	int			out_file;
	int			is_infile;
	int			is_outfile;
	int			total_pipes;
	int			here_doc;
	int			tmpin;
	int			tmpout;
	int			fdin;
	int			fdout;
	int			idx;
	int			ret;
	int			fdpipe[2];
	int			flag;
	pid_t		*pid;
	t_redirect	*redirect;
	int			error;
	int			error_code;
	char		*tmp_red;
}				t_struct;

int		g_status;

void	rl_replace_line(const char *text, int clear_undo);
void	ignore_signals(void);
void	on_chld_signals(void);
void	on_parent_signals(void);

int		get_next_line(int fd, char **line);

void	init_env(char **env, t_struct *p);
void	display_message(t_struct *p);
int		build_cd(char **str, t_struct *p);
int		input_is_empty(char *check);
char	*build_pwd(char **str);
int		find_str(const char *s1, const char *s2);
int		build_export(char **str, t_struct *p);
int		build_unset(char **str, t_struct *p);
void	init_env_list(t_struct *p, char *content);
int		builtin_echo(char **str, t_struct *p);
int		builtin_env(t_struct *p);
char	*get_env_var(char *str, t_struct *p);
char	*first_rparse(char *commands, t_struct *p);

int		make_pids(t_struct *p);
void	preparation(t_struct *p);
void	check_minishell(char **new_arr, t_struct *p);
void	minishell_wo_pipes(char **array, t_struct *p);
void	route_minishell(char **array, t_struct *p);
void	catch_file(t_struct *p, char *filename, int state);

void	check_in(t_struct *p);
void	redirect_in(t_struct *p);
void	redirect_out(t_struct *p);
void	check_out(t_struct *p);
void	child(char **commands, t_struct *p);

void	check_heredoc(t_struct *p);
int		get_outfile(t_struct *p, int pos);
int		check_outfile(t_struct *p, int pos);
char	*get_infile(t_struct *p, int pos);
int		check_infile(t_struct *p, int pos);

void	ctrl_c_parent(int status);
void	ctrl_slash_parent(int status);
void	ctrl_c_pipe_heredoc(int status);
void	ctrl_c_fork(int status);
void	ctrl_c_child(int status);
void	ctrl_slash_child(int status);
void	ctrl_c_heredoc(int status);
void	ignore_signals(void);
void	on_chld_signals(void);
void	on_parent_signals(void);
void	restore_std(t_struct *p);
void	global_wait(t_struct *p);
int		create_redir(t_struct *p);

int		build_exit(char **cmd);
void	add_null_value(char *str, t_struct *p, int flag);
int		check_var(char *str, t_struct *p);
void	blank_and_replace(char *str, t_struct *p);
void	exist_add(char *var, char *value, t_struct *p, int flag);
void	addition_var(char *var, char *value, t_struct *p, int flag);
void	free_list(t_struct *p);
void	clean_split_tmp(char **clean);
void	free_array(char **str);
int		execute(char *path, char **str, t_struct *p);
int		start_execve(char *path, char **str, t_struct *p);
int		check_execve(char **str, t_struct *p);
int		special_check(char *str);
int		execute_chld(char *path, char **str, t_struct *p);

char	**write_in_2_dim(char *command, char **commands);
void	ctrl_c_pipe_heredoc(int status);
void	ctrl_c_heredoc(int status);
int		env_len(char **env);
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
char	*ft_strtrim_quote(char *arr, char *start, char *end);
int		check_digit(char const *start, char *end, t_struct *p);
int		print_env(t_struct *p);
int		export_errors(char **str);
char	**parsing(char *line, t_struct *p, char **commands);
void	loop(char **line, t_struct *p);

char	*trim_and_find(char *array, int i, t_struct *p);
void	trim_env(t_struct *p);
int		check_ones(char *array, int flag);
char	*find_end_dollar(char *end);
int		end_of_quote(const char *array, int i);
char	**ft_split_quotes(char const *s, char c);
char	*concat_and_free(char *first, char *second);
int		create_redir(t_struct *p);
void	start_heredoc(t_struct *p, char *stop);
void	catch_file(t_struct *p, char *filename, int state);
void	choose_func(char **commands, t_struct *p);
int		check_bultin(char **str, t_struct *p);
void	clean_split_tmp(char **clean);
void	remove_spaces_in_line(char **str);

void	util(t_struct *p, char *file, char *redirect);
int		correct_check(t_struct *p);
int		check_string(char *array, t_struct *p);
void	freed(t_struct *p);
void	free2(char *array, char *trimmer);
int		substring(char *start, t_struct *p);

#endif