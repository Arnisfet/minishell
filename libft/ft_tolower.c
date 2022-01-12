/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrudge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 22:19:33 by mrudge            #+#    #+#             */
/*   Updated: 2022/01/12 18:30:39 by mrudge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Created by Mickey Rudge on 5/1/21.
//

#include "libft.h"

int	ft_tolower(int ch)
{
	if (ch >= 65 && ch <= 90)
		ch += 'a' - 'A';
	return (ch);
}
