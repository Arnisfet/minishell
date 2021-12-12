/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrudge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 22:17:39 by mrudge            #+#    #+#             */
/*   Updated: 2021/12/18 19:17:52 by mrudge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Created by Mickey Rudge on 5/1/21.
//
// Возвращает кодовый номер числа

#include "libft.h"

int	ft_isdigit(int ch)
{
	if (ch >= 48 && ch <= 57)
		return (ch);
	return (0);
}
