/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_export_len.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egokeri <egokeri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 12:46:43 by egokeri           #+#    #+#             */
/*   Updated: 2023/10/31 12:47:59 by egokeri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	env_len(void)
{
	char	**env;

	env = g_ms.env;
	while (*env)
		env++;
	return (env - g_ms.env);
}

int	export_len(void)
{
	char	**export;

	export = g_ms.export;
	while (*export)
		export++;
	return (export - g_ms.export);
}
