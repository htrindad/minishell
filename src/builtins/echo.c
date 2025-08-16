/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mely-pan <mely-pan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 18:27:50 by htrindad          #+#    #+#             */
/*   Updated: 2025/08/16 21:28:24 by htrindad         ###   ########.fr       */
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

int	echo(char **arg)
{
	int		i;
	bool	nl;

	i = -1;
	nl = true;
	if (arg[0] == NULL)
	{
		printf("\n");
		return (0);
	}
	while (!h_nl(arg[++i]))
		nl = false;
	if (arg[i] == NULL)
		return (0);
	while (arg[i + 1])
		printf("%s ", arg[i++]);
	printf("%s", arg[i]);
	if (nl)
		printf("\n");
	return (0);
}
