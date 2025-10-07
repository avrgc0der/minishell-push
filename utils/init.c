/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoshahi < enoshahi@student.42abudhabi.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 14:36:35 by mtangalv          #+#    #+#             */
/*   Updated: 2025/10/07 15:21:41 by enoshahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// * contains:
// *	create_exec
// *	shell_envs
// *	create_shell

static int	shell_envs(t_envs *envs)
{
	if (!change_shlvl(&envs->env))
		return (FALSE);
	return (TRUE);
}

t_exec	*init_exec(void)
{
	t_exec	*exec;

	exec = ft_calloc(sizeof(t_exec), 1);
	if (!exec)
		return (NULL);
	exec->in_fd = -1;
	exec->out_fd = -1;
	exec->cmd = NULL;
	exec->args = NULL;
	exec->error = 0;
	exec->next = NULL;
	return (exec);
}

/// @brief Create the main shell structure and initialize envs
/// @param envs environment variables from main
/// @return pointer to the shell structure
t_shell	*create_shell(char **envs)
{
	t_shell	*shell;
	t_env	*new;

	shell = ft_calloc(sizeof(t_shell), 1);
	if (!shell)
		return (NULL);
	shell->envps = ft_calloc(sizeof(t_envs), 1);
	if (!shell->envps)
	{
		free(shell);
		return (NULL);
	}
	while (*envs)
	{
		new = split_var(*envs++);
		if (new != NULL)
			add_env(&shell->envps->env, new);
	}
	if (!shell_envs(shell->envps))
	{
		destroy_shell(shell);
		return (NULL);
	}
	return (shell);
}
