/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoshahi < enoshahi@student.42abudhabi.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 17:46:44 by enoshahi          #+#    #+#             */
/*   Updated: 2025/10/06 20:47:37 by enoshahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	n_flag_check(char *arg)
{
	int	i;
	int	n_flag;

	i = 0;
	n_flag = 0;
	if (!arg || !arg[0])
		return (n_flag);
	if (arg[0] == '-')
	{
		i++;
		while (arg[i] && arg[i] == 'n')
		{
			if (arg[i + 1] == '\0')
				n_flag = 1;
			i++;
		}
	}
	return (n_flag);
}

int	ft_echo(char **args)
{
	int	i;
	int	n_flag;

	i = 0;
	n_flag = 0;
	if (!args)
		return (EXIT_FAILURE);
	while (n_flag_check(args[i]) == 1)
	{
		n_flag = 1;
		i++;
	}
	while (args[i])
	{
		ft_putstr(args[i]);
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (n_flag == 0)
		write(1, "\n", 1);
	return (EXIT_SUCCESS);
}
