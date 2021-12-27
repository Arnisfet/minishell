#include "../inc/minishell.h"

void	add_env_value(char *str, t_struct *p)
{
	t_env	*tmp;

	tmp = p->my_env;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = (t_env *)malloc(sizeof(t_env));
	tmp->next->var = ft_strdup(str);
	tmp->next->value = NULL;
	tmp->next->is_blank = 1;
	tmp->next->next = NULL;
}

void	blank_and_replace(char *str, t_struct *p)
{
	t_env	*tmp;

	tmp = p->my_env;
	while (tmp != NULL)
	{
		if (find_str(str, tmp->var))
			return ;
		tmp = tmp->next;
	}
	add_env_value(str, p);
}

int	print_env(t_struct *p)
{
	t_env	*tmp;

	tmp = p->my_env;
	while (tmp != NULL)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(tmp->var, 1);
		if (tmp->value && !tmp->is_blank)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(tmp->value, 1);
			ft_putstr_fd("\"", 1);
		}
		ft_putchar_fd('\n', 1);
		tmp = tmp->next;
	}
	return (1);
}

int	build_export(char **str, t_struct *p)
{
	int		i;
	char	*equal;
	t_env	*tmp;

	if (!str[1])
	{
		print_env(p);
		return (1);
	}
	i = 1;
	tmp = p->my_env;
	while (str[i])
	{
		equal = ft_strchr(str[i], '=');
		if (equal)
			//find_and_replace(str[i], p);
			return (0);
		else
			blank_and_replace(str[i], p);
		i++;
	}
	return (1);
}
