#include "../inc/minishell.h"

int	build_export(char **str, t_struct *p)
{
	int		i;
	t_env	*tmp;

	i = 0;
	if (!str[1])
	{
		tmp = p->my_env;
		while (tmp != NULL)
		{
			ft_putstr_fd(tmp->var, 1);
			ft_putstr_fd("\n", 1);
			tmp = tmp->next;
		}
		return (1);
	}
	if (!str[2])
	{
			
	}
}