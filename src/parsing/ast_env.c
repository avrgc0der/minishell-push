/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtangalv <mtangalv@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 17:09:48 by mtangalv          #+#    #+#             */
/*   Updated: 2025/10/03 20:04:05 by mtangalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// * contains:
// *	create_str
// *	search_replace
// *	expand_var
// *	loop_str

static char	*create_str(char *str, char *value, int i, int j)
{
	char	*lstr;
	char	*rstr;
	char	*final_str;

	lstr = ft_substr(str, 0, i);
	if (!lstr)
		return (single_env_error((void *)value, NULL));
	rstr = ft_substr(str, j, ft_strlen(str) - j);
	if (!rstr)
		return (double_env_error((void *)lstr, (void *) value, NULL));
	final_str = ft_strappend(lstr, value);
	if (!final_str)
		return (double_env_error((void *)value, (void *)rstr, NULL));
	final_str = ft_strappend(final_str, rstr);
	if (!final_str)
		return (double_env_error((void *)value, (void *)rstr, NULL));
	free_str(value);
	free_str(rstr);
	free_str(str);
	return (final_str);
}

static char	*search_replace(char *str, t_envs *envps, int i, int j)
{
	char	*var_name;
	t_env	*var_value;

	var_name = ft_substr(str, i + 1, j - i - 1);
	if (!var_name)
		return (NULL);
	var_value = env_search(envps->env, var_name);
	if (var_value)
	{
		if (var_value->val)
		{
			free_str(var_name);
			return (ft_strdup(var_value->val));
		}
		else
		{
			free_str(var_name);
			return (ft_strdup(""));
		}
	}
	else
	{
		free_str(var_name);
		return (ft_strdup(""));
	}
}

char	*expand_var(char *str, int i, t_envs *envps)
{
	int		j;
	char	*value;

	j = i + 1;
	if (ft_isdigit(str[j++]))
		value = ft_strdup("");
	else if (str[j - 1] == '?')
		value = ft_itoa(envps->e_code);
	else
	{
		while (str[j] && (ft_isalnum(str[j]) || str[j] == '_'))
			j++;
		value = search_replace(str, envps, i, j);
	}
	if (!value)
		return (NULL);
	str = create_str(str, value, i, j);
	return (str);
}

char	*loop_str(char *str, t_envs *envps)
{
	int		i;
	int		flag;

	i = 0;
	flag = FALSE;
	while (str[i])
	{
		if (str[i] == '"')
			flag = !flag;
		if (str[i] == '\'' && flag != TRUE)
			skip_quotes(str, &i);
		if (str[i] == '$' && (ft_isalnum(str[i + 1]) || str[i + 1] == '_'
				|| str[i + 1] == '?'))
		{
			str = expand_var(str, i, envps);
			if (!str)
				return (NULL);
			continue ;
		}
		i++;
	}
	return (str);
}
