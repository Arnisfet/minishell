/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrudge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 17:53:59 by mrudge            #+#    #+#             */
/*   Updated: 2021/12/12 17:20:02 by mrudge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// void	display_new_line()
// {
// 	char	*cwd;
// 	char	buff[4096 + 1];

// 	cwd = getcwd(buff, 4096);
// 	ft_putstr_fd(cwd, 1);
// 	// free(cwd);
// }

// void	my_handler(int signo)
// {
// 	if (signo == SIGINT)
// 	{
// 		ft_putstr_fd("^C\n", 1);
// 		display_new_line();
// 		ft_putstr_fd("🍑$> ",1);
// 		signal(SIGINT, my_handler);
// 	}
// }

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
		// signal(SIGINT, my_handler);
		line = readline("🍑$> ");
		//add_history(line);
		if (input_is_empty(line))
		{
			free(line);
			continue;
		}
		test = ft_split(line, ' ');
		if (find_str(test[0], "unset"))
			build_unset(test, p);
		if (find_str(test[0], "export"))
			build_export(test, p);
		if (find_str(test[0], "cd"))
			build_cd(test, p);
		if (find_str(test[0], "pwd"))
			build_pwd(test);
		if (find_str(test[0], "exit"))
			build_exit(test, p);
		//write(1, "\n", 2);
		// if (parse_cmd(test, p) == 0)
		// 	return (0);
		free(line);
		//rl_clear_history();
	}
}