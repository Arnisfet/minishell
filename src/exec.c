/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmacmill <jmacmill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 18:36:20 by jmacmill          #+#    #+#             */
/*   Updated: 2022/01/11 19:55:57 by jmacmill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	execute(char *path, char **str, t_struct *p)
{
	pid_t	child;
	
	child = fork();
	if (child == -1)
	{
		ft_putstr_fd("Error creating a process\n", 2);
		return (-1);
	}
	if (child == 0)
	{
		if (execve(path, str, p->arr_env) == -1)
			perror("Could not execute execve");
	}
	waitpid(child, NULL, 0);
	return (1);
}

int	start_execve(char *path, char **str, t_struct *p)
{
	execute(path, str, p);
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
                char *save;
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
		free_array(spl_path);
	}
    ft_putstr_fd("minishell: command not found: ", 2);
    ft_putstr_fd(str[0], 2);
	return (1);	
}
