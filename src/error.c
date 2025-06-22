/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:10:45 by htrindad          #+#    #+#             */
/*   Updated: 2025/06/22 17:07:46 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	em(char *str, t_ms *ms)
{
	perror(str);
	ms->running = false;
}

t_ms	**b_ms(void)
{
	static t_ms	*ms;

	return (&ms);
}

bool	*in_heredoc(void)
{
	static bool	in = false;

	return (&in);
}

int	check_parse_error(t_ms *ms)
{
	int	i;

	i = 0;
	while (ms->input[i])
		i++;
	i--;
	while (i > 0 && (ms->input[i] == 32 || (ms->input[i] > 8 \
			&& ms->input[i] < 14)))
		i--;
	if (ft_is_special_char(ms->input[i]))
	{
		*es() = 2;
		perror("Parse error");
		return (1);
	}
	return (0);
}
