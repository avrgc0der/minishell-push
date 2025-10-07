/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtangalv <mtangalv@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 19:43:15 by mtangalv          #+#    #+#             */
/*   Updated: 2025/10/07 17:55:11 by mtangalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// * contains
// *	dupe_stds
// *	restore_stds
// *	dupe_close
// *	exec_external

static void	dupe_close(int old_fd, int new_fd)
{
	dup2(old_fd, new_fd);
	check_close(old_fd);
}

static void	dupe_stds(t_exec *exec, int *saved_stdin, int *saved_stdout)
{
	if (exec->in_fd != -1)
	{
		*saved_stdin = dup(0);
		dupe_close(exec->in_fd, 0);
	}
	if (exec->out_fd != -1)
	{
		*saved_stdout = dup(1);
		dupe_close(exec->out_fd, 1);
	}
}

static void	restore_stds(int *saved_stdin, int *saved_stdout)
{
	if (saved_stdin != NULL && *saved_stdin != -1)
	{
		dup2(*saved_stdin, 0);
		close(*saved_stdin);
	}
	if (saved_stdout != NULL && *saved_stdout != -1)
	{
		dup2(*saved_stdout, 1);
		close(*saved_stdout);
	}
}

int	exec_builtin(t_exec *exec, t_shell *shell)
{
	int		saved_stdin;
	int		saved_stdout;
	int		result;

	dupe_stds(exec, &saved_stdin, &saved_stdout);
	if (!exec->cmd)
		result = 1;
	else if (!ft_strcmp(exec->cmd, "cd"))
		result = ft_cd(exec->args, shell->envps);
	else if (!ft_strcmp(exec->cmd, "echo"))
		result = ft_echo(exec->args + 1);
	else if (!ft_strcmp(exec->cmd, "pwd"))
		result = ft_pwd();
	else if (!ft_strcmp(exec->cmd, "export"))
		result = ft_export(shell->envps, exec->args + 1);
	else if (!ft_strcmp(exec->cmd, "unset"))
		result = ft_unset(shell->envps, exec->args);
	else if (!ft_strcmp(exec->cmd, "exit"))
		result = ft_exit(exec->args, shell);
	else if (!ft_strcmp(exec->cmd, "env"))
		result = ft_env(shell->envps);
	else
		result = 1;
	restore_stds(&saved_stdin, &saved_stdout);
	return (result);
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
