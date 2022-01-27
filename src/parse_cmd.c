/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmacmill <jmacmill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 17:57:10 by mrudge            #+#    #+#             */
/*   Updated: 2022/01/27 20:18:17 by mrudge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
		build_exit(str);
		return (-1);
	}
	return (0);
}

void	choose_func(char **commands, t_struct *p)
{
	int	a;

	a = 0;
	a = check_bultin(commands, p);
	p->error = g_status;
	g_status = 0;
	if (a == 0 && a != -1)
	{
		if (access(commands[0], (F_OK & X_OK)) == 0)
			execute_chld(commands[0], commands, p);
		else
			check_execve(commands, p);
	}		
}

void	splitting(char **commands, t_struct *p)
{
	restore_std(p);
	on_parent_signals();
	ft_free(commands);
	free(p->pid);
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
		{
			p->error = 1;
			perror("minishell");
		}
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
		p->idx++;
	}
	if (p->total_cmd > 1)
		global_wait(p);
	splitting(commands, p);
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
	create_redir(p);
	commands = split_string(commands, p);
	ft_free(commands);
	return (0);
}
