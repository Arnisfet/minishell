/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrudge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 17:53:59 by mrudge            #+#    #+#             */
/*   Updated: 2021/12/05 20:09:09 by mrudge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **env)
{
	t_struct	*p;
	int			status;
	char		*line;

	(void)argc;
	p = (t_struct *)malloc(sizeof(t_struct));
	if (!p)
		return (-1);
	status = 1;
	init_env(env, p);
	while (status)
	{
		ft_putstr_fd("@minishell🍑$> ", 1);
		line = readline(argv[1]);
		if (input_is_empty(line))
		{
			free(line);
			continue;
		}
		//check_buildin(line);
		ft_putstr_fd(line, 1);
		write(1, "\n", 2);
		free(line);
	}
	return (0);
}