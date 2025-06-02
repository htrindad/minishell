/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 20:21:25 by htrindad          #+#    #+#             */
/*   Updated: 2025/06/02 17:54:58 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline void	first_case(size_t *l, t_token *new, t_ms *ms, size_t *i)
{
	new->value = NULL;
	new->cchar = set_case(ms->input);
	while (mini_spec_case(ms->input + *i, ms->scases) \
			|| ms->input[*i] == ' ')
		(*i)++;
	*l = *i;
	new->next = NULL;
}

static inline void	norm(t_ms *ms, t_token *new, size_t *l, char **value)
{
	size_t	i;

	i = *l;
	new->value = duplicator(value);
	ms->cas = 0;
	if (!new->value)
		em("Error\nMalloc fail.", ms);
	else
	{
		while (ms->input[i])
		{
			if (spec_case(ms->input, ms, l, i++))
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
	}
}

static inline void	fa_spec(char ***args)
{
	size_t	i;

	i = 1;
	while (args[i])
		free_args(args[i++]);
	free(args);
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
		norm(ms, new, l, value);
	ft_lstadd_back((t_list **)head, (t_list *)new);
	return (false);
}

void	lex_free(char ***args)
{
	size_t	i;

	i = 0;
	if (args[0])
	{
		while (args[i])
			free_args(args[i++]);
		free(args);
	}
	else
		fa_spec(args);
}
