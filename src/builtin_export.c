#include "../inc/minishell.h"

int	find_var(const char *s1, const char *s1)
{
	int	result;

	if (!s1 || !s2)
		return (0);
	result = strcmp(s1, s2);
	if (result == 0)
		return (1);
	return (0);
}

int	build_export(char **str, t_struct *p)
{
	int		i;
	t_env	*tmp;
	char	*stop_position;
	char	*compare;

	if (!str[1])
	{
		builtin_env(p);
		return (1);
	}
	i = 1;
	while (str[i])
	{
		stop_position = ft_strchr(str[i], '=');
		if (stop_position)
		{
			*stop_position = '\0';
			compare = ft_strdup(str[i]);
			if (find_var(compare, p))
			{
				/* code */
			}
			free(compare);
		}
		else
		{

		}
		i++;
	}
	return (1);
}