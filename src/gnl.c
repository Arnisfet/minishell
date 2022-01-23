/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmacmill <jmacmill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 12:16:58 by jmacmill          #+#    #+#             */
/*   Updated: 2022/01/23 13:34:23 by jmacmill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	ft_finish(char *tmp, char **line, char c, int i)
{
	tmp[i] = c;
	tmp[i + 1] = 0;
	free(*line);
	*line = tmp;
}

static int	ft_exit(char **line)
{
	free(*line);
	return (-1);
}

static void	ft_fill(char *tmp, char **line, int *i)
{
	tmp[*i] = (*line)[*i];
	(*i)++;
}

int	get_next_line(int fd, char **line)
{
	int		i;
	int		len;
	int		r;
	char	c;
	char	*tmp;

	r = 1;
	len = 1;
	*line = malloc(len);
	(*line)[0] = 0;
	if (!line)
		return (-1);
	while (r > 0 && len++ && c != '\n')
	{
		r = read(fd, &c, 1);
		tmp = malloc(len);
		if (!tmp)
			ft_exit(line);
		i = 0;
		while (i < len - 2)
			ft_fill(tmp, line, &i);
		ft_finish(tmp, line, c, i);
	}
	return (r);
}
