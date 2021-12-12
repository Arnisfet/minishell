#include "../inc/minishell.h"

int	unset_errors(char **str)
{
	if (!str[1])
	{
		ft_putstr_fd("unset: not enough arguments\n", 2);
		return (1);
	}
	return (0);
}

int	build_unset(char **str, t_struct *p)
{
	char	*compare;
	char	*stop_position;
	int		i;
	t_env	*tmp;

	i = 0;
	if (unset_errors(str))
		return (-1);
	// while (p->arr_env[i])
	// {
	// 	stop_position = ft_strchr(p->arr_env[i], '=');
	// 	if (stop_position)
	// 	{
	// 		*stop_position = '\0';
	// 		compare = ft_strdup(p->arr_env[i]);
	// 		if (find_str(str[1], compare))
	// 		{	
	// 			ft_putstr_fd(compare, 1);
	// 			ft_putstr_fd("\n", 1);
	// 		}
	// 		free(compare);
	// 	}
	// 	i++;
	// }
	tmp = p->my_env;
	if (tmp != NULL)
	{
		while (tmp->next != NULL)
		{
			stop_position = ft_strchr(p->my_env->var, '=');
			if (stop_position)
			{
				*stop_position = '\0';
				compare = ft_strdup(p->my_env->var);
				if (find_str(str[1], compare))
				{	
					ft_putstr_fd(compare, 1);
					ft_putstr_fd("\n", 1);
				}
				free(compare);
			}
			tmp = tmp->next;
		}
	}
	return (1);
}