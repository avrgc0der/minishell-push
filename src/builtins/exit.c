/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoshahi < enoshahi@student.42abudhabi.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 16:53:32 by enoshahi          #+#    #+#             */
/*   Updated: 2025/10/06 20:48:13 by enoshahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_isnumeric_str(const char *str)
{
	int	i;

	if (!str || !*str)
		return (EXIT_FAILURE);
	if (str[0] == '+' || str[0] == '-')
		str++;
	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

/// @brief Normalize exit code to 0–255 (bash behavior)
/// @param n The number (can be >255 or <0)
/// @return The normalized value in range 0–255
int	normalize_exit_code(long long n)
{
	return ((unsigned char)(n % 256));
}

/// @brief Exit the shell with proper bash-like behavior
/// @param args Array of arguments (args[0] = "exit", args[1] = optional code)
/// @param shell Main shell struct, used to free resources
/// @return 1 if too many args, otherwise does not return
int	ft_exit(char **args, t_shell *shell)
{
	long long	code;

	ft_putstr_fd("exit\n", 2);
	if (!args[1])
		code = 0;
	else if (!ft_isnumeric_str(args[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		destroy_shell(shell);
		exit(2);
	}
	else if (args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (EXIT_FAILURE);
	}
	else
		code = ft_atof(args[1]);
	destroy_shell(shell);
	exit(normalize_exit_code(code));
	return (EXIT_SUCCESS);
}
