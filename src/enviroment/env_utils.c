/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoshahi < enoshahi@student.42abudhabi.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 23:59:07 by enoshahi          #+#    #+#             */
/*   Updated: 2025/10/07 18:18:03 by enoshahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// * contains:
// *	modify_env
// *	change_shlvl
// *	array_size
// *	return_key
// *	return_val

/// @brief searches envs by key_name and modifies the value of the env
/// @param env the envs list
/// @param key_name the key_name to search
/// @param new_val the new env value to replace the orginal value with
int	modify_env(t_env *env, char *key_name, char *new_val)
{
	t_env	*tmp;

	tmp = env_search(env, key_name);
	if (!tmp)
		return (FALSE);
	free(tmp->val);
	tmp->val = ft_strdup(new_val);
	if (!tmp->val)
		return (FALSE);
	return (TRUE);
}

/// @brief searches for the SHLVL key name and increments it by 1
/// @param env env list
int	change_shlvl(t_env **env)
{
	t_env	*tmp;
	char	*str;
	int		nb;

	tmp = env_search(*env, "SHLVL");
	if (!tmp)
	{
		if (!env_create_var(env, "SHLVL", "1"))
			return (FALSE);
		return (TRUE);
	}
	nb = ft_atoi(tmp->val);
	nb += 1;
	if (nb < 0)
		nb = 0;
	str = ft_itoa(nb);
	if (!str)
		return (FALSE);
	if (!modify_env(tmp, "SHLVL", str))
	{
		free(str);
		return (FALSE);
	}
	free(str);
	return (TRUE);
}

/// @brief gets the size of a double-pointer array
/// @param array double-pointer array
/// @return size/len of the array
int	array_size(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}
