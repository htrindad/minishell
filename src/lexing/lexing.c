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

void	print_tokens(t_token *head)
{
	t_token	*tmp;

	tmp = head;
	while (tmp)
	{
		printf("[%s]\n", tmp->value);
		tmp = tmp->next;
	}
}

void	lexing(t_ms *shell, char **env)
{
	t_token *head;
	char	**args;
	int		i;

	head = NULL;
	shell->env = get_env(env);
	args = ft_split_shell(shell);
	if (!args)
		return ;
	i = 0;
	while (args[i])
	{
		if (!add_token(&head, args[i]))
		{
			free_tokens(head);
			break ;
		}
		i++;
	}
	print_tokens(head);
	free_tokens(head);
	free_args(args);
	return ;
}
