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

static int	ft_count(const char *s, char c)
{
	size_t	i;
	int		counter;

	i = 0;
	counter = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
			counter++;
		while ((s[i] != '\0') && (s[i] != c))
			i++;
	}
	return (counter);
}

static char	*ft_copy(const char *str, size_t n)
{
	char	*new;
	size_t	i;

	new = (char *)malloc(sizeof(char) * (n + 1));
	if (new == NULL)
		return (NULL);
	i = 0;
	while ((str[i] != '\0') && (i < n))
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	**ft_split(char const *s, char c)
{
	char	**new;
	size_t	i;
	size_t	place;
	int		word;

	if (s == NULL)
		return (NULL);
	new = (char **)malloc(sizeof(char *) * (ft_count(s, c) + 1));
	if (new == NULL)
		return (NULL);
	i = 0;
	word = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		place = i;
		while ((s[i] != '\0') && (s[i] != c))
			i++;
		if (place < i)
			new[word++] = ft_copy(s + place, i - place);
	}
	new[word] = NULL;
	return (new);
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
		get_env_parse(env);
		ft_putstr_fd(line, 1);
		write(1, "\n", 1);
		free(line);
	}
	return (0);
}