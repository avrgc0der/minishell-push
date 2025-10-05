/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_frees.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoshahi < enoshahi@student.42abudhabi.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 16:21:22 by mtangalv          #+#    #+#             */
/*   Updated: 2025/10/06 01:10:01 by enoshahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// * contains
// *	free_exec
// *	free_all_exec

void	free_exec(t_exec *exec)
{
	if (!exec)
		return ;
	check_close(exec->in_fd);
	exec->in_fd = -1;
	check_close(exec->out_fd);
	exec->out_fd = -1;
	if (exec->cmd)
		free_str(exec->cmd);
	if (exec->args)
		free_dpt(exec->args);
	exec->error = 0;
	free(exec);
	exec = NULL;
}

void	free_all_exec(t_exec **exec)
{
	t_exec	*current;
	t_exec	*tmp;

	current = *exec;
	if (!current)
		return ;
	while (current)
	{
		tmp = current->next;
		free_exec(current);
		current = tmp;
	}
	exec = NULL;
}
