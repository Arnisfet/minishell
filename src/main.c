/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrudge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 17:53:59 by mrudge            #+#    #+#             */
/*   Updated: 2021/12/26 13:16:48 by mrudge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"


int main(int argc, char **argv, char **env)
{
	t_struct	*p;
	int			status;
	char		*line;


//	char line[] = ">>file'$US'ER$USER\"$USER\"";
	(void)argc;
	p = (t_struct *)malloc(sizeof(t_struct));
	if (!p)
		return (-1);
	status = 1;
	init_env(env, p);
	while (status)
	{
		display_message(p);
		line = readline("/minishell🍑$> ");
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
