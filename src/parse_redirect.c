/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrudge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 18:13:15 by mrudge            #+#    #+#             */
/*   Updated: 2022/01/20 20:26:58 by mrudge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static	char	*write_filename(char *end, char *start, t_struct *p)
{
	while (*end != ' ' && *end != '>' && *end != '<' && *end != '\0')
	{
		if (*end == '"' || *end == '\'')
			end = ft_strchr(end, *end);
		end++;
	}
	if (*end != ' ' && *end != '\0')
	{
		if (!(check_digit(start, end, p)))
			return (NULL);
	}
	return (end);
}

static int	check_status(char *file, t_struct *p, char *redirect, char *end)
{
	if (*end == '\0')
	{
		file = NULL;
		add_to_list_redirect(p, redirect, file, p->count);
		if (correct_check(p))
			return (2);
	}
	return (0);
}

int	substring(char *start, t_struct *p)
{
	char	*redirect;
	char	*file;
	char	*end;

	end = start;
	p->point_r = start;
	while (*end != '\0' && (*end != ' ' && (*end == '<' || *end == '>')))
		end++;
	redirect = ft_strndup(start, end - start);
	if (*end != '\0' && *(end) == ' ')
		end++;
	if (check_status(file, p, redirect, end))
		return (2);
	start = end;
	end = write_filename(end, start, p);
	if (!end)
		return (2);
	p->point_f = end;
	file = ft_strndup(start, end - start);
	if (ft_strcmp("<<", redirect) != 0)
		file = parse_dollar_without_quote(file, p);
	util(p, file, redirect);
	if (correct_check(p))
		return (2);
	return (0);
}

char	*first_rparse(char *commands, t_struct *p)
{
	char	*start;
	int		i;

	p->tmp_red = NULL;
	i = 0;
	while (commands[i])
	{
		if (commands[i] == '\'' || commands[i] == '"')
			i = end_of_quote(commands, i);
		if (commands[i] == '>' || commands[i] == '<')
		{
			start = &commands[i];
			if (substring(start, p))
			{
				free(p->tmp_red);
				return (NULL);
			}
			free(p->tmp_red);
			commands = ft_strtrim_quote(commands, p->point_r, p->point_f);
			continue ;
		}
		i++;
	}
	return (commands);
}

char	**parse_redirect(char **commands, t_struct *p)
{
	int	i;

	p->count = 0;
	i = 0;
	while (commands[i])
	{
		commands[i] = first_rparse(commands[i], p);
		i++;
		p->count++;
	}
	return (commands);
}
