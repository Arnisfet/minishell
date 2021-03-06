/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmacmill <jmacmill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 17:43:02 by jmacmill          #+#    #+#             */
/*   Updated: 2022/01/27 20:18:17 by mrudge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	find_str(const char *s1, const char *s2)
{
	int	result;

	if (!s1 || !s2)
		return (0);
	result = strcmp(s1, s2);
	if (result == 0)
		return (1);
	return (0);
}

void	update_var(char *s1, char *s2, t_struct *p)
{
	t_env	*tmp;

	tmp = p->my_env;
	while (tmp != NULL)
	{
		if (find_str(s1, tmp->var))
		{
			if (tmp->value)
			{
				free(tmp->value);
				tmp->value = NULL;
			}
			tmp->value = ft_strdup(s2);
			break ;
		}
		tmp = tmp->next;
	}
}

void	go_to_dir(char *path, t_struct *p)
{
	char	oldpwd[4096 + 1];
	char	cwd[4096 + 1];

	getcwd(oldpwd, 4096);
	if (chdir(path) != 0)
	{
		p->error = 1;
		perror("cd ");
		return ;
	}
	update_var("OLDPWD", oldpwd, p);
	update_var("PWD", getcwd(cwd, 4096), p);
}

int	build_cd(char **str, t_struct *p)
{
	char	*home_path;
	char	*old_path;

	home_path = get_env_var("HOME", p);
	old_path = get_env_var("OLDPWD", p);
	if (!str[1])
		go_to_dir(home_path, p);
	else
	{
		if (!str[2])
		{
			if (!find_str(str[1], "--") && !find_str(str[1], "~") \
			&& !find_str(str[1], "-"))
				go_to_dir(str[1], p);
			if (find_str(str[1], "--") || find_str(str[1], "~"))
				go_to_dir(home_path, p);
			if (find_str(str[1], "-"))
				go_to_dir(old_path, p);
		}
		else
		{
			p->error = 1;
			ft_putstr_fd("bash: cd: too many arguments\n", 2);
		}
	}
	return (1);
}
