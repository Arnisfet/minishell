/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrudge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 18:13:15 by mrudge            #+#    #+#             */
/*   Updated: 2022/01/20 19:27:18 by mrudge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free2(char *array, char *trimmer)
{
	free (array);
	free(trimmer);
}

void	util(t_struct *p, char *file, char *redirect)
{
	p->tmp_red = ft_strdup(redirect);
	file = parse_revert(file, 0, p);
	add_to_list_redirect(p, redirect, file, p->count);
}