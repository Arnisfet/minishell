/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrudge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 20:32:09 by mrudge            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/12/03 17:02:34 by mrudge           ###   ########.fr       */
=======
/*   Updated: 2021/12/03 15:28:13 by mrudge           ###   ########.fr       */
>>>>>>> cd
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	build_cd(const char *str)
{
	if (chdir(str) == 0)
	{
		return (0);
	}
	return (-1);
}

int main(int argc, char **argv, char **env)
{
	printf("Hello Minishell! \n");

	return (0);
}