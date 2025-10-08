/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtangalv <mtangalv@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 16:49:35 by enoshahi          #+#    #+#             */
/*   Updated: 2025/10/08 11:40:52 by mtangalv         ###   ########.fr       */
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

static char	*ft_path(char **args, t_envs *envs)
{
	t_env	*home;
	char	*path;

	if (!args[1])
	{
		home = env_search(envs->env, "HOME");
		if (!home || !home->val)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return ("HOME");
		}
		path = home->val;
	}
	else
		path = args[1];
	return (path);
}

int	ft_cd(char **args, t_envs *envs)
{
	char	oldpwd[MAX_PATH];
	char	newpwd[MAX_PATH];
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
	if (chdir(ft_path(args, envs)) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(ft_path(args, envs));
		return (EXIT_FAILURE);
	}
	if (getcwd(newpwd, sizeof(newpwd)))
		update_pwd_vars(envs, oldpwd, newpwd);
	return (EXIT_SUCCESS);
}
