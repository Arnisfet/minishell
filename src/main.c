/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmacmill <jmacmill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 17:53:59 by mrudge            #+#    #+#             */
/*   Updated: 2022/01/27 20:18:17 by mrudge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	display_new_line(void)
{
	char	*cwd;
	char	buff[4096 + 1];

	cwd = getcwd(buff, 4096);
	ft_putstr_fd(cwd, 1);
}

void	my_handler(int signo)
{
	if (signo == SIGINT)
	{
		write(1, "\n", 2);
		ft_putstr_fd("minishell🍑$> ", 1);
		signal(SIGINT, my_handler);
	}
}

static void	str_ct(t_struct *p, char **env)
{
	p->count = 0;
	p->revert_flag = 0;
	p->trim_env = NULL;
	signal(SIGQUIT, ctrl_slash_parent);
	signal(SIGINT, ctrl_c_parent);
	init_env(env, p);
}

int	main(int argc, char **argv, char **env)
{
	t_struct	*p;
	char		*line;

	line = NULL;
	g_status = 0;
	(void ) argv;
	if (argc > 1)
	{
		ft_putstr_fd("Error: too many arguments\n", 2);
		return (-1);
	}
	p = (t_struct *)malloc(sizeof(t_struct));
	if (!p)
		return (-1);
	str_ct(p, env);
	loop(&line, p);
	return (0);
}
