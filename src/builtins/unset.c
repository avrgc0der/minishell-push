/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoshahi < enoshahi@student.42abudhabi.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 12:22:22 by enoshahi          #+#    #+#             */
/*   Updated: 2025/10/07 15:31:40 by enoshahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	delete_unset(t_env **env, char *delete_key)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = *env;
	prev = NULL;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, delete_key) == 0)
		{
			if (prev == NULL)
				*env = tmp->next;
			else
				prev->next = tmp->next;
			env_free_node(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

int	ft_unset(t_envs *envs, char **args)
{
	t_env	*tmp;
	int		i;

	if (!envs || !args)
		return (EXIT_FAILURE);
	i = 0;
	while (args[i])
	{
		tmp = env_search(envs->env, args[i]);
		if (tmp)
			delete_unset(&envs->env, tmp->key);
		i++;
	}
	return (EXIT_SUCCESS);
}
