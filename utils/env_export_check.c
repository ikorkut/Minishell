/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_export_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egokeri <egokeri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 12:46:38 by egokeri           #+#    #+#             */
/*   Updated: 2023/10/31 12:48:45 by egokeri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_export(char *str)
{
	char	**export;

	export = g_ms.export;
	while (*export)
	{
		if (ft_strcmp(*export, str) || export_pos(str, *export))
			return (FALSE);
		export++;
	}
	return (TRUE);
}

int	check_env(char *str)
{
	char	*head;

	head = ft_strchr(str, '=');
	if (!head)
	{
		if (check_export(str))
			add_export(str);
		return (FALSE);
	}
	if (head == str)
		return (FALSE);
	while (*str)
	{
		if (is_whitespace(*str))
			return (FALSE);
		str++;
	}
	return (TRUE);
}
