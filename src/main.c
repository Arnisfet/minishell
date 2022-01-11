/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmacmill <jmacmill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 17:53:59 by mrudge            #+#    #+#             */
/*   Updated: 2022/01/10 21:12:16 by mrudge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	display_new_line()
{
	char	*cwd;
	char	buff[4096 + 1];

	cwd = getcwd(buff, 4096);
	ft_putstr_fd(cwd, 1);
	//free(cwd);
}

void	my_handler(int signo)
{
	if (signo == SIGINT)
	{
		write(1, "\n", 2);
		display_new_line();
		ft_putstr_fd("🍑$> ",1);
		signal(SIGINT, my_handler);
	}
}

int main(int argc, char **argv, char **env)
{
	t_struct	*p;
	int			status;
	char		*line;
//    char line1[] = ">>>";
//    char line2[] = "$SHELL";

//    line = line1;
	p = (t_struct *)malloc(sizeof(t_struct));
	if (!p)
	return (-1);
	(void)argc;
	p->count = 0;
	p->revert_flag = 0;
	p->trim_env = NULL;
	status = 3;
	signal(SIGQUIT, my_handler);
	init_env(env, p);
	while (status)
	{
		signal(SIGINT, my_handler);
		line = readline("/minishell🍑$> ");
		add_history(line);
		if (input_is_empty(line))
		{
			free(line);
			continue;
		}
		parse_cmd(line, p);
		if (p->redirect)
			freed(p);
		free(line);
		p->error_code = p->error;
//		line = line2;
	}
}
