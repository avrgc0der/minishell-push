/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   two_pass.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtangalv <mtangalv@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 17:11:42 by mtangalv          #+#    #+#             */
/*   Updated: 2025/10/06 18:17:45 by mtangalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// * contains
// *	handle_word
// *	handle_input
// *	handle_truncate
// *	handle_append

int	handle_word(t_exec *exec, t_ast *node, char **envar)
{
	exec->args = node->value.args;
	node->value.args = NULL;
	if (!exec->args)
	{
		perror("TRASH");
		return (set_failure(exec, NULL));
	}
	if (exec->args[0])
	{
		if (is_builtin(exec->args[0]))
			exec->cmd = ft_strdup(exec->args[0]);
		else
			exec->cmd = get_path(exec->args[0], envar);
		if (!exec->cmd)
		{
			perror("TRASH");
			return (set_failure(exec, NULL));
		}
	}
	return (TRUE);
}

int	handle_truncate(t_shell *shell, t_exec *exec, t_ast *node, t_env *env)
{
	int	fd;

	check_close(exec->out_fd);
	fd = open(node->right->value.args[0], O_WRONLY | O_TRUNC | O_CREAT, 420);
	if (fd == -1)
	{
		perror("TRASH");
		return (set_failure(exec, NULL));
	}
	exec->out_fd = fd;
	return (two_pass(shell, exec, node->left, env));
}

int	handle_append(t_shell *shell, t_exec *exec, t_ast *node, t_env *env)
{
	int	fd;

	check_close(exec->out_fd);
	fd = open(node->right->value.args[0], O_WRONLY | O_APPEND | O_CREAT, 420);
	if (fd == -1)
	{
		perror("TRASH");
		return (set_failure(exec, NULL));
	}
	exec->out_fd = fd;
	return (two_pass(shell, exec, node->left, env));
}

int	handle_input(t_shell *shell, t_exec *exec, t_ast *node, t_env *env)
{
	int	fd;

	if (node->right->value.args[0] == NULL)
		return (set_failure(exec, "TRASH: obscure redirect\n"));
	if (access(node->right->value.args[0], F_OK) == -1)
		return (set_failure(exec, "TRASH: No such file or directory\n"));
	fd = open(node->right->value.args[0], O_RDONLY, 420);
	if (fd == -1)
	{
		perror("TRASH");
		return (set_failure(exec, NULL));
	}
	if (find_heredoc(node) == TRUE)
	{
		close(fd);
		return (two_pass(shell, exec, node->left, env));
	}
	check_close(exec->in_fd);
	exec->in_fd = fd;
	return (two_pass(shell, exec, node->left, env));
}
