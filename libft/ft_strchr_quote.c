/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrudge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 22:18:42 by mrudge            #+#    #+#             */
/*   Updated: 2022/01/07 04:13:42 by mrudge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr_quote(const char *str, int ch)
{
	char	*p;
	char	*end;

	p = (char *)str;
	if (!p)
		return (p);
	while (*p && *p != ch)
	{
		if (*p == '"' || *p == '\'')
		{
			end = ft_strchr(p + 1, *p);
			p += end - p + 1;
		}
		else
			p++;
	}
	if (*p == ch)
		return (p);
	return (NULL);
}
