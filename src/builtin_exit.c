#include "../inc/minishell.h"

void	free_list(t_struct *p)
{
	t_env	*tmp;

	while (p->my_env != NULL)
	{
		tmp = p->my_env;
		p->my_env = p->my_env->next;
		free(tmp->var);
		free(tmp);
	}
}

void	build_exit(char **str, t_struct *p)
{
	free_list(p);
	ft_putendl_fd("exit", 1);
	exit(1);
}