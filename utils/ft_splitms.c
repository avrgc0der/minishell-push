/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtangalv <mtangalv@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 14:58:10 by mtangalv          #+#    #+#             */
/*   Updated: 2025/09/25 13:23:24 by mtangalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// * contains:
// *	free_sdpt;
// *	count_quotes_as_oneword;
// *	num_of_wordsms;
// *	alloc_wordms;
// *	ft_splitms;

static void	free_sdpt(char **str, int index)
{
	int	i;

	i = 0;
	while (i <= index)
		free(str[i++]);
	free(str);
}

static int	count_quotes_as_oneword(char const *str, int i)
{
	char	quote_char;

	quote_char = str[i++];
	while (str[i] != '\0' && str[i] != quote_char)
		i++;
	return (i);
}

static int	num_of_wordsms(char const *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		while (str[i] != '\0' && str[i] == c)
			i++;
		if (str[i] != '\0')
		{
			count++;
			while (str[i] != '\0' && str[i] != c)
			{
				if (str[i] == 34 || str[i] == 39)
					i = count_quotes_as_oneword(str, i);
				if (i < 0)
					return (-1);
				i++;
			}
		}
	}
	return (count);
}

static char	*alloc_wordms(char const *str, char c)
{
	int		i;
	int		word_len;
	char	*final;

	i = 0;
	while (str[i] != '\0' && str[i] != c)
	{
		if (str[i] == 34 || str[i] == 39)
			i = count_quotes_as_oneword(str, i);
		if (i < 0)
			return (NULL);
		i++;
	}
	word_len = i;
	final = (char *)malloc(sizeof(char) * (word_len + 1));
	if (!final)
		return (NULL);
	i = 0;
	while (i < word_len)
	{
		final[i] = str[i];
		i++;
	}
	final[i] = '\0';
	return (final);
}

char	**ft_splitms(char const *s, char c)
{
	int		i;
	char	**arr;

	if (num_of_wordsms(s, c) < 0)
		return (NULL);
	arr = (char **)ft_calloc((num_of_wordsms(s, c) + 1), sizeof(char *));
	if (arr == NULL || s == NULL)
		return (NULL);
	i = 0;
	while (*s != '\0')
	{
		while (*s != '\0' && *s == c)
			s++;
		if (*s != '\0')
		{
			arr[i] = alloc_wordms(s, c);
			if (arr[i] == NULL)
			{
				free_sdpt(arr, i - 1);
				return (NULL);
			}
			s += ft_strlen(arr[i++]);
		}
	}
	return (arr);
}
