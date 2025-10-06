/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtangalv <mtangalv@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 11:41:28 by mtangalv          #+#    #+#             */
/*   Updated: 2025/10/06 18:07:11 by mtangalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// * contains
// *	run_single
// *	run_multiple
// *	execute

static int	get_signal(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 2);
		return (130);
	}
	else if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit: 3\n", 2);
		return (131);
	}
	return (128 + sig);
}

int	run_multiple(t_shell *shell)
{
	pid_t	*pids;
	t_exec	*curr;
	int		i;
	int		count;

	count = count_commands(shell->exec);
	pids = malloc(sizeof(pid_t) * count);
	if (!pids)
		return (1);
	curr = shell->exec;
	i = 0;
	while (curr)
	{
		pids[i++] = fork_and_exec(shell, curr, pids);
		if (pids[i - 1] < 0)
			return (cleanup_pids(pids, 1));
		curr = curr->next;
	}
	close_all_exec_fds(shell->exec);
	return (wait_and_cleanup(pids, count));
}

static int	run_single(t_shell *shell)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		perror("TRASH");
		return (1);
	}
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		exit(exec_external(shell, shell->exec, shell->envps->envs));
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status))
			return (get_signal(WTERMSIG(status)));
	}
	return (WEXITSTATUS(status));
}

int	execute(t_shell *shell)
{
	int	status;

	if (shell->exec)
		free_all_exec(&shell->exec);
	shell->exec = init_exec();
	if (!shell->exec)
		return (1);
	if (set_path(shell->envps) == FALSE)
		return (one_pass_cleanup(shell));
	if (one_pass(shell, shell->exec, shell->ast, shell->envps->env) == FALSE)
		return (one_pass_cleanup(shell));
	if (two_pass(shell, shell->exec, shell->ast, shell->envps->env) == FALSE)
		return (one_pass_cleanup(shell));
	free_tree(&shell->ast);
	if (shell->exec->cmd == NULL || shell->exec->args[0] == NULL)
		return (one_pass_cleanup(shell));
	if (shell->exec->next == NULL && is_builtin(shell->exec->cmd))
		status = exec_builtin(shell->exec, shell);
	else if (shell->exec->next == NULL)
		status = run_single(shell);
	else
		status = run_multiple(shell);
	return (status);
}
