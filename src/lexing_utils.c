/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 20:21:25 by htrindad          #+#    #+#             */
/*   Updated: 2025/05/31 20:26:48 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline void	first_case(size_t *l, t_token *new, t_ms *ms, size_t *i)
{
	new->value = NULL;
	new->cchar = set_case(ms->input);
	while (mini_spec_case(ms->input + *i, ms->scases) \
			|| ms->input[i] == ' ')
		(*i)++;
	*l = *i;
	new->next = NULL;
	ft_lstadd_back((t_list **)head, (t_list *)new);
}

static inline int	norm(t_ms *ms, t_token *new, size_t *l, char **value, size_t *i);
{
	new->value = duplicator(value);
	if (!new->value)
		return (em("Error\nMalloc fail.\n", ms), true);
	while (ms->input[*i])
	{
		if (spec_case(ms->input, ms->scases, l, (*i)++, NULL))
		{
			new->cchar = set_case(ms->input + *l);
			break ;
		}
	}
	if (new->cchar != APPEND && new->cchar != HEREDOC)
		(*l)++;
	else
		(*l) += 2;
	new->next = NULL;
	ft_lstadd_back((t_list **)head, (t_list *)new);
}

bool	add_token(t_token **head, char **value, t_ms *ms, size_t *l)
{
	t_token	*new;
	size_t	i;

	i = *l;
	new = ft_calloc(1, sizeof(t_token));
	if (!new)
		return (em("Error:\nMalloc failed\n", ms), true);
	new->is_redir = false;
	if (!(*l) && mini_spec_case(ms->input, ms->scases))
		first_case(l, new, ms, &i);
	else
		norm(ms, new, l, value, &i);
	return (false);
}

