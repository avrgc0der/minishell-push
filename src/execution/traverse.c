/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtangalv <mtangalv@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 11:51:05 by mtangalv          #+#    #+#             */
/*   Updated: 2025/10/05 14:39:48 by mtangalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// * contains
// *	one_pass
// *	two_pass

int	two_pass(t_shell *shell, t_exec *exec, t_ast *node, t_env *envl)
{
	if (node == NULL)
		return (TRUE);
	if (node->value.type == PIPE)
		return (two_pass(shell, exec, node->left, envl)
			&& two_pass(shell, exec->next, node->right, envl));
	if (node->value.type == HEREDOC)
		return (two_pass(shell, exec, node->left, envl));
	if (node->value.type == WORD)
		return (handle_word(exec, node, shell->envps->path));
	if (node->value.type == INPUT)
		return (handle_input(shell, exec, node, envl));
	if (node->value.type == TRUNCATE)
		return (handle_truncate(shell, exec, node, envl));
	if (node->value.type == APPEND)
		return (handle_append(shell, exec, node, envl));
	return (TRUE);
}

int	one_pass(t_shell *shell, t_exec *exec, t_ast *node, t_env *envl)
{
	if (!node)
		return (TRUE);
	if (node->value.type == WORD)
		return (TRUE);
	if (node->value.type == HEREDOC)
		if (handle_heredoc(shell, exec, node, shell->envps) == FALSE)
			return (FALSE);
	if (one_pass(shell, exec, node->left, envl) == FALSE)
		return (FALSE);
	if (node->value.type == PIPE)
		if (handle_pipe(shell, exec, node, envl) == FALSE)
			return (FALSE);
	return (TRUE);
}
