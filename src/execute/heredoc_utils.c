/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mely-pan <mely-pan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 16:19:55 by mely-pan          #+#    #+#             */
/*   Updated: 2025/06/14 16:19:56 by mely-pan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	skip_quote_delim(const char *s, int *i)
{
	char	q;

	q = s[*i];
	(*i)++;
	while (s[*i] && s[*i] != q)
		(*i)++;
	if (s[*i])
		(*i)++;
}

static void	skip_unquoted_delim(const char *s, int *i)
{
	while (s[*i] && s[*i] != ' ' && s[*i] != '\t'
		&& ft_is_special_char(s[*i]))
		(*i)++;
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
				skip_quote_delim(input, &i);
				tmp->heredoc_q = true;
			}
			else
				skip_unquoted_delim(input, &i);
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
			em("heredoc", ms);
			return ;
		}
		write(fd, expanded, ft_strlen(expanded));
		free(expanded);
	}
}
