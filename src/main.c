/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrudge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 17:53:59 by mrudge            #+#    #+#             */
/*   Updated: 2021/12/04 13:19:19 by mrudge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "../minishell.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (*str++)
		i++;
	return (i);
}

int	input_is_empty(char *check)
{
	int	i;

	i = 0;
	while (check[i] != '\0')
	{
		if (check[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	build_cd(const char *str)
{
	char	*error;

	if (chdir(str) == 0)
	{
		return (0);
	}
	error = strerror(errno);
	ft_putstr_fd(error, 1);
	return (1);
}

void	get_env_parse(char **env)
{
	//char	**parsed_env;
	int	i;

	i = 0;
	while (*env[i] != '\0')
	{
		ft_putstr_fd(env[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
}

int main(int argc, char **argv, char **env)
{
	t_struct	*p;
	int			status;
	char		*line;

	p = (t_struct *)malloc(sizeof(t_struct));
	status = 1;
	init_env(env, p);
	while (status)
	{
		display_message(p);
		ft_putstr_fd("minishell🐻$> ", 1);
		line = readline(argv[1]);
		if (input_is_empty(line))
		{
			free(line);
			continue;
		}
		get_env_parse(env);
		ft_putstr_fd(line, 1);
		write(1, "\n", 1);
		free(line);
	}
	return (0);
}