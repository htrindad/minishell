/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mely-pan <mely-pan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:32:53 by mely-pan          #+#    #+#             */
/*   Updated: 2025/05/31 17:07:57 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_redirs(t_redir *redir)
{
	t_redir	*tmp;

	while (redir)
	{
		tmp = redir->next;
		if (redir->filename)
			free(redir->filename);
		free(redir);
		redir = tmp;
	}
}

void	free_fds(t_fds *fds)
{
	if (!fds)
		return;
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
	int			i;

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

// ALL BELOW IS ONLY FOR DEBUGGING PURPOSES (LATER MUST BE DELETED)

void	print_value(char **value)
{
	int	i = 0;

	if (!value)
	{
		printf("Value     : (null)\n");
		return;
	}
	printf("Value     : ");
	while (value[i])
	{
		printf("\"%s\" ", value[i]);
		i++;
	}
	printf("\n");
}

void	print_redirs(t_redir *redir, const char *label)
{
	while (redir)
	{
		printf("  [%s] %s (type: %d)\n", label, redir->filename, redir->type);
		redir = redir->next;
	}
}

void	print_fds(t_fds *fds)
{
	if (!fds)
	{
		printf("  [FDS] No redirections\n");
		return;
	}
	if (!fds->in && !fds->out)
	{
		printf("  [FDS] No input or output redirections\n");
		return;
	}
	if (fds->in)
		print_redirs(fds->in, "IN");
	if (fds->out)
		print_redirs(fds->out, "OUT");
}

void	print_tokens_debug(t_token *head)
{
	int	i = 0;

	while (head)
	{
		printf("\n=== Token #%d ===\n", i++);
		print_value(head->value);
		printf("cchar     : %d\n", head->cchar);
		print_fds(head->fds);
		printf("==========\n");
		head = head->next;
	}
}
