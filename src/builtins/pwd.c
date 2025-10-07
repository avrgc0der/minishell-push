/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoshahi < enoshahi@student.42abudhabi.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 16:33:43 by enoshahi          #+#    #+#             */
/*   Updated: 2025/10/06 20:49:39 by enoshahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(void)
{
	char	str[MAX_PATH];

	if (getcwd(str, MAX_PATH))
	{
		ft_putendl_fd(str, 1);
		return (EXIT_SUCCESS);
	}
	else
		return (EXIT_FAILURE);
}
