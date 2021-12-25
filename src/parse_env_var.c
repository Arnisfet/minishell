#include "../inc/minishell.h"

char	*dollar(char *command, char *line, int i, t_struct *p)
{
	char	*var;
	int		j;

	j = i;
	while(line[i] != ' ' && line[i] != '\0')
	{
		var = ft_realloc_ch(var, line[j]);
		if (line[i] == '\'' || line[i] == '"')
		{
			free(var);
			parse_revert(var, line, i ,p);
		}
		j++;
		p->count++;
	}
}