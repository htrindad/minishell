/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:46:43 by htrindad          #+#    #+#             */
/*   Updated: 2025/04/21 18:18:51 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*comp_path(char **arg, t_env *env, t_ms *ms)
{
	char	*str;

	while (env)
	{
		if (ft_strncmp(env->key, "PATH", 4))
		{
			env = env->next;
			break ;
		}

	}
	str = ft_strjoin(env->value, arg[0]);
	if (str == NULL)
		return (em("Error\nMalloc Fail.\n", ms), NULL);
	return (str);
}

static char	**comp_env(t_env *env)
{
	char	**ptr;
	char	*tmp;
	size_t	i;
	size_t	j;

	i = ft_lstsize((t_list *)env);
	j = 0;
	ptr = ft_calloc(i + 1, sizeof(char *));
	if (ptr == NULL)
		return (NULL);
	ptr[i] = NULL;
	while (j < i)
	{
		tmp = ft_calloc(ft_strlen(env->key) + ft_strlen(env->value) + 2);
		if (tmp == NULL)
			return (NULL);
		ft_strlcat(tmp, env->key, ft_strlen(env->key));
		ft_strlcat(tmp, "=", 1);
		ft_strlcat(tmp, env->value, ft_strlen(env->value));
		ptr[j] = ft_strdup(tmp);
		free(tmp);
		if (ptr[j++] == NULL)
			return (free_args(ptr), NULL);
	}
	return (ptr);
}

static void	han_case(t_token *tok) //In case it is not meant to output to stdout
{
	//TODO
}

static void	ex_loop(t_ms *ms, t_token *tok, char **env) //It will run while we have commands
{
	char	*tmp;

	tmp = comp_path(ms->tokens, ms->env, ms);
	if (tmp == NULL)
	{
		em("Error\nMalloc Fail.\n", ms);
		return ;
	}
	while (tok)
	{
		if (tok->cchar != OUT)
			//TODO
		ms->pid = fork();
		if (!ms->pid)
			execve(tmp, ms->tokens->value, env);
		else
			wait();
		tok = tok->next;
	}
	free(tmp);
}

void	executor(t_ms *ms) //This is the function that will execute the commands from the parsing
{
	char	**env;

	env = comp_env(ms->env);
	if (env == NULL)
	{
		em("Error\nMalloc Fail.\n", ms);
		return ;
	}
	ex_loop(ms, ms->token, env);
	free_args(env);
}
