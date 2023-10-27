/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egokeri <egokeri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 20:36:59 by egokeri           #+#    #+#             */
/*   Updated: 2023/10/26 20:37:00 by egokeri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_get_arg_count(char **input)
{
	int	i;

	i = 0;
	while (input[i])
		i++;
	return (i);
}

int	ft_isnumber_with_sign(char *arg)
{
	while (*arg)
	{
		if ((*arg >= '0' && *arg <= '9') || *arg == '+' || *arg == '-')
			arg++;
		else
			return (FALSE);
	}
	return (TRUE);
}

void	builtin_exit(char **input)
{
	if (ft_get_arg_count(input) == 1)
	{
		printf("exit\n");
		exit(errno);
	}
	else
	{
		if (ft_isnumber_with_sign(input[1]))
		{
			if (ft_get_arg_count(input) > 2)
			{
				write(2, "exit\nminishell: exit: too many arguments\n", 41);
				errno = 1;
				return ;
			}
			printf("exit\n");
			exit(ft_atoi(input[1]) % 256);
		}
		write(2, "exit\nminishell: exit: numeric argument required\n", 48);
		exit(-1 % 256);
	}
}
