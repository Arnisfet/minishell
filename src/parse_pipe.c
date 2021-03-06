/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrudge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 21:51:41 by mrudge            #+#    #+#             */
/*   Updated: 2022/01/27 20:18:17 by mrudge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	printr(char **commands)
{
	int	i;

	i = 0;
	while (commands[i])
	{
		printf("%s\n", commands[i]);
		i++;
	}
}

char	*quotes(char *line, char *command, int i, t_struct *p)
{
	char	ch;

	p->revert_flag = 1;
	p->count = i;
	command = write_in_arr(line, command, i, p);
	ch = line[i++];
	while (line[i] != '\0' && line[i] != ch)
	{
		command = write_in_arr(line, command, i, p);
		i++;
	}
	if (line[i] != ch)
	{
		ft_putstr_fd("\t\tError: odd number of quotes\n", 1);
		p->error = 1;
		free(command);
		return (NULL);
	}
	p->count = i - p->count;
	p->revert_flag = 0;
	return (command);
}

char	*write_in_arr(char *line, char *command, int i, t_struct *p)
{
	if ((line[i] == ' ' && (line[i + 1] == ' ' || line[i + 1] == '\0'))
		&& p->revert_flag == 0)
		return (command);
	if ((line[i] == '"' || line[i] == '\'') && p->revert_flag == 0)
	{
		command = quotes(line, command, i, p);
		if (command == NULL)
			return (NULL);
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

char	**parse_pipe(char *line, t_struct *p)
{
	int		i;
	char	**commands;
	char	*command;

	i = 0;
	commands = NULL;
	command = NULL;
	while (line[i])
	{
		p->count = 0;
		if (line[i] == '|')
		{
			commands = write_in_2_dim(command, commands);
			command = NULL;
			i++;
		}
		command = write_in_arr(line, command, i, p);
		i += p->count + 1;
	}
	commands = write_in_2_dim(command, commands);
	if (command)
		free(command);
	return (commands);
}
//"qwerty$SHELL qwe$USER""$USER$SHELL" checktha$ qwe | $USER $SHELL