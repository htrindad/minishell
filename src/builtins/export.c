/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:12:35 by htrindad          #+#    #+#             */
/*   Updated: 2025/04/23 16:26:44 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static inline bool	error_chk(char *arg)
{
	perror("export: '");
	perror(arg);
	perror("': not a valid identifier\n");
	return (true);
}

bool	check_exp_arg(char *arg)
{
	int	i;

	i = 0;
	if (!ft_isalpha(arg[i]) && arg[i] != '_')
		return (error_chk(arg));
	i++;
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (error_chk(arg));
		i++;
	}
	return (false);
}

void	add_var(char **var)
{
	
}
