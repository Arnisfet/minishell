/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmacmill <jmacmill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 17:57:10 by mrudge            #+#    #+#             */
/*   Updated: 2022/01/23 11:13:17 by jmacmill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_array(char **str)
{
	int	i;

	if (str)
	{
		i = 0;
		while (str[i])
		{
			free(str[i]);
			i++;
		}
		free(str);
	}
}

int	check_bultin(char **str, t_struct *p)
{
	if (find_str(str[0], "cd"))
		return (build_cd(str, p));
	if (find_str(str[0], "pwd"))
	{
		build_pwd(str);
		return (1);
	}
	if (find_str(str[0], "echo"))
	{
		if (builtin_echo(str + 1, p))
			return (1);
	}
	if (find_str(str[0], "env"))
		return (builtin_env(p));
	if (find_str(str[0], "unset"))
		return (build_unset(str, p));
	if (find_str(str[0], "export"))
		return (build_export(str, p));
	if (find_str(str[0], "exit"))
	{
		build_exit(str, p);
		return (-1);
	}
	return (0);
}

void	unlink_file_err(void)
{
	unlink(".heredoc_tmp");
	ft_putendl_fd("Error: unable to open a file", 2);
}

void	act_signals(void)
{
	signal(SIGINT, ctrl_c_heredoc);
	signal(SIGQUIT, ctrl_slash_child);
}

void	start_heredoc(t_struct *p, char *stop)
{
	int			file;
	char		*buf;
	pid_t		pid;

	file = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_APPEND, 0000644);
	pid = fork();
	if (pid == 0)
	{
		act_signals();
		while (21)
		{
			write(1, "heredoc> ", 9);
			if (get_next_line(0, &buf) < 0)
				exit(1);
			if (!ft_strncmp(stop, buf, ft_strlen(stop) + 1))
				exit(1);
			write(file, buf, ft_strlen(buf));
			write(file, "\n", 1);
			free(buf);
		}
		free(buf);
	}
	else
		waitpid(pid, NULL, 0);
	close(file);
	p->in_file = open(".heredoc_tmp", O_RDONLY);
	if (p->in_file < 0)
		unlink_file_err();
}

char	*get_file(t_struct *p, char *symbol)
{
	t_redirect	*tmp;

	tmp = p->redirect;
	while (tmp)
	{
		if (!ft_strncmp(symbol, tmp->type, 2))
			return (tmp->file);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*get_infile(t_struct *p, int pos)
{
	t_redirect	*tmp;
	char		*filename;
	int			flag;

	filename = NULL;
	tmp = p->redirect;
	flag = 0;
	while (tmp != NULL)
	{
		if (!ft_strncmp("<<", tmp->type, 3) && \
		tmp->number_command == pos && g_status != 130)
		{
			if (!access(".heredoc_tmp", F_OK))
				unlink(".heredoc_tmp");
			start_heredoc(p, tmp->file);
			flag = 1;
		}
		if (!ft_strncmp("<", tmp->type, 2) && tmp->number_command == pos)
		{
			filename = tmp->file;
			flag = 2;
		}
		tmp = tmp->next;
	}
	if (flag == 1)
		filename = ".heredoc_tmp";
	return (filename);
}

void	catch_file(t_struct *p, char *filename, int state)
{
	if (p->flag)
	{
		close(p->out_file);
		p->flag = 0;
	}
	p->flag++;
	if (state == 1)
	{
		p->out_file = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (p->out_file == -1)
			perror("minishell");
	}
	if (state == 2)
	{
		p->out_file = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (p->out_file == -1)
			perror("minishell");
	}
}

int	get_outfile(t_struct *p, int pos)
{
	t_redirect	*tmp;
	int			flag;

	tmp = p->redirect;
	p->flag = 0;
	while (tmp != NULL)
	{
		if (!ft_strncmp(">", tmp->type, 2) && pos == tmp->number_command)
			catch_file(p, tmp->file, 1);
		if (!ft_strncmp(">>", tmp->type, 3) && pos == tmp->number_command)
			catch_file(p, tmp->file, 2);
		tmp = tmp->next;
	}
	return (p->out_file);
}

void	check_heredoc(t_struct *p)
{
	t_redirect	*tmp;

	tmp = p->redirect;
	while (tmp)
	{
		if (!ft_strncmp("<<", tmp->type, 3))
		{
			p->here_doc = 1;
			break ;
		}
		tmp = tmp->next;
	}
}

int	check_outfile(t_struct *p, int pos)
{
	t_redirect	*tmp;

	tmp = p->redirect;
	p->is_outfile = 0;
	while (tmp)
	{
		if (!ft_strncmp(">", tmp->type, 2) && pos == tmp->number_command)
			return (1);
		if (!ft_strncmp(">>", tmp->type, 3) && pos == tmp->number_command)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	check_infile(t_struct *p, int pos)
{
	t_redirect	*tmp;

	tmp = p->redirect;
	while (tmp)
	{
		if (!ft_strncmp("<", tmp->type, 2) && pos == tmp->number_command)
			return (1);
		if (!ft_strncmp("<<", tmp->type, 3) && pos == tmp->number_command)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	check_in(t_struct *p)
{
	if (check_infile(p, p->idx))
	{
		p->fdin = open(get_infile(p, p->idx), O_RDONLY, 0644);
		if (p->fdin == -1)
			perror("minishell");
	}
}

void	redirect_in(t_struct *p)
{
	dup2(p->fdin, 0);
	close(p->fdin);
}

void	redirect_out(t_struct *p)
{
	dup2(p->fdout, 1);
	close(p->fdout);
}

void	check_out(t_struct *p)
{
	if (check_outfile(p, p->idx))
		p->fdout = get_outfile(p, p->idx);
	else
		p->fdout = dup(p->tmpout);
}

void	choose_func(char **commands, t_struct *p)
{
	int	a;

	a = 0;
	a = check_bultin(commands, p);
	if (a == 0 && a != -1)
		check_execve(commands, p);
}

void	child(char **commands, t_struct *p)
{
	if (p->idx != 0)
		check_in(p);
	redirect_in(p);
	if (p->idx == p->total_cmd - 1)
		check_out(p);
	else
	{
		pipe(p->fdpipe);
		if (check_outfile(p, p->idx))
		{
			p->fdout = get_outfile(p, p->idx);
			dup2(p->fdout, p->fdpipe[1]);
		}
		else
			p->fdout = p->fdpipe[1];
		p->fdin = p->fdpipe[0];
	}
	redirect_out(p);
	p->pid[p->idx] = fork();
	if (p->pid[p->idx] == 0)
	{
		if (p->fdin != -1)
			choose_func(commands, p);
		exit(1);
	}
}

int	make_pids(t_struct *p)
{
	if (p->total_cmd != 0)
	{
		p->pid = (pid_t *)malloc((p->total_cmd) * sizeof(pid_t));
		if (!(p->pid))
		{
			ft_putendl_fd("Error: unable to allocate memory", 2);
			return (2);
		}
	}
	return (0);
}

void	ignore_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	on_chld_signals(void)
{
	signal(SIGINT, ctrl_c_child);
	signal(SIGQUIT, ctrl_slash_child);
}

void	on_parent_signals(void)
{
	signal(SIGQUIT, ctrl_slash_parent);
	signal(SIGINT, ctrl_c_parent);
}

void	restore_std(t_struct *p)
{
	dup2(p->tmpin, 0);
	dup2(p->tmpout, 1);
	close(p->tmpin);
	close(p->tmpout);
}

void	global_wait(t_struct *p)
{
	int	i;

	i = 0;
	while (i < p->total_cmd)
	{
		waitpid(p->pid[i], NULL, 0);
		i++;
	}
}

void	preparation(t_struct *p)
{
	ignore_signals();
	p->tmpin = dup(0);
	p->tmpout = dup(1);
	p->here_doc = 0;
	p->idx = 0;
}

void	check_minishell(char **new_arr, t_struct *p)
{
	int	a;

	a = 0;
	if (find_str(new_arr[0], "exit"))
	{
		build_exit(new_arr, p);
		return ;
	}
	if (p->total_cmd == 1)
	{
		a = 0;
		a = check_bultin(new_arr, p);	
	}
	if (a == 1)
		return ;
	// if (ft_strncmp(new_arr[0], "./minishell", 12))
	// 	on_chld_signals();
	child(new_arr, p);
}

void	minishell_wo_pipes(char **array, t_struct *p)
{
	int	i;
	int	a;

	i = 0;
	dup2(p->fdin, 0);
	close(p->fdin);
	check_out(p);
	redirect_out(p);
	a = 0;
	if (find_str(array[0], "exit"))
	{
		build_exit(array, p);
		return ;
	}
	i = check_bultin(array, p);
	if (i == 0)
	{
		check_execve(array, p);
	}
}

void	route_minishell(char **array, t_struct *p)
{
	if (p->total_cmd == 1)
	{
		minishell_wo_pipes(array, p);
	}
	else
	{
		if (ft_strncmp(array[0], "./minishell", 12))
			on_chld_signals();
		child(array, p);
	}
}

char	**split_string(char **commands, t_struct *p)
{
	char	**new_arr;

	new_arr = NULL;
	preparation(p);
	if (check_infile(p, p->idx))
	{
		p->fdin = open(get_infile(p, p->idx), O_RDONLY, 0644);
		if (p->fdin == -1)
			perror("minishell");
	}
	else
		p->fdin = dup(p->tmpin);
	make_pids(p);
	while (p->idx < p->total_cmd)
	{
		new_arr = ft_split_quotes(commands[p->idx], ' ');
		new_arr = parse_strings(new_arr, p);
		if (new_arr[0] != NULL)
			route_minishell(new_arr, p);
			// check_minishell(new_arr, p);
		p->idx++;
	}
	if (p->total_cmd > 1)
	{
		global_wait(p);
	}
	restore_std(p);
	on_parent_signals();
	ft_free(commands);
	free(p->pid);
	return (new_arr);
}

int	parse_cmd(char *line, t_struct *p)
{
	char	**commands;
	int		i;

	p->error = 0;
	if (check_string(line, p) != 0)
		return (2);
	commands = parse_pipe(line, p);
	if (p->error != 0)
	{
		if (commands)
			ft_free(commands);
		return (1);
	}
	commands = parse_redirect(commands, p);
	if (p->error != 0)
	{
		ft_free(commands);
		return (2);
	}
	i = 0;
	while (commands[i])
		i++;
	p->total_cmd = i;
	commands = split_string(commands, p);
	// if (p->redirect)
	// 	print_list(p);
	ft_free(commands);
	return (0);
}
