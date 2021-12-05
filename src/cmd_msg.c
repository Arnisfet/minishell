/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_msg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrudge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 22:26:43 by mrudge            #+#    #+#             */
/*   Updated: 2021/12/05 22:03:29 by mrudge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* Check the HOME variable from **env*/

char	*get_env_var(char *str, t_struct *p)
{
	int	i;
	char	*array;

	i = 0;
	while (p->arr_env[i])
	{
		array = ft_strjoin(str, "=");
		if (ft_strncmp(array, p->arr_env[i], 4) == 0)
		{
			free(array);
			return (ft_strchr(p->arr_env[i], '=') + 1);
		}
		i++;
	}
	return (NULL);
}

char  *parse_path(char *path, t_struct *p, int reverse)
{
	char  *home_path;

	if (!path)
		return (NULL);
	home_path = get_env_var("HOME", p);
	if (reverse == 0)
	{
		if (ft_strcmp(path, home_path) != 0)
			return (ft_strdup(path));
	}
	if (reverse == 1)
	{
		if (ft_strcmp(path, "~") != 0)
			return (ft_strdup(path));
	}
	return (home_path);
}

void  display_message(t_struct *p)
{
	char *cwd;
	char buf[4096 + 1];
	char *parsed;

	cwd = getcwd(buf, 4096);
	parsed = parse_path(cwd, p, 0);
	ft_putstr_fd(parsed, 1);
	ft_putstr_fd("/minishell🍑$> ", 1);
}