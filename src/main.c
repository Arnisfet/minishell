/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrudge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 17:53:59 by mrudge            #+#    #+#             */
/*   Updated: 2021/12/07 21:29:43 by mrudge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"


int main(int argc, char **argv, char **env)
{
	t_struct	*p;
	int			status;
	char		*line;
	char		**test;

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
		test = ft_split(line, ' ');
		if (find_str(test[0], "cd"))
			build_cd(test, p);
		if (find_str(test[0], "pwd"))
			build_pwd(test);
		write(1, "\n", 2);
		free(line);
	}
	return (0);
}