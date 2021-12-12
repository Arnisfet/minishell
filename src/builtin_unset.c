#include "../inc/minishell.h"

void	delete_var(t_env *to_delete, t_struct *p)
{
	t_env	*tmp;

	tmp = p->my_env;
	if (tmp == to_delete)
	{
		p->my_env = to_delete->next;
		free(to_delete->var);
		free(to_delete);
		return ;
	}
	while (tmp->next != to_delete)
		tmp = tmp->next;
	tmp->next = to_delete->next;
	free(to_delete->var);
	free(to_delete);
}

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
	tmp = p->my_env;
	while (tmp != NULL)
	{
		stop_position = ft_strchr(tmp->var, '=');
		if (stop_position)
		{
			*stop_position = '\0';
			compare = ft_strdup(tmp->var);
			if (find_str(str[1], compare))
			{	
				ft_putstr_fd(compare, 1);
				ft_putstr_fd("\n", 1);
				delete_var(tmp, p);
				break ;
			}
			else
				*stop_position = '=';
			free(compare);
		}
		tmp = tmp->next;
	}
	return (1);
}