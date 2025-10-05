/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtangalv <mtangalv@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 16:50:08 by mtangalv          #+#    #+#             */
/*   Updated: 2025/09/29 13:44:51 by mtangalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// * contains:
// *	count_quotes
// *	remove_string_quotes
// *	remove_quotes
// *	split_args

/**
 * @brief count quotes and calculate string length without it
 * @param str Input string
 * @param final_len Pointer to store the final length
 * @return Number of quotes found
 */
static int	count_quotes(char *str, int *final_len)
{
	int	i;
	int	quote_count;

	i = 0;
	quote_count = 0;
	*final_len = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			skip_within(str, &quote_count, final_len, &i);
		else
			(*final_len)++;
		if (str[i])
			i++;
	}
	return (quote_count);
}

/**
 * @brief Remove quotes from a string in a memory-efficient way
 * @param str Input string with quotes
 * @return New string with quotes removed, or NULL if error
 */
char	*remove_string_quotes(char *str)
{
	int		i;
	int		j;
	int		final_len;
	int		quote_count;
	char	*result;

	if (!str)
		return (NULL);
	quote_count = count_quotes(str, &final_len);
	if (quote_count == 0)
		return (ft_strdup(str));
	result = (char *)malloc(final_len + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			add_within(str, result, &i, &j);
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}

/**
 * @brief Remove quotes from all strings in the AST
 * @param node Current AST node
 * @return 1 on success, 0 on failure
 */
int	remove_quotes(t_ast *node)
{
	char	*new_str;

	if (node == NULL)
		return (TRUE);
	if (node->value.type != WORD)
		return (remove_quotes(node->left) && remove_quotes(node->right));
	if (node->value.cmd)
	{
		new_str = remove_string_quotes(node->value.cmd);
		if (!new_str)
			return (FALSE);
		free(node->value.cmd);
		node->value.cmd = new_str;
	}
	if (node->value.args)
		if (remove_from_args(node) == FALSE)
			return (FALSE);
	return (TRUE);
}

int	split_args(t_ast *node)
{
	if (node == NULL)
		return (TRUE);
	if (node->value.type != WORD)
		return (split_args(node->left) && split_args(node->right));
	node->value.args = ft_splitms(node->value.cmd, ' ');
	if (!(node->value.args))
		return (FALSE);
	return (TRUE);
}
