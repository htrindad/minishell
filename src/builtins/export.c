/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:12:35 by htrindad          #+#    #+#             */
/*   Updated: 2025/04/23 17:04:46 by htrindad         ###   ########.fr       */
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

static bool	check_exp_arg(char *arg)
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

bool	bi_export(t_ms *ms)
{
	int		i;
	bool	ret;
	char	**arg;

	ret = true;
	i = 0;
	arg = ms->token->value + 1;
	while (arg[i])
	{
		if (check_exp_arg(arg[i]))
		{
			i++;
			ret = false;
			continue ;
		}
		add_env(&ms->env, arg[i]);
		i++;
	}
	return (ret);
}
