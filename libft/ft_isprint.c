/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrudge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 22:17:46 by mrudge            #+#    #+#             */
/*   Updated: 2022/01/08 17:15:15 by mrudge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
// Created by Mickey Rudge on 5/1/21.
//

#include "libft.h"

int	ft_isprint(int ch)
{
	if (ch >= 32 && ch <= 126)
		return (ch);
	return (0);
}
