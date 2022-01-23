/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmacmill <jmacmill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 18:36:20 by jmacmill          #+#    #+#             */
/*   Updated: 2022/01/23 13:45:03 by jmacmill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	execute(char *path, char **str, t_struct *p)
{
	int	ret;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ctrl_c_child);
	signal(SIGQUIT, ctrl_slash_child);
	ret = fork();
	if (ret == -1)
		ft_putendl_fd("Unable to create a fork", 2);
	if (ret == 0)
	{
		if (execve(path, str, p->arr_env) == -1)
			perror("Could not execute execve");
	}
	else
		waitpid(ret, NULL, 0);
	return (1);
}

int	execute_chld(char *path, char **str, t_struct *p)
{
	if (execve(path, str, p->arr_env) == -1)
		perror("Could not execute execve");
	return (1);
}

int	start_execve(char *path, char **str, t_struct *p)
{
	if (p->total_cmd == 1)
		execute(path, str, p);
	else
		execute_chld(path, str, p);
	free(path);
	return (0);
}

int	check_execve(char **str, t_struct *p)
{
	char		*path;
	char		*execve_path;
	char		**spl_path;
	int			i;

	path = get_env_var("PATH", p);
	if (path)
	{
		i = 0;
		spl_path = ft_split(path, ':');
		while (spl_path[i])
		{
			if (find_str(str[0], spl_path[i]))
				execve_path = ft_strdup(str[0]);
            else
            {
                char	*save;
                execve_path = ft_strjoin(spl_path[i], "/");
                save = execve_path;
                execve_path = ft_strjoin(save, str[0]);
                free(save);
            }
			if (access(execve_path, (F_OK & X_OK)) == -1)
				free(execve_path);
			else
			{
				free_array(spl_path);
				return (start_execve(execve_path, str, p));
			}
			i++;
		}
		if (!ft_strncmp(str[0], "./minishell", 12))
		{
			ignore_signals();
			return (start_execve(str[0], str, p));
		}
		free_array(spl_path);
	}
    ft_putstr_fd("minishell: command not found: ", 2);
    ft_putstr_fd(str[0], 2);
	ft_putstr_fd("\n", 2);
	return (1);	
}
