/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikorkut <ikorkut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 20:37:04 by egokeri           #+#    #+#             */
/*   Updated: 2023/11/02 15:26:25 by ikorkut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_export(char *str)
{
	int		i;
	char	**export;
	char	**new_export;

	i = 0;
	export = g_ms.export;
	new_export = ft_calloc(sizeof(char **), export_len() + 2);
	while (export[i])
	{
		new_export[i] = ft_strdup(export[i]);
		i++;
	}
	new_export[i] = ft_strdup(str);
	free_array(g_ms.export);
	g_ms.export = new_export;
}

int	export_pos(char *str, char *export)
{
	int		pos;
	char	*tmp;

	pos = 0;
	while (export[pos] && export[pos] != '=')
		pos++;
	tmp = ft_substr(export, 0, pos);
	if (ft_strcmp(tmp, str))
	{
		free (tmp);
		return (TRUE);
	}
	free (tmp);
	return (FALSE);
}

void	add_env(char *str)
{
	int		i;
	char	**env;
	char	**new_env;

	i = 0;
	env = g_ms.env;
	new_env = ft_calloc(sizeof(char **), env_len() + 2);
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i] = ft_strdup(str);
	free_array(g_ms.env);
	g_ms.env = new_env;
}

void	add_export_env(char **input)
{
	int		pos_env;
	int		pos_export;

	if (check_env(*input))
	{
		pos_env = is_include_env(*input);
		pos_export = is_include_export(*input);
		if (pos_env != -1)
			swap_env(pos_env, *input);
		if (pos_export != -1)
			swap_export(pos_export, *input);
		if (pos_env == -1)
		{
			if (export_check_char(*input))
				add_env(*input);
			else
			{
				export_err(*input);
				return ;
			}
		}
		if (pos_export == -1)
		{
			if (export_check_char(*input))
				add_export(*input);
			else
			{
				export_err(*input);
				return ;
			}
		}
	}
}

void	builtin_export(char **input)
{
	input++;
	if (!*input)
		print_export();
	while (*input)
	{
		add_export_env(input);
		input++;
	}
	set_paths();
	if (is_child())
		exit (EXIT_SUCCESS);
}
