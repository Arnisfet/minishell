/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrudge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 20:32:09 by mrudge            #+#    #+#             */
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

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
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

int main(int argc, char **argv, char **env)
{
	int		status;
	char	*line;

	status = 1;
	while (status)
	{
		ft_putstr_fd("minishell🐻$> ", 1);
		line = readline(argv[1]);
		if (input_is_empty(line))
		{
			free(line);
			continue;
		}
		ft_putstr_fd(line, 1);
		write(1, "\n", 1);
		free(line);
	}
	return (0);
}