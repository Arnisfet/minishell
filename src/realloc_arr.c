/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_arr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrudge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 21:51:16 by mrudge            #+#    #+#             */
/*   Updated: 2022/01/08 17:34:11 by mrudge           ###   ########.fr       */
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
		new_arr[i] = strdup(commands[i]);
		i++;
	}
	new_arr[i] = strdup(command);
	new_arr[i + 1] = NULL;
//	ft_free(commands);
	return (new_arr);
}

char **write_in_2_dim(char *command,char **commands)
{
	if (!command)
		return (NULL);
	if (!commands)
	{
		commands = (char **)malloc(sizeof (char *) * 2);
		commands[0] = ft_strdup(command);
		commands[1] = NULL;
		return (commands);
	}
	else
	{
		commands = realloc_2_dim(commands, command);
		return (commands);
	}
}

char	*ft_realloc_ch(char *command, char ch)
{
	int	i;
	char *new_arr;

	i = 0;
	if (command)
		i = ft_strlen(command);
	new_arr = (char *)malloc(sizeof (char) * (i + 2));
	new_arr = ft_memmove(new_arr, command, i);
	new_arr[i] = ch;
	new_arr[i + 1] = '\0';
	free (command);
	return (new_arr);
}