/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoshahi < enoshahi@student.42abudhabi.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 17:48:11 by mtangalv          #+#    #+#             */
/*   Updated: 2025/10/06 20:43:41 by enoshahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (FALSE);
	if (ft_strcmp(cmd, "echo") == 0)
		return (TRUE);
	if (ft_strcmp(cmd, "cd") == 0)
		return (TRUE);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (TRUE);
	if (ft_strcmp(cmd, "export") == 0)
		return (TRUE);
	if (ft_strcmp(cmd, "unset") == 0)
		return (TRUE);
	if (ft_strcmp(cmd, "env") == 0)
		return (TRUE);
	if (ft_strcmp(cmd, "exit") == 0)
		return (TRUE);
	return (FALSE);
}

int	exec_builtin(t_exec *exec, t_shell *shell)
{
	char	*cmd;

	cmd = exec->cmd;
	if (!cmd)
		return (EXIT_FAILURE);
	if (!ft_strcmp(cmd, "cd"))
		return (ft_cd(exec->args, shell->envps));
	else if (!ft_strcmp(cmd, "echo"))
		return (ft_echo(exec->args + 1));
	else if (!ft_strcmp(cmd, "pwd"))
		return (ft_pwd());
	else if (!ft_strcmp(cmd, "export"))
		return (ft_export(shell->envps, exec->args + 1));
	else if (!ft_strcmp(cmd, "unset"))
		return (ft_unset(shell->envps, exec->args));
	else if (!ft_strcmp(cmd, "exit"))
		return (ft_exit(exec->args, shell));
	else if (!ft_strcmp(cmd, "env"))
		return (ft_env(shell->envps));
	else
		return (EXIT_FAILURE);
}
