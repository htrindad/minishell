/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mely-pan <mely-pan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 16:19:55 by mely-pan          #+#    #+#             */
/*   Updated: 2025/08/20 00:03:18 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	have_heredocs(char *u_input, t_token *head)
{
	t_token	*curr;
	int		hd_indx;

	curr = head;
	hd_indx = 0;
	while (curr)
	{
		if (curr->fds && curr->fds->in && curr->fds->in->type == HEREDOC)
			hd_indx += get_heredoc_quotes(u_input + hd_indx, &curr->fds->in);
		curr = curr->next;
	}
}

static char	skip_quote_delim(const char *s, int *i)
{
	char	q;

	q = s[*i];
	(*i)++;
	while (s[*i] && s[*i] != q)
		(*i)++;
	if (s[*i])
		(*i)++;
	return (q);
}

static void	skip_unquoted_delim(const char *s, int *i, t_redir **tmp)
{
	while (s[*i] && s[*i] != ' ' && s[*i] != '\t'
		&& !ft_is_special_char(s[*i]) && s[*i] != '\'' && s[*i] != '\"')
		(*i)++;
	if (s[*i] == '\'' || s[*i] == '\"')
		(*tmp)->heredoc_q = true;
}

int	get_heredoc_quotes(char *input, t_redir **redir)
{
	int		i;
	t_redir	*tmp;

	i = 0;
	tmp = *redir;
	while (input[i] && tmp)
	{
		if (input[i] == '<' && input[i + 1] == '<')
		{
			i += 2;
			while (input[i] == ' ' || input[i] == '\t')
				i++;
			if (input[i] == '\'' || input[i] == '\"')
			{
				tmp->heredoc_q_type = skip_quote_delim(input, &i);
				tmp->heredoc_q = true;
			}
			else
				skip_unquoted_delim(input, &i, &tmp);
			tmp = tmp->next;
		}
		else
			i++;
	}
	return (i);
}

void	write_line_heredoc(char *line, int fd, t_ms *ms, bool quoted)
{
	char	*expanded;

	if (quoted)
		write(fd, line, ft_strlen(line));
	else
	{
		expanded = handle_env_var(line, ms);
		if (!expanded)
		{
			free(line);
			em("heredoc", ms, 0);
			return ;
		}
		write(fd, expanded, ft_strlen(expanded));
		free(expanded);
	}
}
