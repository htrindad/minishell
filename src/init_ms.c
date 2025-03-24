#include "minishell.h"

void	init_ms(t_ms *shell)
{
	ft_calloc((size_t)1, sizeof(t_ms));
	shell->env = NULL;
	shell->input = NULL;
	shell->last_status = 0;
	shell->tokens = NULL;
}
