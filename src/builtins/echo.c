/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 18:27:50 by htrindad          #+#    #+#             */
/*   Updated: 2025/04/23 18:57:24 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	h_nl(char *arg)
{
	size_t	i;

	i = 0;
	if (arg && arg[i++] == '-')
	{
		while (arg[i])
		{
			if (arg[i] != 'n')
				break ;
			if (!arg[i + 1])
				return (false);
			i++;
		}
	}
	return (true);
}

int	echo(t_ms *ms)
{
	char	**arg;
	int		i;
	bool	nl;

	arg = ms->token->value + 1;
	i = -1;
	if (arg[0] == NULL)
		return (-1);
	while (!h_nl(arg[++i]))
		nl = false;
	while (arg[i + 1])
		printf("%s ", arg[i++]);
	printf("%s", arg[i]);
	if (nl)
		printf("\n");
	return (0);
}
