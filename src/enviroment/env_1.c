/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoshahi < enoshahi@student.42abudhabi.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 15:31:26 by enoshahi          #+#    #+#             */
/*   Updated: 2025/10/06 01:15:08 by enoshahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// * contains:
// *	env_create_var
// *	env_malloc
// *	split_var
// *	env_search
// *	ft_env

/// @brief Mallocs and copies to_copy string until len
/// @param to_copy string to malloc and dup
/// @param len length to copy until
/// @return malloc'ed string
int	env_create_var(t_env *env, char *key, char *val)
{
	t_env	*new;

	new = NULL;
	if (!key || !val)
		return (FALSE);
	new = malloc(sizeof(t_env));
	if (!new)
		return (FALSE);
	new->key = ft_strdup(key);
	new->val = ft_strdup(val);
	add_env(&env, new);
	return (TRUE);
}

/// @brief Mallocs and copies to_copy string until len
/// @param to_copy string to malloc and dup
/// @param len length to copy until
/// @return malloc'ed string
static char	*env_malloc(char *to_copy, int len)
{
	int		i;
	char	*to_malloc;

	i = 0;
	to_malloc = malloc(sizeof(char) * (len + 1));
	if (!to_malloc)
		return (NULL);
	while (i < len)
	{
		to_malloc[i] = to_copy[i];
		i++;
	}
	to_malloc[i] = '\0';
	return (to_malloc);
}

/// @brief Gets length of the key and value of envp variables
/// @param envp Environment variables
/// @return env node
t_env	*split_var(char *envp)
{
	t_env	*env;
	int		i;
	int		key_len;
	int		val_len;

	i = 0;
	val_len = 0;
	while (envp[i] && envp[i] != '=')
		i++;
	key_len = i;
	if (envp[i] == '=')
		while (envp[++i])
			val_len++;
	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->key = env_malloc(envp, key_len);
	if (!env->key)
		return (NULL);
	env->val = env_malloc(envp + key_len + 1, val_len);
	if (!env->val)
		return (NULL);
	env->next = NULL;
	return (env);
}

/// @brief Searches env list to find key_name match
/// @param env environement list
/// @param key_name the string/keyname we are searching for in env
/// @return traversed env
t_env	*env_search(t_env *env, char *key_name)
{
	int		i;
	t_env	*tmp;

	tmp = env;
	if (key_name == NULL || key_name[0] == '\0')
		return (NULL);
	while (tmp)
	{
		i = 0;
		if (tmp->key)
		{
			while (tmp->key[i] && key_name[i] && tmp->key[i] == key_name[i])
				i++;
			if (tmp->key[i] == '\0' && key_name[i] == '\0')
				return (tmp);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

int	ft_env(t_envs *envs)
{
	t_env	*tmp;

	tmp = envs->env;
	if (!tmp)
		return (FALSE);
	while (tmp)
	{
		printf("%s=%s\n", tmp->key, tmp->val);
		tmp = tmp->next;
	}
	return (TRUE);
}

// todo   fill out the env list
// todo   set shlvl
// todo   set path