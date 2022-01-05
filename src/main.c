/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmacmill <jmacmill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 17:53:59 by mrudge            #+#    #+#             */
/*   Updated: 2022/01/05 20:20:20 by jmacmill         ###   ########.fr       */
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
		//display_new_line();
		ft_putstr_fd("minishell🍑$> ",1);
		signal(SIGINT, my_handler);
	}
}

int main(int argc, char **argv, char **env)
{
	t_struct	*p;
	int			status;
	char		*line;


//	char line[] = ">>file'$US'ER$USER\"$USER\"";
	if (argc > 1)
	{
		ft_putstr_fd("Error: too many arguments\n", 2);
		return (-1);
	}
	p = (t_struct *)malloc(sizeof(t_struct));
	if (!p)
		return (-1);
	status = 1;
	init_env(env, p);
	signal(SIGQUIT, my_handler);
	while (status)
	{
		// display_message(p);
		signal(SIGINT, my_handler);
		line = readline("minishell🍑$> ");
		if (!line)
		{
			write(1, "exit\n", 5);
			break ;
		}
		add_history(line);
		if (input_is_empty(line))
		{
			free(line);
			continue;
		}
		parse_cmd(line, p);
		free(line);
	}
}
