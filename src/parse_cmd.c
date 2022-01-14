/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmacmill <jmacmill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 17:57:10 by mrudge            #+#    #+#             */
/*   Updated: 2022/01/05 20:04:37 by jmacmill         ###   ########.fr       */
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

void	start_heredoc(t_struct *p, char *stop)
{
	int			file;
	char		*buf;

	file = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_APPEND, 0000644);
	if (file < 0)
	{
		perror("minishell: ");
		return ;
	}
	while (21)
	{
		write(1, "heredoc> ", 9);
		if (get_next_line(0, &buf) < 0)
			exit(1);
		if (!ft_strncmp(stop, buf, ft_strlen(stop) + 1))
			break ;
		write(file, buf, ft_strlen(buf));
		write(file, "\n", 1);
		free(buf);
	}
	free(buf);
	close(file);
	p->in_file = open(".heredoc_tmp", O_RDONLY);
	if (p->in_file < 0)
	{
		unlink(".heredoc_tmp");
		ft_putendl_fd("Error: unable to open a file", 2);
	}
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

void	get_infile(t_struct *p)
{
	t_redirect	*tmp;

	tmp = p->redirect;
	if (p->here_doc)
	{
		while (tmp)
		{
			if (!ft_strncmp("<<", tmp->type, 3))
				start_heredoc(p, tmp->file);
			tmp = tmp->next;
		}
	}
	else
	{
		if (p->is_infile)
		{
			p->in_file = open(get_file(p, "<"), O_RDONLY);
			if (p->in_file < 0)
				return ;
		}
		else
			p->in_file = dup(0);
	}
}

char	*get_outfile(t_struct *p)
{
	t_redirect	*tmp;
	char		*file_name;

	tmp = p->redirect;
	while (tmp)
	{
		if (!ft_strncmp(">", tmp->type, 2))
			return (tmp->file);
		tmp = tmp->next;
	}
	return (NULL);
}

int	launch(char **commands, t_struct *p)
{
	char	*infile;

	printf("%d\n", p->in_file);
	
	//get_outfile(p);

	// else     
	// {
	// 	result = check_bultin(commands, p);
	// 	if (result == 1)
	// 		return (0);
	// 	if (result == -1)
	// 		return (-1);
	// 	if (check_execve(commands, p))
	// 		return (0);
	// }
	//free(p->pipe);
	return (1);
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

void	check_infile(t_struct *p)
{
	t_redirect	*tmp;

	tmp = p->redirect;
	while (tmp)
	{
		if (!ft_strncmp("<", tmp->type, 2))
		{
			p->is_infile = 1;
			break ;
		}
		tmp = tmp->next;
	}
}

void	parent_free(t_struct *p)
{
	close(p->in_file);
	close(p->out_file);
	if (p->here_doc)
		unlink(".heredoc_tmp");
	if (p->pipe)
		free(p->pipe);
}

static void	create_pipes(t_struct *p)
{
	int	i;

	i = 0;
	while (i < p->total_cmd - 1)
	{
		if (pipe(p->pipe + 2 * i) < 0)
			parent_free(p);
		i++;
	}
}

char	**split_string(char **commands, t_struct *p)
{
	int		i;
	char	**new_arr;

	i = 0;
	while (commands[i])
		i++;
	p->total_cmd = i;
	i = 0;
	p->here_doc = 0;
	p->is_infile = 0;
	check_heredoc(p);
	check_infile(p);
	get_infile(p);
	p->pipe = (int *)malloc(sizeof(int) * (2 * (p->total_cmd - 1)));
	if (!(p->pipe))
		return (NULL);
	create_pipes(p);
	p->idx = -1;

	while (commands[i])
	{
		new_arr = ft_split_quotes(commands[i], ' ');
		new_arr = parse_strings(new_arr, p);
		launch(new_arr, p);
		i++;
	}
	ft_free(commands);
	return (new_arr);
}

int	parse_cmd(char *line, t_struct *p)
{
	char	**commands;

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
	commands = split_string(commands, p);
	if (p->redirect)
		print_list(p);
	ft_free(commands);
	return (0);
}
