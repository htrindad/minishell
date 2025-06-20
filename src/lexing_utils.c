/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mely-pan <mely-pan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 20:21:25 by htrindad          #+#    #+#             */
/*   Updated: 2025/06/19 18:02:51 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline void	first_case(size_t *l, t_token *new, t_ms *ms, size_t *i)
{
	new->value = NULL;
	while (ms->input[*i] == ' ')
		(*i)++;
	new->cchar = set_case(ms->input + *i);
	while (mini_spec_case(ms->input + *i, ms->scases) \
			|| ms->input[*i] == ' ')
		(*i)++;
	*l = *i;
	new->next = NULL;
}

static inline void	norm(t_ms *ms, t_token *new, char **value)
{
	size_t	i;

	i = *counter();
	new->value = duplicator(value);
	ms->cas = 0;
	if (!new->value)
		em("Error\nMalloc fail.", ms);
	else
	{
		while (ms->input[i])
		{
			if (spec_case(ms->input, ms, counter(), i++))
			{
				new->cchar = set_case(ms->input + *counter());
				break ;
			}
		}
		if (new->cchar != APPEND && new->cchar != HEREDOC)
			(*counter())++;
		else
			*counter() += 2;
		new->next = NULL;
	}
}

void	fa_spec(char ***args)
{
	size_t	i;

	i = 1;
	while (args[i])
		free_args(args[i++]);
	free(args);
}

bool	add_token(t_token **head, char **value, t_ms *ms)
{
	t_token	*new;
	size_t	i;

	i = *counter();
	new = ft_calloc(1, sizeof(t_token));
	if (!new)
		return (em("Error:\nMalloc failed\n", ms), true);
	new->is_redir = false;
	new->fds = NULL;
	if (f_spec_case(ms->input, counter(), ms->scases))
		first_case(counter(), new, ms, &i);
	else
		norm(ms, new, value);
	ft_lstadd_back((t_list **)head, (t_list *)new);
	return (false);
}

bool	ft_is_special_char(int c)
{
	if (c == '<' || c == '>' || c == '|')
		return (true);
	return (false);
}
