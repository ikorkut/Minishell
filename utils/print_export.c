/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikorkut <ikorkut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 20:40:34 by egokeri           #+#    #+#             */
/*   Updated: 2023/10/27 15:56:37 by ikorkut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_export(void)
{
	char	**env;

	env = g_ms.env;
	while (*env)
	{
		printf("declare -x %s\n", *env);
		env++;
	}
	if (!is_parent())
		exit (EXIT_SUCCESS);
}
