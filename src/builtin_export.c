#include "../inc/minishell.h"

void	add_null_value(char *str, t_struct *p, int flag)
{
	t_env	*tmp;

	tmp = p->my_env;
	if (tmp == NULL)
	{
		tmp = (t_env *)malloc(sizeof(t_env));
		tmp->var = ft_strdup(str);
		tmp->value = NULL;
		tmp->is_blank = 1;
		tmp->next = NULL;
	}
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = (t_env *)malloc(sizeof(t_env));
		tmp->next->var = ft_strdup(str);
		tmp->next->value = NULL;
		tmp->next->is_blank = 1;
		tmp->next->next = NULL;
	}
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
	add_null_value(str, p, 1);
}

int	print_env(t_struct *p)
{
	t_env	*tmp;

	tmp = p->my_env;
	while (tmp != NULL)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(tmp->var, 1);
		if (!tmp->is_blank)
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

int	check_var(char *str, t_struct *p)
{
	t_env	*tmp;

	tmp = p->my_env;
	while (tmp != NULL)
	{
		if (find_str(str, tmp->var))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	exist_add(char *var, char *value, t_struct *p, int flag)
{
	t_env	*tmp;

	tmp = p->my_env;
	while (tmp != NULL)
	{
		if (find_str(var, tmp->var))
		{
			if (flag)
			{
				if (tmp->value)
					free(tmp->value);
				tmp->value = NULL;
				tmp->is_blank = 0;
			}
			else
			{
				if (tmp->value)
					free(tmp->value);
				tmp->value = ft_strdup(value);
				tmp->is_blank = 0;
			}
		}
		tmp = tmp->next;
	}
}

void	addition_var(char *var, char *value, t_struct *p, int flag)
{
	t_env	*tmp;

	tmp = p->my_env;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = (t_env *)malloc(sizeof(t_env));
	tmp->next->var = ft_strdup(var);
	if (flag)
	{
		tmp->next->value = NULL;
		tmp->next->is_blank = 0;
	}
	else
	{
		tmp->next->value = ft_strdup(value);
		tmp->next->is_blank = 0;
	}
}

void	add_new(char *var, char *value, t_struct *p, int flag)
{
	t_env	*tmp;

	tmp = p->my_env;
	if (tmp == NULL)
	{
		tmp = (t_env *)malloc(sizeof(t_env));
		tmp->var = ft_strdup(var);
		if (flag)
		{
			tmp->value = NULL;
			tmp->is_blank = 1;
		}
		else
		{
			tmp->value = ft_strdup(value);
			tmp->is_blank = 0;
		}
		tmp->next = NULL;
	}
	else
		addition_var(var, value, p, flag);
}

void	find_and_update(char *str, t_struct *p)
{
	char	*stop_position;

	stop_position = ft_strchr(str, '=');
	*stop_position = '\0';
	if (check_var(str, p))
	{
		stop_position++;
		if (*stop_position)
			exist_add(str, stop_position, p, 0);
		else
			exist_add(str, stop_position, p, 1);
	}
	else
	{
		stop_position++;
		if (*stop_position)
			add_new(str, stop_position, p, 0);
		else
			add_new(str, stop_position, p, 1);
	}
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
			find_and_update(str[i], p);
		else
			blank_and_replace(str[i], p);
		i++;
	}
	return (1);
}
