/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 14:51:54 by htrindad          #+#    #+#             */
/*   Updated: 2025/08/23 19:27:21 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	spec_case_middle(char const *s, size_t i, char **cases)
{
	bool	qc;

	while (i)
	{
		qc = mini_spec_case(s + i--, cases);
		if (s[i] != ' ' && qc)
			return (false);
		if (qc)
			return (true);
	}
	return (false);
}

t_info	empty_spli(void)
{
	t_info	spli;

	spli.count = 0;
	spli.ptr = NULL;
	return (spli);
}
