/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egokeri <egokeri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 20:37:34 by egokeri           #+#    #+#             */
/*   Updated: 2023/10/26 20:37:35 by egokeri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_token(void)
{
	t_token		*tmp;
	t_token		*token;

	token = g_ms.token;
	while (token)
	{
		free(token->str);
		token = token->next;
	}
	token = g_ms.token;
	while (token)
	{
		tmp = token;
		token = token->next;
		free(tmp);
	}
}
