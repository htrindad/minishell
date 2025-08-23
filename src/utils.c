/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrindad <htrindad@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 20:45:57 by htrindad          #+#    #+#             */
/*   Updated: 2025/08/23 20:46:33 by htrindad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_info	empty_info(void)
{
	t_info	inf;

	inf.ptr = NULL;
	inf.count = 0;
	return (inf);
}
