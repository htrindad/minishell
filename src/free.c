/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mely-pan <mely-pan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:32:53 by mely-pan          #+#    #+#             */
/*   Updated: 2025/04/18 16:43:34 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// A file to keep customized free() functions for lists, strings etc.

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

void	free_env(t_env *env)
{
	t_env	*tmp;

	if (!env)
		return ;
	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}

void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	if (!tokens)
		return ;
	while (tokens)
	{
		tmp = tokens;
		tokens = tokens->next;
		free(tmp->value);
		free(tmp);
	}
}

void	clean_ms(t_ms *shell)
{
	int	i;

	if (!shell)
		return ;
	free(shell->input);
	shell->input = NULL;
	i = 0;
	while (i < 5)
		free(shell->scases[i++]);
	free(shell->scases);
	free_tokens(shell->tokens);
	shell->tokens = NULL;
	free_env(shell->env);
	shell->env = NULL;
}
