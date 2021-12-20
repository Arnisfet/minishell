/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_arr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrudge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 21:51:16 by mrudge            #+#    #+#             */
/*   Updated: 2021/12/20 23:03:49 by mrudge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_free(char **commands)
{
	int	i;

	i = 0;
	while (commands[i])
	{
		free(commands[i]);
		i++;
	}
	free(commands);
}

char	**realloc_2_dim(char **commands, char *command)
{
	int		i;
	char	**new_arr;

	i = 0;
	new_arr = (char **)malloc(sizeof (char *) * (env_len(commands) + 2));
	while (commands[i])
	{
		new_arr[i] = ft_strdup(commands[i]);
		i++;
	}
	new_arr[i] = ft_strdup(command);
	new_arr[i + 1] = NULL;
	i = 0;
	while (new_arr[i])
	{
		printf("%s\n", new_arr[i]);
		i++;
	}
	ft_free(commands);
	return (new_arr);
}

char **write_in_2_dim(char *command,char **commands)
{
	if (!command)
		return (NULL);
	if (!commands)
	{
		commands = (char **)malloc(sizeof (char *) * 1);
		commands[0] = ft_strdup(command);
		free(command);
		return (commands);
	}
	else
	{
		commands = realloc_2_dim(commands, command);
		free(command);
		return (commands);
	}
}