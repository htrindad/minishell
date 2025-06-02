/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 19:55:58 by htrindad          #+#    #+#             */
/*   Updated: 2025/05/31 19:56:53 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	rm_finisher(t_env *curr, t_env **head)
{
	t_env	*prev;
	t_env	*next;

	prev = curr->prev;
	next = curr->next;
	if (prev)
		prev->next = next;
	if (next)
		next->prev = prev;
	if (curr == *head)
		*head = next;
	free(curr->key);
	free(curr->value);
	free(curr);
}
