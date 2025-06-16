/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:10:45 by htrindad          #+#    #+#             */
/*   Updated: 2025/06/16 20:51:29 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	em(char *str, t_ms *ms)
{
	perror(str);
	ms->running = false;
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
