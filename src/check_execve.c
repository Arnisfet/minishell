/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_execve.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmacmill <jmacmill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 18:19:42 by jmacmill          #+#    #+#             */
/*   Updated: 2022/01/24 20:04:09 by jmacmill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	help_execve(char **spl_path, char *execve_path, \
char **str, t_struct *p)
{
	int		i;
	char	*save;

	i = 0;
	save = NULL;
	while (spl_path[i++])
	{
		if (find_str(str[0], spl_path[i]))
			execve_path = ft_strdup(str[0]);
		else
		{
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
	}
	return (1);
}

int	check_execve(char **str, t_struct *p)
{
	char		*path;
	char		*execve_path;
	char		**spl_path;

	execve_path = NULL;
	path = get_env_var("PATH", p);
	if (path)
	{
		spl_path = ft_split(path, ':');
		if (!help_execve(spl_path, execve_path, str, p))
			return (0);
		if (!ft_strncmp(str[0], "./minishell", 12))
		{
			ignore_signals();
			return (start_execve(str[0], str, p));
		}
		free_array(spl_path);
	}
	p->error = 127;
	ft_putstr_fd("minishell: command not found: ", 2);
	ft_putstr_fd(str[0], 2);
	ft_putstr_fd("\n", 2);
	return (1);
}
