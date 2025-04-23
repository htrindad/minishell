/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:58:59 by htrindad          #+#    #+#             */
/*   Updated: 2025/04/23 17:03:31 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static inline bool	er_id(char *arg)
{
	perror("unset: '");
	perror(arg);
	perror("': not a valid identifier\n");
	return (true);
}

bool	check_unst(char *arg)
{
	size_t	i;

	i = 0;
	if (!ft_islpha(arg[i]) && arg[i] != '_')
		return (er_id(arg));
	while (arg[++i])
		if ((!ft_isalnum(arg[i]) && arg[i] != '_') || arg[i] == '=')
			return (er_id(arg));
	return (false);
}
