/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmacmill <jmacmill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 17:57:10 by mrudge            #+#    #+#             */
/*   Updated: 2022/01/15 18:29:31 by jmacmill         ###   ########.fr       */
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
			{
				ft_putendl_fd("Unable to open a file", 1);	
				return ;
			}
		}
		else
			p->in_file = dup(0);
	}
}

void	get_outfile(t_struct *p)
{
	if (p->is_outfile)
	{
		p->out_file = open(get_file(p, ">"), O_CREAT | O_WRONLY | O_TRUNC, 0000644);	
		if (p->out_file < 0)
		{
			ft_putendl_fd("Unable to open a file", 1);	
			return ;
		}
	}
	else
		p->out_file = dup(1);
}

void	close_pipes(t_struct *p)
{
	int	i;

	i = 0;
	while (i < (p->total_pipes))
	{
		close(p->pipe[i]);
		i++;
	}
}

void	sub_dup2(int fdin, int fdout)
{
	dup2(fdin, STDIN_FILENO);
	dup2(fdout, STDOUT_FILENO);
}

// void	launch_child(char **commands, t_struct *p)
// {
// 	// printf("%s\n", *commands);
// 	//get_outfile(p);	
// 	p->pid = fork();
// 	if (!p->pid)
// 	{
// 		if (p->idx == 0) // Если первая команда
// 			sub_dup2(p->in_file, p->pipe[1]);
// 		else if (p->idx == 0 && p->total_cmd == 1) // Если первая и последняя команда
// 			sub_dup2(p->pipe[1], p->out_file);
// 		else if (p->idx == p->total_cmd - 1) // Если последняя команда
// 			sub_dup2(p->pipe[2 * p->idx - 2], p->out_file); // Направляем файл в out
// 		else
// 			sub_dup2(p->pipe[2 * p->idx - 2], p->pipe[2 * p->idx + 1]); // Направлем в следующий пайп
// 		close_pipes(p);
		
// 		if (check_bultin(commands, p) == 1)
// 			return ;
// 		// if (result == -1)
// 		// 	return ;
// 		if (check_execve(commands, p))
// 			return ;		
// 	}
// 	// else     
// 	// {
// 	// 	result = check_bultin(commands, p);
// 	// 	if (result == 1)
// 	// 		return (0);
// 	// 	if (result == -1)
// 	// 		return (-1);
// 	// 	if (check_execve(commands, p))
// 	// 		return (0);
// 	// }
// 	//free(p->pipe);
// }

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

void	check_files(t_struct *p)
{
	t_redirect	*tmp;

	tmp = p->redirect;
	p->is_infile = 0;
	p->is_outfile = 0;
	while (tmp)
	{
		if (!ft_strncmp("<", tmp->type, 2))
		{
			p->is_infile = 1;
			break ;
		}
		tmp = tmp->next;
	}
	tmp = p->redirect;
	while (tmp)
	{
		if (!ft_strncmp(">", tmp->type, 2))
		{
			p->is_outfile = 1;
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

void	create_fd(t_struct *p)
{
	int	i;

	i = 0;
	p->fd = malloc(sizeof(int *) * p->total_cmd);
	if (!p->fd)
		printf("Error\n");
	while (i < p->total_cmd)
	{
		p->fd[i] = malloc(sizeof(int) * 2);
		if (!(p->fd[i]))
			printf("Error\n");
		i++;
	}
}

void	create_pipe_fd(t_struct *p)
{
	int	i;

	i = 0;
	while (i < p->total_cmd)
	{
		pipe(p->fd[i]);
		if (pipe(p->fd[i]) == -1)
			printf("Error\n");
		i++;
	}
}

void	close_fds(t_struct *p)
{
	int	i;

	i = 0;
	while (i < p->total_cmd)
	{
		if (!p->fd || !p->fd[i])
			continue ;
		close(p->fd[i][0]);
		close(p->fd[i][1]);
		free(p->fd[i]);
		i++;
	}
	free(p->fd);
}

int	child(char **commands, t_struct *p)
{
	int	file[2];
	int	dup_result;

	file[0] = 0;
	file[1] = 1;
	if (p->idx == 0)
		dup2(file[0], STDIN_FILENO);
	else if (p->idx != 0)
		dup2(p->fd[p->idx][1], STDOUT_FILENO);
	close_fds(p);
	check_execve(commands, p);
	return (0);
}

void	waitpid_pipex(t_struct *p)
{
	int	i;

	i = 0;
	while (i < p->total_cmd)
	{
		waitpid(p->pid[i], NULL, 0);
		i++;
	}
}

char	**split_string(char **commands, t_struct *p)
{
	int		i;
	char	**new_arr;

	//save in/out
	int tmpin = dup(0);
	int tmpout = dup(1);	

	//set the initial input
	int fdin;
	fdin = dup(tmpin);  //Use default input
	
	int ret;
	int fdout;

	i = 0;
	while (commands[i])
		i++;
	p->total_cmd = i;
	p->idx = 0;

	while (p->idx < p->total_cmd)
	{
		new_arr = ft_split_quotes(commands[p->idx], ' ');
		new_arr = parse_strings(new_arr, p);
		
		//redirect input
		dup2(fdin, 0);
		close(fdin);
		//set output
		if (p->idx == p->total_cmd - 1)
		{
			// Use default output
			fdout = dup(tmpout);
		}
		else
		{
			// Not last simple command create pipe
			int fdpipe[2];
			pipe(fdpipe);
			fdout = fdpipe[1];
			fdin = fdpipe[0];
		}
		// Redirect output
		dup2(fdout, 1);
		close(fdout);

		// Create child process;
		ret = fork();
		if (ret == 0)
		{
			check_execve(new_arr, p);
			//perror("minishell");
			exit(1);
		}

		p->idx++;
	}
	// restore in/out defaults
	dup2(tmpin, 0);
	dup2(tmpout, 1);

	close(tmpin);
	close(tmpout);

	waitpid(ret, NULL, 0);

	ft_free(commands);
	return (new_arr);
}

// char	**split_string(char **commands, t_struct *p)
// {
// 	int		i;
// 	char	**new_arr;

// 	i = 0;
// 	while (commands[i])
// 		i++;
// 	p->total_cmd = i;
// 	i = 0;
// 	p->here_doc = 0;
// 	check_heredoc(p);
// 	check_files(p);
// 	get_infile(p);
// 	get_outfile(p);
// 	p->total_pipes = 2 * (p->total_cmd - 1);
// 	printf("Total pipes: %d\n",p->total_pipes);
// 	p->pipe = (int *)malloc(sizeof(int) * p->total_pipes);
// 	if (!(p->pipe))
// 		return (NULL);
// 	create_pipes(p);
// 	p->idx = 0;

// 	printf("AMOUNT of commands: %d\n",p->total_cmd);
// 	while (p->idx < p->total_cmd)
// 	{
// 		new_arr = ft_split_quotes(commands[p->idx], ' ');
// 		new_arr = parse_strings(new_arr, p);
// 		launch_child(new_arr, p);
// 		p->idx++;
// 	}
// 	close_pipes(p);
// 	close(p->in_file);
// 	close(p->out_file);
// 	waitpid(-1, NULL, 0);

// 	free(p->pipe);
// 	ft_free(commands);
// 	return (new_arr);
// }

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
	// if (p->redirect)
	// 	print_list(p);
	ft_free(commands);
	return (0);
}
