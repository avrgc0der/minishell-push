/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtangalv <mtangalv@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 19:43:15 by mtangalv          #+#    #+#             */
/*   Updated: 2025/10/05 14:59:37 by mtangalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// * contains
// *	dupe_close
// *	exec_external

static void	dupe_close(int old_fd, int new_fd)
{
	dup2(old_fd, new_fd);
	check_close(old_fd);
}

int	exec_external(t_shell *shell, t_exec *exec, char **envs)
{
	int	err;

	if (exec->in_fd != -1)
		dupe_close(exec->in_fd, 0);
	if (exec->out_fd != -1)
		dupe_close(exec->out_fd, 1);
	if (!exec->args[0])
	{
		destroy_shell(shell);
		return (0);
	}
	err = get_execve_error(exec->cmd);
	if (err != 0)
	{
		destroy_shell(shell);
		return (err);
	}
	if (exec->cmd)
		execve(exec->cmd, exec->args, envs);
	destroy_shell(shell);
	return (1);
}
