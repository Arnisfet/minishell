/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrudge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 21:51:41 by mrudge            #+#    #+#             */
/*   Updated: 2021/12/23 23:04:38 by mrudge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	printr(char **commands)
{
	int i;

	i = 0;
	while (commands[i])
	{
		printf("%s\n", commands[i]);
		i++;
	}
}

char	*write_in_arr(char *line, char *command, int i, t_struct *p)
{
	if (line[i] == ' ' && (line[i + 1] == ' ' || line[i + 1] == '\0'))
		return (command);
	if (line[i] == '"' || line[i] == '\'')
	{
		command = parse_revert(command, line , i, p);
		return (command);
	}
	if (command == NULL)
	{
		if (line[i] == ' ')
			return (command);
		command = (char *)malloc(sizeof (char) + 1);
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
	char	**commands;
	char	*command;

	p->count = 0;
	i = 0;
	commands = NULL;
	command = NULL;
	while (line[i])
	{
		if (line[i] == '|')
		{
			commands =  write_in_2_dim(command, commands);
			command = NULL;
			i++;
		}
		command = write_in_arr(line, command, i, p);
		i += 1 + p->count;
		p->count = 0;
	}
	commands =  write_in_2_dim(command, commands);
	printr(commands);
}
