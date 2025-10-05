/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtangalv <mtangalv@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 18:27:05 by mtangalv          #+#    #+#             */
/*   Updated: 2025/10/03 16:56:41 by mtangalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// * contains:
// *	ft_strappend;
// *	ft_strstrms;
// *	skip_quotes;
// *	replace_whitespaces;

char	*ft_strappend(char *str1, char *str2)
{
	char	*res;

	if (str1 == NULL || str2 == NULL)
		return (NULL);
	res = ft_strjoin(str1, str2);
	free(str1);
	str1 = NULL;
	if (!res)
		return (NULL);
	return (res);
}

char	*ft_strstrms(char *str, char *search)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (search[0] == '\0')
		return (str);
	while (str[i])
	{
		skip_quotes(str, &i);
		while (str[i + j] == search[j] && search[j] != '\0')
			j++;
		if (search[j] == '\0')
			return (&str[i]);
		i++;
		j = 0;
	}
	return (NULL);
}

/// @brief skip quoted strings, while keeping track of the current index
/// @param str The string to process.
/// @param i The current index in the string.
void	skip_quotes(const char *str, int *i)
{
	char	quote;

	if (str[*i] == '\'' || str[*i] == '"')
	{
		quote = str[*i];
		(*i)++;
		while (str[*i] && str[*i] != quote)
			(*i)++;
	}
}

/// @brief Replace all whitespace characters in the string with a single space.
/// @param str The string to process.
/// @return 0 on success, 1 if an error occurs (e.g., unclosed quotes).
int	replace_whitespaces(char *str)
{
	while (*str)
	{
		if (*str == '"' || *str == '\'')
			str = ft_strchr(str + 1, *str);
		else if (*str >= 8 && *str <= 13)
			*str = ' ';
		if (!str)
			return (FALSE);
		str++;
	}
	return (TRUE);
}
