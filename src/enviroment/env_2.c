/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtangalv <mtangalv@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 00:11:11 by enoshahi          #+#    #+#             */
/*   Updated: 2025/10/04 19:24:43 by mtangalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// * contains:
// *	env_last
// *	add_env
// *	env_size
// *	env_join
// *	envs_array

/// @brief Gets the last node on the env
/// @param lst list of envs
/// @return last node in env
t_env	*env_last(t_env *lst)
{
	t_env	*node;

	node = lst;
	if (!lst)
		return (NULL);
	while (node->next != NULL)
		node = node->next;
	return (node);
}

/// @brief Adds a new env to the end of the list
/// @param env list of envs
/// @param new new env to add
void	add_env(t_env **env, t_env *new)
{
	if (!env || !new)
		return ;
	if (*env)
		env_last(*env)->next = new;
	else
		*env = new;
	new->next = NULL;
}

/// @brief ft_strlen for envs
/// @param env 
/// @return length of the env list
int	env_size(t_env *env)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = env;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

/// @brief Concatenates the env node's key and value together,
/// including '=' and stores in a char *
/// @param env environment list
/// @return string with joined key and value with '=' sign
char	*env_join(t_env *env)
{
	char	*joinstr;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	len = ft_strlen(env->key) + ft_strlen(env->val) + 2;
	joinstr = (char *)malloc((len) * sizeof(char));
	if (!joinstr)
		return (NULL);
	while (env->key[i] != '\0')
	{
		joinstr[i] = env->key[i];
		i++;
	}
	joinstr[i] = '=';
	i += 1;
	while (env->val[j] != '\0')
		joinstr[i++] = env->val[j++];
	joinstr[i] = '\0';
	return (joinstr);
}

/// @brief convert linked list of envs to a array
/// @param list_envs 
/// @param env 
int	envs_array(t_envs *list_envs, t_env *env)
{
	t_env	*tmp;
	int		size;
	int		i;

	i = 0;
	tmp = env;
	size = env_size(env);
	if (list_envs->envs)
	{
		free_dpt(list_envs->envs);
		list_envs->envs = NULL;
	}
	list_envs->envs = malloc(sizeof(char *) * (size + 1));
	if (!list_envs->envs)
		return (FALSE);
	while (tmp)
	{
		list_envs->envs[i] = env_join(tmp);
		if (!list_envs->envs[i])
			return (FALSE);
		i++;
		tmp = tmp->next;
	}
	list_envs->envs[i] = NULL;
	return (TRUE);
}
