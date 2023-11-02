/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_export_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikorkut <ikorkut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 12:46:38 by egokeri           #+#    #+#             */
/*   Updated: 2023/11/02 15:08:42 by ikorkut          ###   ########.fr       */
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

int export_check_char(char *str)
{
	int	i = 1;
	
	if(!ft_isalpha(str[0]))
		return FALSE;
	while(str[i])
	{
		if(!ft_isalnum(str[i]))
			return FALSE;
		i++;
	}
	return	TRUE;
}

int	check_env(char *str)
{
	char	*head;

	head = ft_strchr(str, '=');
	if (!head)
	{
		if (check_export(str))
		{
			if(export_check_char(str))
				add_export(str);
			else
				export_err(str);
				
		}
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
