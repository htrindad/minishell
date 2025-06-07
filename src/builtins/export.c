/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:12:35 by htrindad          #+#    #+#             */
/*   Updated: 2025/06/07 16:22:33 by htrindad         ###   ########.fr       */
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

static void	no_args(t_env *env)
{
	while (env)
	{
		printf("declare -x %s", env->key);
		if (env->value != NULL)
			printf("=%s", env->value);
		printf("\n");
		env = env->next;
	}
}

static inline bool	replace(char *arg, t_env *env)
{
	size_t	i;
	char	*tmp;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	if (!arg[i])
		return (false);
	tmp = ft_substr(arg, 0, i);
	if (tmp == NULL)
		return (true);
	rm_env(&env, tmp);
	free(tmp);
	return (false);
}

int	bi_export(t_ms *ms)
{
	int		i;
	bool	ret;
	char	**arg;

	ret = 0;
	i = 0;
	arg = ms->tokens->value + 1;
	if (!ms->tokens->value[1])
		return (no_args(ms->env), 0);
	if (replace(arg[0], ms->env))
		return (1);
	while (arg[i])
	{
		if (check_exp_arg(arg[i]))
		{
			i++;
			ret = 1;
			continue ;
		}
		add_env(&ms->env, arg[i]);
		i++;
	}
	return (ret);
}
