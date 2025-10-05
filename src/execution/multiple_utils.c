/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtangalv <mtangalv@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 13:41:09 by mtangalv          #+#    #+#             */
/*   Updated: 2025/10/05 21:30:29 by mtangalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// * contains
// *	count_commands
// *	fork_and_exec
// *	setup_child_fds
// *	close_all_exec_fds
// *	wait_and_cleanup

int	count_commands(t_exec *exec)
{
	int	count;

	count = 0;
	while (exec)
	{
		count++;
		exec = exec->next;
	}
	return (count);
}

pid_t	fork_and_exec(t_shell *shell, t_exec *exec)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("TRASH");
		return (-1);
	}
	if (pid == 0)
	{
		setup_child_fds(exec);
		close_all_exec_fds(shell->exec);
		if (is_builtin(exec->cmd))
			exit(exec_builtin(exec, shell));
		else
			exit(exec_external(shell, exec, shell->envps->envs));
	}
	return (pid);
}

void	setup_child_fds(t_exec *exec)
{
	if (exec->in_fd != -1)
	{
		dup2(exec->in_fd, STDIN_FILENO);
		close(exec->in_fd);
	}
	if (exec->out_fd != -1)
	{
		dup2(exec->out_fd, STDOUT_FILENO);
		close(exec->out_fd);
	}
}

void	close_all_exec_fds(t_exec *exec)
{
	while (exec)
	{
		if (exec->in_fd != -1)
			close(exec->in_fd);
		if (exec->out_fd != -1)
			close(exec->out_fd);
		exec = exec->next;
	}
}

int	wait_and_cleanup(pid_t *pids, int count)
{
	int	status;
	int	last_status;
	int	i;

	last_status = 0;
	i = 0;
	while (i < count)
	{
		waitpid(pids[i], &status, 0);
		if (WIFEXITED(status))
			last_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			last_status = 128 + WTERMSIG(status);
		i++;
	}
	free(pids);
	return (last_status);
}
