/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrudge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 18:13:15 by mrudge            #+#    #+#             */
/*   Updated: 2022/01/12 19:50:19 by mrudge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	first_node(t_struct *p, char *type, char *file, int num)
{
	t_redirect 	*tmp;

	p->redirect = (t_redirect *)malloc(sizeof(t_struct));
	if (!p->redirect)
		return ((void )NULL);
	tmp = p->redirect;
	tmp->next = NULL;
	tmp->file = file;
	tmp->number_command = num;
	tmp->type = type;
}

void	add_to_list_redirect(t_struct *p, char *type, char *file, int num)
{
	t_redirect *tmp;

	if (p->redirect == NULL)
		first_node(p, type, file, num);
	else
	{
		tmp = p->redirect;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = (t_redirect *)malloc(sizeof(t_struct));
		if (!tmp->next)
			return((void) NULL);
		tmp = tmp->next;
		tmp->type = type;
		tmp->file = file;
		tmp->number_command = num;
		tmp->next = NULL;
	}
}

void	print_list(t_struct *p)
{
	t_redirect	*tmp;

	tmp = p->redirect;
	if (!tmp)
		return ;
	while (tmp)
	{
		printf ("type of redirect: %s, filename: %s, number of pipe: %d\n",
				tmp->type, tmp->file, tmp->number_command);
		tmp = tmp->next;
	}
}

void	trim_env(t_struct *p)
{
	int		i;
	char	*trimmer;
	char	*start;

	i = 0;
	p->trim_env = (char **)malloc(sizeof (char*) * env_len(p->arr_env) + 1);
	if (!p->trim_env)
		return ((void) NULL);
	while (p->arr_env[i])
	{
		start = ft_strchr(p->arr_env[i], '=');
		trimmer = ft_substr(p->arr_env[i], start - p->arr_env[i] + 1, ft_strlen
		(p->arr_env[i]));
		p->trim_env[i] = ft_strdup(trimmer);
		free(trimmer);
		i++;
	}
}

char	*trim_and_find(char *array, int i, t_struct *p)
{
	int		j;
	char	*trimmer;
	char	*end;

	if (check_ones(array, i))
		return (ft_strdup(array));
	if (strcmp(array, "$?") == 0)
		return (ft_itoa(p->error_code));
	j = 0;
	while (p->arr_env[j])
	{
		end = ft_strchr(p->arr_env[j], '=');
		trimmer = ft_substr(p->arr_env[j], 0, end - p->arr_env[j]);
		if ((ft_strcmp(array + 1, trimmer)) == 0)
		{
			free (array);
			free(trimmer);
			trimmer  = ft_substr(p->arr_env[j], (end - p->arr_env[j]) + 1,
								 (ft_strlen(p->arr_env[j]) - (end -
								 p->arr_env[j])));
			return (trimmer);
		}
		j++;
	}
	free(trimmer);
	free(array);
	return (ft_strdup(""));
}