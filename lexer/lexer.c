/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egokeri <egokeri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 20:37:57 by egokeri           #+#    #+#             */
/*   Updated: 2023/10/29 16:20:09 by egokeri          ###   ########.fr       */
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

int	new_process(t_token *token, t_process *process)
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
			return (FALSE);
		token = token->next;
	}
	return (TRUE);
}

int	lexer(void)
{
	t_token		*token;
	t_process	*process;
	int			err;

	process = NULL;
	token = g_ms.token;
	err = new_process(token, process);
	if (err == FALSE)
		return (FALSE);
	free_token();
	return (TRUE);
}
