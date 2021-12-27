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
		tmp->is_blank = 0;
		if (flag == 1)
			tmp->next->is_blank = 1;
		else
			tmp->next->is_blank = 0;
		tmp->next = NULL;
	}
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = (t_env *)malloc(sizeof(t_env));
		tmp->next->var = ft_strdup(str);
		tmp->next->value = NULL;
		if (flag == 1)
			tmp->next->is_blank = 1;
		else
			tmp->next->is_blank = 0;
		tmp->next->next = NULL;
	}
}

void	add_value_to_env(char *str, t_struct *p)
{
	t_env	*tmp;
	char	**splitted;

	tmp = p->my_env;
	splitted = ft_split(str, '=');
	if (tmp == NULL)
	{
		tmp = (t_env *)malloc(sizeof(t_env));
		tmp->var = ft_strdup(splitted[0]);
		if (splitted[1])
			tmp->value = splitted[1];
		else
			tmp->value = NULL;
		tmp->is_blank = 0;
		tmp->next = NULL;
	}
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = (t_env *)malloc(sizeof(t_env));
		tmp->var = ft_strdup(splitted[0]);
		if (splitted[1])
			tmp->value = splitted[1];
		else
			tmp->value = NULL;
		tmp->next->is_blank = 0;
		tmp->next->next = NULL;
	}
	clean_split_tmp(splitted);
}

void	update_value(char *position, t_env *tmp, int flag)
{
	if (tmp->value)
		free(tmp->value);
	if (flag)
		tmp->value = ft_strdup(position);	
	else
		tmp->value = NULL;
	tmp->next->is_blank = 0;
}


void	find_and_replace(char *str, t_struct *p)
{
	char	*position;
	t_env	*tmp;

	tmp = p->my_env;
	while (tmp != NULL)
	{
		position = ft_strchr(str, '=');
		*position = '\0';
		if (find_str(str, tmp->var))
		{
			*position = '=';
			position++;
			if (position)
				update_value(position, tmp, 0);
			else
				update_value(position, tmp, 1);
		}
		else
		{
			*position = '=';
			position++;
			if (position)
				add_value_to_env(str, p);
			else
			{
				position--;
				*position = '\0';
				add_null_value(str, p, 2);
			}
		}
		tmp = tmp->next;
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
			find_and_replace(str[i], p);
		else
			blank_and_replace(str[i], p);
		i++;
	}
	return (1);
}
