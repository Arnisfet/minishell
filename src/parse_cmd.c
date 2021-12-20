/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrudge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 21:51:41 by mrudge            #+#    #+#             */
/*   Updated: 2021/12/20 23:27:26 by mrudge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_realloc_ch(char *command, char ch)
{
	int	i;
	char *new_arr;

	i = strlen(command);
	new_arr = (char *)malloc(sizeof (char) * (i + 1));
	new_arr = memmove(new_arr, command, i);
	new_arr[i] = ch;
	new_arr[i + 1] = '\0';
//	printf("-----%s \n", command);
	return (new_arr);
}

char	*write_in_arr(char *line, char *command, int i)
{
	if (line[i] == ' ')
		return (command);
	if (!command)
	{
		command = (char *)malloc(sizeof (char) * 2);
		ft_bzero(command, ft_strlen(command));
		command[0] = line[i];
		command[0 + 1] = '\0';
	}
	else
		command = ft_realloc_ch(command, line[i]);
	return (command);
}

int	parse_cmd(char *line, t_struct *p)
{
	int	i;
	char	*command;
	char	**commands;

	i = 0;
	command = NULL;
	commands = NULL;
	while (line[i])
	{
		if (line[i] == ' ')
		{
			commands = write_in_2_dim(command, commands);
			command = NULL;
		}
		command = write_in_arr(line, command, i);
		i++;
	}
	ft_free(commands);
}

