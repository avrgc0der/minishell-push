/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoshahi < enoshahi@student.42abudhabi.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 16:49:35 by enoshahi          #+#    #+#             */
/*   Updated: 2025/10/07 15:22:32 by enoshahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_pwd_vars(t_envs *envs, char *oldpwd, char *newpwd)
{
	if (env_search(envs->env, "OLDPWD"))
		modify_env(envs->env, "OLDPWD", oldpwd);
	else
		env_create_var(&envs->env, "OLDPWD", oldpwd);
	if (env_search(envs->env, "PWD"))
		modify_env(envs->env, "PWD", newpwd);
	else
		env_create_var(&envs->env, "PWD", newpwd);
	envs_array(envs, envs->env);
}

static int	ft_arrlen(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return (i);
	while (arr[i])
		i++;
	return (i);
}

/// @brief Change directory to given path (or $HOME if no args)
/// @param args Array of arguments (args[0] = "cd", args[1] = path)
/// @param envs Struct holding environment linked list
/// @return 0 on success, 1 on failure
int	ft_cd(char **args, t_envs *envs)
{
	char	oldpwd[MAX_PATH];
	char	newpwd[MAX_PATH];
	char	*path;
	t_env	*home;
	int		arg_size;

	arg_size = ft_arrlen(args);
	if (arg_size > 2)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (EXIT_FAILURE);
	}
	if (!getcwd(oldpwd, sizeof(oldpwd)))
	{
		perror("cd");
		return (EXIT_FAILURE);
	}
	if (!args[1])
	{
		home = env_search(envs->env, "HOME");
		if (!home || !home->val)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (EXIT_FAILURE);
		}
		path = home->val;
	}
	else
		path = args[1];
	if (chdir(path) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(path);
		return (EXIT_FAILURE);
	}
	if (getcwd(newpwd, sizeof(newpwd)))
		update_pwd_vars(envs, oldpwd, newpwd);
	return (EXIT_SUCCESS);
}
