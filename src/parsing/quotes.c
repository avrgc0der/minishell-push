/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtangalv <mtangalv@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 15:26:10 by mtangalv          #+#    #+#             */
/*   Updated: 2025/09/29 13:54:50 by mtangalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// * contains:
// *	skip_within
// *	add_within
// *	remove_from_args

void	skip_within(char *str, int *quote_count, int *final_len, int *i)
{
	char	quote_char;

	quote_char = str[(*i)++];
	(*quote_count)++;
	while (str[*i] && str[(*i)] != quote_char)
	{
		(*final_len)++;
		(*i)++;
	}
	if (str[*i] == quote_char)
		(*quote_count)++;
}

void	add_within(char *str, char *result, int *i, int *j)
{
	char	quote_char;

	quote_char = str[*i];
	(*i)++;
	while (str[*i] && str[*i] != quote_char)
		result[(*j)++] = str[(*i)++];
	if (str[*i] == quote_char)
		(*i)++;
}

int	remove_from_args(t_ast *node)
{
	char	**args;
	char	*new_str;
	int		i;

	args = node->value.args;
	i = 0;
	while (args[i])
	{
		new_str = remove_string_quotes(args[i]);
		if (!new_str)
			return (FALSE);
		free(args[i]);
		args[i] = new_str;
		i++;
	}
	return (TRUE);
}
