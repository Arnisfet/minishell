/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_msg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrudge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 22:26:43 by mrudge            #+#    #+#             */
/*   Updated: 2021/12/03 23:25:00 by mrudge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

char  *parse_path(char *path, t_struct *p)
{
	char  *home_path;

	if (!path)
		return (NULL);
	home_path = get_env_var("HOME", p);
}

void  display_message(t_struct *p)
{
	char *cwd;
	char buf[4096 + 1];
	char *parsed;

	cwd = getcwd(buf, 4096);
	parsed = parse_path(cwd, p);
}