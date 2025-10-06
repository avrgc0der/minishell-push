/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtangalv <mtangalv@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 17:15:33 by mtangalv          #+#    #+#             */
/*   Updated: 2025/10/06 14:47:14 by mtangalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// * contains:
// *	check_quotes;
// *	check_pipe;
// *	check_redirect;
// *	ft_validate;

/// @brief Validate the string for quotes
/// @param str string to validate
/// @return 1 if unclosed quotes, 0 if valid
static int	check_quotes(char *str)
{
	while (*str)
	{
		if ((*str == '\'' || *str == '"'))
			str = ft_strchr(str + 1, *str);
		if (str == NULL)
			return (FALSE);
		str++;
	}
	return (TRUE);
}

/// @brief validate the string for pipes
/// @param str string to validate
/// @return 1 if invalid pipe, 0 if valid
static int	check_pipe(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		skip_quotes(str, &i);
		if (str[i] == '|')
		{
			if (i == 0)
				return (FALSE);
			if (str[i - 1] == '<' || str[i - 1] == '>')
				return (FALSE);
			i++;
			while (str[i] == ' ')
				i++;
			if (str[i] == '\0' || str[i] == '|')
				return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

static int	check_redirect(char *str)
{
	int		i;

	i = 0;
	if (str[i] == str[i + 1] && (str[i] == '<' || str[i] == '>'))
		i += 2;
	while (str[i] == ' ')
		i++;
	if (str[i] == '\0')
		return (FALSE);
	while (str[i])
	{
		skip_quotes(str, &i);
		if (str[i] == '<' || str[i] == '>')
		{
			if (str[i + 1] == str[i])
				i++;
			i++;
			while (str[i] == ' ')
				i++;
			if (ft_strchr("><&|", str[i]) || str[i] == '\0')
				return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

/// @brief Validate the input string
/// @param str The input string to validate
/// @return 0 if valid, 1 if invalid
int	ft_validate(char *str)
{
	if (!str || *str == '\0')
		return (FALSE);
	if (!check_quotes(str))
	{
		ft_printf("TRASH: unclosed quotes\n");
		return (FALSE);
	}
	if (!check_redirect(str))
	{
		ft_printf("TRASH: invalid redirect(s)\n");
		return (FALSE);
	}
	if (!check_pipe(str))
	{
		ft_dprintf(2, "TRASH: invalid pipe\n");
		return (FALSE);
	}
	return (TRUE);
}
