/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ecpeu.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:35:03 by htrindad          #+#    #+#             */
/*   Updated: 2025/04/23 16:29:01 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	quit(t_ms *ms)
{
	(*ms)->running = false;
	return (0);
}

int	env(t_ms *ms)
{
	t_env	*env;

	env = ms->env;
	while (env)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (0);
}

int	pwd(t_ms *ms)
{
	t_env	*env;

	env = ms->env;
	while (1)
	{
		if (!ft_strncmp(ms->key, "PWD", 3) || !env)
			break ;
		env = env->next;
	}
	if (env == NULL)
		return (-1);
	printf("%s=%s\n", env->key, env->value);
	return (0);
}

int	change_dir(t_ms *ms)
{
	char	c[PATH_MAX];
	t_token	*tok;

	tok = ms->token;
	if (tok->value[1] == NULL)
	{
		tok->value[1] = get_home(ms->env);
		if (tok->value == NULL)
			return (printf("cd: HOME not set\n"));
	}
	getcwd(c, sizeof(c));
	if (chdir(tok->value[1] < 0))
	{
		if (!tok->value[1][0])
			return (-1);
		perror("cd: ");
		perror(tok->value[1]);
		perror(": No such file or directory\n");
		return (-1);
	}
}

bool	bi_export(t_ms *ms)
{
	char	**str;
	int		i;
	int		ret;
	char	**arg;

	ret = true;
	i = 0;
	arg = ms->token->value;
	while (arg[i])
	{
		if (check_exp_arg(arg))
		{
			i++;
			continue ;
			ret = false;
		}
		str = ft_split(arg, '=');
		
	}
	return (ret);
}
