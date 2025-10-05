/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtangalv <mtangalv@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 14:13:46 by mtangalv          #+#    #+#             */
/*   Updated: 2025/09/29 13:20:28 by mtangalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// * contains:
// *	get_redirect;
// *	get_word;
// *	split_even;
// *	split_in_place;
// *	create_ast_node;

char	*get_redirect(t_ast *node)
{
	char	*found;

	found = ft_strstrms(node->value.cmd, "<");
	if (found)
	{
		if (found[1] == '<')
			node->value.type = HEREDOC;
		else
			node->value.type = INPUT;
		return (found);
	}
	found = ft_strstrms(node->value.cmd, ">");
	if (!found)
		return (NULL);
	if (found[1] == '>')
		node->value.type = APPEND;
	else
		node->value.type = TRUNCATE;
	return (found);
}

static char	*get_word(char *str)
{
	while (*str == ' ')
		str++;
	while (*str != '\0')
	{
		if (*str == '"')
			str = ft_strchr(str + 1, '"');
		else if (*str == '\'')
			str = ft_strchr(str + 1, '\'');
		else if (ft_strchr(" \t<>|", *str) != NULL)
			return (str);
		str++;
	}
	return (str);
}

int	split_even(char *cmd, char *found, t_ast **left, t_ast **right)
{
	char	*left_str;
	char	*right_str;

	left_str = ft_substr(cmd, 0, found - cmd);
	if (!left_str)
		return (FALSE);
	right_str = ft_substr(found + 1, 0, ft_strlen(found + 1));
	if (!right_str)
		return (single_tree_error(left_str, NULL));
	*left = create_ast_node(left_str);
	if (!*left)
		return (double_tree_error((void *)left_str, (void *)right_str, NULL));
	*right = create_ast_node(right_str);
	if (!*right)
		return (double_tree_error((void *)left_str, (void *)right_str, NULL));
	return (TRUE);
}

int	split_in_place(char *cmd, char *found, t_ast **left, t_ast **right)
{
	char	*left_str;
	char	*right_str;

	left_str = ft_strdup(cmd);
	if (!left_str)
		return (FALSE);
	right_str = ft_substr(found, 0, get_word(found) - found);
	if (!right_str)
		return (single_tree_error(left_str, NULL));
	left_str = ft_strappend(left_str, found + ft_strlen(right_str));
	if (!left_str)
		return (single_tree_error(right_str, NULL));
	*left = create_ast_node(left_str);
	if (!*left)
		return (double_tree_error((void *)left_str, (void *)right_str, NULL));
	*right = create_ast_node(right_str);
	if (!*left || !*right)
		return (double_tree_error((void *)left_str, (void *)right_str, NULL));
	return (TRUE);
}

t_ast	*create_ast_node(char *value)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->left = NULL;
	node->right = NULL;
	node->value.cmd = value;
	node->value.args = NULL;
	node->value.type = WORD;
	return (node);
}
