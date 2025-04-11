/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ms.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mely-pan <mely-pan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:33:21 by mely-pan          #+#    #+#             */
/*   Updated: 2025/03/27 19:15:23 by mely-pan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_ms(t_ms *shell)
{
	shell = ft_calloc((size_t)1, sizeof(t_ms));
	shell->env = NULL;
	shell->input = NULL;
	shell->last_status = 0;
	shell->tokens = NULL;
}
