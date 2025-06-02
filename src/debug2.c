/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mely-pan <mely-pan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 19:50:00 by mely-pan          #+#    #+#             */
/*   Updated: 2025/06/02 19:50:37 by mely-pan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

static inline void	print_type(t_case ccase)
{
	if (ccase == NONE)
		printf("NONE ");
	if (ccase == OUT)
		printf("OUT ");
	if (ccase == IN)
		printf("IN ");
	if (ccase == PIPE)
		printf("PIPE ");
	if (ccase == HEREDOC)
		printf("HEREDOC ");
	if (ccase == APPEND)
		printf("APPEND");
}

void	print_tokens(t_token *head)
{
	t_token	*tmp;
	size_t	i;

	tmp = head;
	while (tmp)
	{
		i = 0;
		printf("(");
		while (tmp->value && tmp->value[i])
			printf("[%s]", tmp->value[i++]);
		printf(") ");
		print_type(tmp->cchar);
		tmp = tmp->next;
	}
	printf("\n");
}
