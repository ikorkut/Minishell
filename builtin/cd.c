/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egokeri <egokeri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 20:36:46 by egokeri           #+#    #+#             */
/*   Updated: 2023/10/26 20:36:47 by egokeri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_pwd(char **env, char *pwd, char *type)
{
	int		i;
	char	*new_env;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], type, ft_strlen(type)) == 0)
		{
			new_env = malloc(ft_strlen(pwd) + ft_strlen(type) + 1);
			if (new_env)
			{
				ft_strcpy(new_env, type);
				ft_strcat(new_env, pwd);
				free(pwd);
				free(env[i]);
				env[i] = new_env;
			}
			break ;
		}
		i++;
	}
}

void	set_pwd(void)
{
	change_pwd(g_ms.env, get_env("PWD"), "OLDPWD=");
	change_pwd(g_ms.env, getcwd(NULL, 0), "PWD=");
}

void	builtin_cd(char **input)
{
	char	*home;

	if (input[1] == NULL || ft_strchr(input[1], '~'))
	{
		home = getenv("HOME");
		if (home && *home)
		{
			if (chdir(home))
				perror("minishell ");
		}
	}
	else
	{
		if (chdir(input[1]) != 0)
		{
			errno = 1;
			write(2, "minishell : No such file or directory\n", 38);
			strerror(errno);
		}
	}
	set_pwd();
	if (!is_parent())
	{
		exit (errno);
	}
}
