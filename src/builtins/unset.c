/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:58:59 by htrindad          #+#    #+#             */
/*   Updated: 2025/08/19 19:33:49 by htrindad         ###   ########.fr       */
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

char	*tilt(char *old, char *home)
{
	const size_t	h_size = ft_strlen(home) + 1;
	size_t			size;
	char			*new;

	size = h_size;
	if (old)
		size += ft_strlen(old + 1) + 2;
	new = ft_calloc(size, 1);
	if (new == NULL)
		return (NULL);
	ft_strlcpy(new, home, h_size);
	if (old)
		(ft_strlcat(new, "/", h_size + 1), ft_strlcat(new, old + 1, size));
	free(old);
	return (new);
}

static inline bool	clean(char **new, t_ms *ms)
{
	free_args(new);
	return (em("Malloc fail.", ms, 0), true);
}

bool	rearchitect(char ***matrix, t_ms *ms)
{
	char	**new;
	size_t	counter;
	size_t	i;

	counter = 0;
	while ((*matrix)[counter])
		counter++;
	new = ft_calloc(++counter + 1, sizeof(char *));
	if (new == NULL)
		return (em("Malloc fail.", ms, 0), true);
	i = 0;
	new[counter--] = NULL;
	while (i <= counter)
	{
		if (i == counter)
			new[i] = ft_strdup(ms->home);
		else
			new[i] = ft_strdup((*matrix)[i]);
		if (new[i++] == NULL)
			return (clean(new, ms));
	}
	free_args(*matrix);
	*matrix = new;
	return (false);
}

bool	check_unst(char *arg)
{
	size_t	i;

	i = 0;
	if (!ft_isalpha(arg[i]) && arg[i] != '_')
		return (er_id(arg));
	while (arg[++i])
		if ((!ft_isalnum(arg[i]) && arg[i] != '_') || arg[i] == '=')
			return (er_id(arg));
	return (false);
}
