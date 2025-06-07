/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mely-pan <mely-pan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 19:32:48 by mely-pan          #+#    #+#             */
/*   Updated: 2025/06/07 17:40:20 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	ret(t_ms *shell)
{
	free(shell->input);
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
