/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mely-pan <mely-pan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 19:32:48 by mely-pan          #+#    #+#             */
/*   Updated: 2025/08/23 21:01:50 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	ret(t_ms *shell)
{
	shell->skip = false;
	free(shell->input);
	close_hds(shell->tokens);
	free_tokens(shell->tokens);
}

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

void	*nuller(char ***args)
{
	size_t	i;

	i = 0;
	if (!args[i] && args[i + 1])
		i++;
	while (args[i])
		free_args(args[i++]);
	if (args)
		free(args);
	return (NULL);
}

void	lex_free(t_info info)
{
	size_t	i;

	i = -1;
	if (info.ptr)
	{
		while (++i < info.count)
			if (info.ptr[i])
				free_args(info.ptr[i]);
		free(info.ptr);
	}
}

void	free_pre_split(char ***split)
{
	size_t	i;

	if (split == NULL)
		return ;
	i = 0;
	if (split[i] == NULL)
		i++;
	while (split[i])
		free_args(split[i++]);
	free(split);
}
