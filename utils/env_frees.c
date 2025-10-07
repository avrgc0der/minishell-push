/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_frees.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoshahi < enoshahi@student.42abudhabi.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 11:54:31 by enoshahi          #+#    #+#             */
/*   Updated: 2025/10/07 14:40:52 by enoshahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// * contains;
// *	env_free_node;
// *	free_env;

void	env_free_node(t_env *env)
{
	if (!env)
		return ;
	if (env->key)
	{
		free(env->key);
		env->key = NULL;
	}
	if (env->val)
	{
		free(env->val);
		env->val = NULL;
	}
	free(env);
	env = NULL;
}

void	free_env(t_env *env)
{
	t_env	*current;
	t_env	*tmp;

	current = env;
	if (!current)
		return ;
	while (current)
	{
		tmp = current->next;
		env_free_node(current);
		current = tmp;
	}
}
