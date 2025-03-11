#include "./minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_ms	shell;
	(void)argv;

	if (argc != 1)
		ft_putstr_fd("Run ./minishell with no args!", 2);
	ft_calloc(&shell, sizeof(t_ms));
	while (1)
	{
		shell.input = readline("minishell> ");
		if (!shell.input)
		{
			printf("exit\n");
			break ;
		}
		if (shell.input)
			add_history(shell.input);
		shell.tokens = lexing(shell.input);
		
		free(shell.input);
	}
}
