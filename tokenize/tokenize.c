/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egokeri <egokeri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 20:38:26 by egokeri           #+#    #+#             */
/*   Updated: 2023/10/26 20:38:27 by egokeri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*init_token(char *str, enum e_ttype type)
{
	t_token	*token;

	token = ft_calloc(sizeof(t_token), 1);
	token->type = type;
	token->str = str;
	token->prev = NULL;
	token->next = NULL;
	return (token);
}

int	token_addback(t_token **token, t_token *new_token, int plus)
{
	t_token	*i_token;

	i_token = *token;
	if (!i_token)
		*token = new_token;
	else
	{
		while (i_token->next)
			i_token = i_token->next;
		i_token->next = new_token;
		new_token->prev = i_token;
	}
	return (plus);
}

void	tokenize(char *str)
{
	while (*str)
	{
		if (is_operator(str) == RED_APPEND)
			str += token_addback(&g_ms.token, init_token(ft_strdup(">>"), \
			RED_APPEND), 2);
		else if (is_operator(str) == HERE_DOC)
			str += token_addback(&g_ms.token, init_token(ft_strdup("<<"), \
			HERE_DOC), 2);
		else if (is_operator(str) == PIPE)
			str += token_addback(&g_ms.token, init_token(ft_strdup("|"), \
			PIPE), 1);
		else if (is_operator(str) == RED_INPUT)
			str += token_addback(&g_ms.token, init_token(ft_strdup("<"), \
			RED_INPUT), 1);
		else if (is_operator(str) == RED_OUTPUT)
			str += token_addback(&g_ms.token, init_token(ft_strdup(">"), \
			RED_OUTPUT), 1);
		else
			parse_token_string(&str);
	}
}
