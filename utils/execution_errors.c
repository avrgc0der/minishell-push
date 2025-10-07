/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_errors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtangalv <mtangalv@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 11:50:18 by mtangalv          #+#    #+#             */
/*   Updated: 2025/10/07 19:19:40 by mtangalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// * contains
// *	get_execve_error
// *	set_failure
// *	one_pass_cleanup
// *	cleanup_pids

int	get_execve_error(char *cmd)
{
	if (access(cmd, F_OK) == -1)
	{
		ft_dprintf(2, "TRASH: %s: command not found\n", cmd);
		return (127);
	}
	else if (access(cmd, X_OK) == -1)
	{
		ft_dprintf(2, "TRASH: %s: Permission denied\n", cmd);
		return (126);
	}
	else
		return (0);
}

int	set_failure(t_exec *exec, char *error_msg)
{
	if (error_msg)
		ft_dprintf(2, "%s", error_msg);
	exec->error = 1;
	return (FALSE);
}

int	cleanup_exec(t_shell *shell)
{
	if (shell->exec)
	{
		free_all_exec(&(shell->exec));
		shell->exec = NULL;
	}
	return (1);
}

int	cleanup_pids(pid_t *pids, int exit_code)
{
	free(pids);
	return (exit_code);
}
