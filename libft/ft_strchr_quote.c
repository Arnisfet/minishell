/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrudge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 22:18:42 by mrudge            #+#    #+#             */
/*   Updated: 2021/12/18 19:29:25 by mrudge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr_quote(const char *str, int ch)
{
	char	*p;
	char	quote;

	p = (char *)str;
	while (*p && *p != ch)
	{
		if (*p == '"' || *p == '\'')
		{
			quote = *p++;
			while (*p != quote)
				p++;
		}
		else
			p++;
	}
	if (*p == ch)
		return (p);
	return (NULL);
}
