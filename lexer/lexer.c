/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egokeri <egokeri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 20:37:57 by egokeri           #+#    #+#             */
/*   Updated: 2023/10/26 20:37:58 by egokeri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_lexer(void)
{
	free_token();
	free_process();
}

int	append_arguments(t_token **token, t_process *process)
{
	char		*data;

	if ((*token)->type == STRING)
	{
		data = clean_quote((*token)->str);
		process->execute = push_array(process->execute, data);
	}
	else
	{
		data = clean_quote((*token)->str);
		process->redirects = push_array(process->redirects, data);
		*token = (*token)->next;
		if (!(*token) || (*token)->type != STRING)
		{
			if (!(*token))
				token_err(0);
			else
				token_err((*token)->type);
			free_lexer();
			return (FALSE);
		}
		data = clean_quote((*token)->str);
		process->redirects = push_array(process->redirects, data);
	}
	return (TRUE);
}

int	pipe_control(void)
{
	t_token		*token;

	token = g_ms.token;
	if (token->type == PIPE && token->prev == NULL)
	{
		token_err(PIPE);
		return (0);
	}
	if (!token)
	{
		token_err(PIPE);
		return (0);
	}
	return (1);
}

int	lexer(void)
{
	t_token		*token;
	t_process	*process;

	token = g_ms.token;
	while (token)
	{
		if (!pipe_control())
			break ;
		if (token->type == PIPE || token->prev == NULL)
		{
			if (token->type == PIPE)
				token = token->next;
			process = init_process();
			process_addback(&g_ms.process, process);
			g_ms.process_count++;
		}
		if (!pipe_control())
			break ;
		if (!append_arguments(&token, process))
			return (FALSE);
		if (token)
			token = token->next;
	}
	free_token();
	return (TRUE);
}
