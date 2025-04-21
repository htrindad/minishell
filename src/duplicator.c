/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   duplicator.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:08:59 by htrindad          #+#    #+#             */
/*   Updated: 2025/04/14 18:13:52 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**duplicator(char **arg)
{
	size_t	max;
	size_t	i;
	char	**ptr;

	max = 0;
	i = 0;
	while (arg[max])
		max++;
	ptr = ft_calloc(max + 1, sizeof(char *));
	while (i < max)
	{
		ptr[i] = ft_strdup(arg[i]);
		i++;
	}
	ptr[max] = NULL;
	return (ptr);
}
