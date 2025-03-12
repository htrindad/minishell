#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libs/neo_libft/libft.h"
# include <signal.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct  s_ms
{
	char	**env;
	char	*input;
	int		pid;
	int		last_exit_stat;
	t_token	*tokens;
}	t_ms;

typedef struct  s_token
{
	char	*value;
	int		type;;
	t_token	*next;
}	t_token;

t_token	*lexing(const char *input);
int		add_token(t_token **head, char *value);

void	free_args(char **args);



#endif