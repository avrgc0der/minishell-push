/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtangalv <mtangalv@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 13:49:27 by mtangalv          #+#    #+#             */
/*   Updated: 2025/10/03 20:38:29 by mtangalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// * contains:
// *	split_on_pipe
// *	split_on_io
// *	expand_vars
// *	scaffold_ast

static int	split_on_pipe(t_ast *head)
{
	char	*found;

	if (head == NULL)
		return (TRUE);
	if (head->value.type != WORD)
		return (split_on_pipe(head->left)
			&& split_on_pipe(head->right));
	found = ft_strstrms(head->value.cmd, "|");
	if (!found)
		return (TRUE);
	if (!split_even(head->value.cmd, found, &head->left, &head->right))
		return (FALSE);
	free_null((void **)&head->value.cmd);
	head->value.type = PIPE;
	return (split_on_pipe(head->left) && split_on_pipe(head->right));
}

static int	split_on_io(t_ast *head)
{
	char	*found;

	if (head == NULL)
		return (TRUE);
	if (head->value.type != WORD)
		return (split_on_io(head->left) && split_on_io(head->right));
	found = get_redirect(head);
	if (!found)
		return (TRUE);
	*found = '\0';
	found++;
	if (head->value.type == HEREDOC || head->value.type == APPEND)
		found++;
	if (!split_in_place(head->value.cmd, found, &head->left, &head->right))
		return (FALSE);
	free_null((void **)&head->value.cmd);
	return (split_on_io(head->left) && split_on_io(head->left));
}

int	expand_vars(t_ast *head, t_envs *envps)
{
	if (head == NULL)
		return (TRUE);
	if (head->value.type != WORD)
		return (expand_vars(head->left, envps)
			&& expand_vars(head->right, envps));
	head->value.cmd = loop_str(head->value.cmd, envps);
	if (!head->value.cmd)
		return (FALSE);
	return (expand_vars(head->left, envps) && expand_vars(head->right, envps));
}

/// @brief Create the tree as required by the execution part
/// @param input The input string to parse
/// @param shell The shell struct
/// @param envps envs, in a char array
/// @return The root of the abstract syntax tree
t_ast	*scaffold_ast(char *input, t_envs *envps)
{
	t_ast	*root;

	root = create_ast_node(input);
	if (!root)
	{
		ft_dprintf(2, "create root failed\n");
		return (NULL);
	}
	if (split_on_pipe(root) == FALSE)
		return (ast_error(root, "split pipe failed\n"));
	if (split_on_io(root) == FALSE)
		return (ast_error(root, "split output failed\n"));
	if (expand_vars(root, envps) == FALSE)
		return (ast_error(root, "expand vars failed\n"));
	if (split_args(root) == FALSE)
		return (ast_error(root, "arg split failed\n"));
	if (remove_quotes(root) == FALSE)
		return (ast_error(root, "quotes failed\n"));
	return (root);
}
