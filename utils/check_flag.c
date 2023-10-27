/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_flag.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egokeri <egokeri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 12:40:41 by egokeri           #+#    #+#             */
/*   Updated: 2023/10/27 12:45:03 by egokeri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_flag(void)
{
	if (g_ms.check_flag == 1)
		errno = 4;
	if (g_ms.check_flag == 1)
	{
		errno = 1;
		g_ms.check_flag = 0;
	}
}
