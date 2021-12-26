#include "../inc/minishell.h"

void	add_or_blank(char *str, t_struct *p)
{
	char	*stop_position;
	char	*compare;
	t_env	*tmp;

	tmp = p->my_env;
	while (tmp != NULL)
	{
		stop_position = ft_strchr(tmp->var, '=');
		if (stop_position)
		{
			*stop_position = '\0';
			compare = ft_strdup(tmp->var);
			if (find_str(str, compare))
			{
				free(tmp->var);
				tmp->var = ft_strdup(str);
			}
			else
			{
				free(tmp->var);
				tmp->var = ft_strdup(str);
			}
		}
	}
}

int	print_env(t_struct *p)
{
	t_env	*tmp;

	tmp = p->my_env;
	while (tmp != NULL)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(tmp->var, 1);
		ft_putchar_fd('=', 1);
		ft_putendl_fd(tmp->value, 1);
		tmp = tmp->next;
	}
	return (1);
}

int	build_export(char **str, t_struct *p)
{
	int		i;
	char	*stop_position;
	char	*compare;

	if (!str[1])
	{
		print_env(p);
		return (1);
	}
	// i = 1;
	// while (str[i])
	// {
	// 	stop_position = ft_strchr(str[i], '=');
	// 	if (stop_position)
	// 	{
	// 		*stop_position = '\0';
	// 	}
	// 	else
	// 	{
	// 		add_or_blank(str[i], p);
	// 	}
	// 	i++;
	// }
	return (1);
}