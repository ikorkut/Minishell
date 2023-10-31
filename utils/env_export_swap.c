/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_export_swap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egokeri <egokeri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 12:46:46 by egokeri           #+#    #+#             */
/*   Updated: 2023/10/31 12:47:38 by egokeri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	swap_export(int pos, char *input)
{
	char	*temp;

	temp = g_ms.export[pos];
	g_ms.export[pos] = ft_strdup(input);
	free(temp);
}

void	swap_env(int pos, char *input)
{
	char	*temp;

	temp = g_ms.env[pos];
	g_ms.env[pos] = ft_strdup(input);
	free(temp);
}
