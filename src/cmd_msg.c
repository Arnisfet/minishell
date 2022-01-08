/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_msg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrudge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 22:26:43 by mrudge            #+#    #+#             */
/*   Updated: 2022/01/08 17:15:15 by mrudge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* Check the HOME variable from **env*/

char	*get_env_var(char *str, t_struct *p)
{
	t_env	*tmp;

	tmp = p->my_env;
	while (tmp != NULL)
	{
		if (find_str(str, tmp->var))
			return (tmp->value);
		tmp = tmp->next;
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
}