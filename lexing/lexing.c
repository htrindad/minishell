#include "./minishell.h"

//The Purpose of lexing is to separate the user input into tokens the
//same way the shell does, for that we must have in consideration quotes,
//special characteres (>, <, |, >>, <<), spaces and $.

int	add_token(t_token **head, char *value)
{
	t_token	*new;
	t_token	*last;

	new = (t_token *)malloc(sizeof (t_token));
	if (!new)
		return (0);
	new->value = ft_strdup(value);
	if (!new->value)
		return (free(new), 0);
	new->next = NULL;
	if (!*head)
		*head = new;
	else
	{
		last = *head;
		while (last->next)
			last = last->next;
		last->next = new;
	}
	return (1);
}


t_token	*lexing(t_ms *shell)
{
	t_token *head;
	char	**args;
	int		i;

	head = NULL;
	args = ft_split_shell(shell->input);
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
