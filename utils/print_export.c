/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egokeri <egokeri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 20:40:34 by egokeri           #+#    #+#             */
/*   Updated: 2023/10/31 11:55:45 by egokeri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_export(void)
{
	char	**export;

	export = g_ms.export;
	while (*export)
	{
		printf("declare -x %s\n", *export);
		export++;
	}
	if (is_child())
		exit (EXIT_SUCCESS);
}
