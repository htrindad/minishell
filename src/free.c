/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mely-pan <mely-pan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:32:53 by mely-pan          #+#    #+#             */
/*   Updated: 2025/05/31 19:34:25 by mely-pan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_fds(t_fds *fds)
{
	if (!fds)
		return ;
	if (fds->in)
		free_redirs(fds->in);
	if (fds->out)
		free_redirs(fds->out);
	free(fds);
}

void	free_args(char **args)
{
	int	i;

	if (!args)
		return ;
	i = 0;
	while (args[i])
		free(args[i++]);
	free(args);
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
		tmp = tokens->next;
		if (tokens->value)
			free_args(tokens->value);
		if (tokens->fds)
			free_fds(tokens->fds);
		free(tokens);
		tokens = tmp;
	}
}

void	clean_ms(t_ms *shell)
{
	int	i;

	if (!shell)
		return ;
	i = 0;
	while (i < 5)
		free(shell->scases[i++]);
	free(shell->scases);
	shell->tokens = NULL;
	free_env(shell->env);
	free_tokens(shell->tokens);
	shell->env = NULL;
	free(shell->builtin);
	free(shell);
}
