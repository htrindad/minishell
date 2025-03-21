#include "../minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_ms	shell;
	(void)argv;

	if (argc != 1)
		ft_putstr_fd("Run ./minishell with no args!", 2);
	init_ms(&shell);
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
		lexing(&shell, env);

		free(shell.input);
	}
	return (0);
}
