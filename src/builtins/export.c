/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoshahi < enoshahi@student.42abudhabi.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 20:18:17 by enoshahi          #+#    #+#             */
/*   Updated: 2025/10/05 19:58:25 by enoshahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	valid_export_key(char *key)
{
	int	i;

	if (!key)
		return (0);
	i = 0;
	if (!ft_isalpha(key[i]) && key[i] != '_')
		return (0);
	i++;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	print_export(t_env **temp, int size)
{
	int		i;
	int		j;
	t_env	*swap;

	i = 0;
	while (i < size - 1)
	{
		j = i + 1;
		while (j < size)
		{
			if (ft_strcmp(temp[i]->key, temp[j]->key) > 0)
			{
				swap = temp[i];
				temp[i] = temp[j];
				temp[j] = swap;
			}
			j++;
		}
		i++;
	}
	i = -1;
	while (++i < size)
		printf("declare -x %s=\"%s\"\n", temp[i]->key, temp[i]->val);
}

static int export_args(char **args, t_envs *envs)
{
	int		i;
	t_env	*temp;

	i = 0;
	while (args[i])
	{
		temp = split_var(args[i]);
		if (!temp)
			continue; // to be checked
		if (env_search(envs->env, temp->key))
			modify_env(envs->env, temp->key, temp->val);
		else if (valid_export_key(temp->key))
			env_create_var(envs->env, temp->key, temp->val);
		env_free_node(temp);
		i++;
	}
	return (TRUE);
}
static int	ft_eggsnport(t_envs *envs, t_env **exp, t_env *new)
{
	int	i;
	int	size;

	i = 0;
	printf("inside eggs\n");
	size = env_size(envs->env);
	exp = malloc(sizeof(t_env *) * size + 1);
	if (!exp)
		return (FALSE);
	while (new)
	{
		exp[i++] = new;
		new = new->next;
	}
	print_export(exp, size);
	free(exp);
	return (TRUE);
}

int	ft_export(t_envs *envs, char **args)
{
	t_env	**exp;
	t_env	*new;

	exp = NULL;
	new = envs->env;
	// printf("%s this is export\n", args[0]);
	if (args[0] == NULL)
		return (ft_eggsnport(envs, exp, new));
	return (export_args(args, envs));
}
