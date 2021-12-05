/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrudge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 17:53:59 by mrudge            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/12/05 21:52:51 by mrudge           ###   ########.fr       */
=======
/*   Updated: 2021/12/05 20:46:49 by mrudge           ###   ########.fr       */
>>>>>>> 02437a4db877d98d289ad7eba4fed4b2b4a561a5
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"


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
		display_message(p);
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