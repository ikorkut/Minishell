/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egokeri <egokeri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 20:37:20 by egokeri           #+#    #+#             */
/*   Updated: 2023/10/26 20:37:21 by egokeri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_builtin(t_process *process)
{
	int	in;
	int	out;

	in = dup(0);
	out = dup(1);
	get_all_inputs(process);
	set_all_outputs(process);
	run_builtin(process->execute);
	dup2(in, 0);
	dup2(out, 1);
	close(in);
	close(out);
}

void	wait_cmd(void)
{
	t_process	*process;

	process = g_ms.process;
	close_all_fd();
	while (process)
	{
		if (process->pid != -1)
		{
			waitpid(process->pid, &errno, 0);
			errno = WEXITSTATUS(errno);
		}
		process = process->next;
	}
}

void	start_cmd(void)
{
	t_process	*process;

	process = g_ms.process;
	if (!process)
		return ;
	fill_all_heredoc();
	if (g_ms.ignore)
		return (close_all_fd());
	if (is_builtin(process->execute[0]) && g_ms.process_count == 1)
	{
		get_builtin(process);
		process = process->next;
	}
	while (process)
	{
		run_cmd(process);
		process = process->next;
	}
	wait_cmd();
}
