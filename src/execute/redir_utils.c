/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mely-pan <mely-pan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 20:33:47 by mely-pan          #+#    #+#             */
/*   Updated: 2025/06/14 16:32:23 by mely-pan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	remove_token(t_token **head, t_token *to_remove)
{
	t_token	*prev;
	t_token	*curr;

	prev = NULL;
	curr = *head;
	while (curr)
	{
		if (curr == to_remove)
		{
			if (prev)
				prev->next = curr->next;
			else
				*head = curr->next;
			free_args(curr->value);
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

static int	dup_and_check(char **dest, char *src, char **to_free)
{
	int	i;

	i = 0;
	*dest = ft_strdup(src);
	if (!*dest)
	{
		free_args(to_free);
		return (1);
	}
	return (0);
}

static int	shift_args_left(char **args, t_token *token)
{
	int		i;
	int		j;
	char	**new_value;

	j = 0;
	while (token->value && token->value[j])
		j++;
	i = 1;
	while (args[i++])
		j++;
	new_value = ft_calloc(sizeof(char *), j + 1);
	if (!new_value)
		return (1);
	new_value[j] = NULL;
	j = 0;
	i = -1;
	while (token->value[++i])
		if (dup_and_check(&new_value[i], token->value[i], new_value))
			return (1);
	while (args[++j])
		if (dup_and_check(&new_value[i++], args[j], new_value))
			return (1);
	free_args(token->value);
	token->value = new_value;
	return (0);
}

static int	remove_redir(t_token *token)
{
	t_token	*file;

	file = token->next;
	if (file && file->value && file->value[0] && file->value[1] && token)
		if (shift_args_left(file->value, token))
			return (1);
	if (file)
	{
		token->next = file->next;
		token->cchar = file->cchar;
		free_args(file->value);
		free(file);
	}
	else
		token->cchar = NONE;
	return (0);
}

int	cleanup_redir(t_token **tokens)
{
	t_token	*curr;
	t_token	*prev;

	curr = *tokens;
	prev = NULL;
	while (curr)
	{
		if (is_redirection(curr->cchar))
		{
			if (remove_redir(curr))
				return (1);
			if (prev)
				curr = prev;
			else
				curr = *tokens;
		}
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
	return (0);
}
