#include "./minishell.h"

//A file to keep customized free() functions for lists, strings etc.

void	free_args(char **args)
{
	int	i;

	i = 0;
	if (args)
	{
		while (args[i])
			free(args[i++]);
		free(args);
	}
}
