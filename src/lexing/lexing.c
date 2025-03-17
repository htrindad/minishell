#include "../../minishell.h"

//The Purpose of lexing is to separate the user input into tokens the
//same way the shell does, for that we must have in consideration quotes,
//special characteres (>, <, |, >>, <<), spaces and $.
//The tokens will be stored in a linked list of t_token structs.

int	add_token(t_token **head, char *value)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof (t_token));
	if (!new)
		return (0);
	new->value = ft_strdup(value);
	if (!new->value)
		return (free(new), 0);
	new->next = NULL;
	ft_lstadd_back((t_list **)head, (t_list *)new);
	return (1);
}

void	lexing(t_ms *shell, char **env)
{
	t_token *head;
	char	**args;
	int		i;

	head = NULL;
	shell->env = get_env(env);
	args = ft_split_shell(shell->input, shell->env);
	if (!args)
		return (NULL);
	i = 0;
	while (args[i])
	{
		if (!add_token(&head, args[i]));
		{
			free_list(&head);
			break ;
		}
		i++;
	}
	free_splited(args);
	return (head);
}
