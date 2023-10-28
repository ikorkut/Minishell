/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egokeri <egokeri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 20:37:57 by egokeri           #+#    #+#             */
/*   Updated: 2023/10/28 14:39:30 by egokeri          ###   ########.fr       */
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

void	new_process(t_token *token, t_process *process)
{
	while (token)
	{
		if (token->type == PIPE && token->prev == NULL)
		{
			token_err(PIPE);
			break ;
		}
		if (token->type == PIPE || token->prev == NULL)
		{
			if (token->type == PIPE)
				token = token->next;
			process = init_process();
			process_addback(&g_ms.process, process);
			g_ms.process_count++;
		}
		if (!token)
		{
			token_err(PIPE);
			break ;
		}
		if (!append_arguments(&token, process))
			return ;
		if (token)
			token = token->next;
	}
}

int	lexer(void)
{
	t_token		*token;
	t_process	*process;

	process = NULL;
	token = g_ms.token;
	new_process(token, process);
	free_token();
	return (TRUE);
}
