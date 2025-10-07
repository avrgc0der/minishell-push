/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtangalv <mtangalv@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 17:48:11 by mtangalv          #+#    #+#             */
/*   Updated: 2025/10/07 20:07:09 by mtangalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (FALSE);
	if (ft_strcmp(cmd, "echo") == 0)
		return (TRUE);
	if (ft_strcmp(cmd, "cd") == 0)
		return (TRUE);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (TRUE);
	if (ft_strcmp(cmd, "export") == 0)
		return (TRUE);
	if (ft_strcmp(cmd, "unset") == 0)
		return (TRUE);
	if (ft_strcmp(cmd, "env") == 0)
		return (TRUE);
	if (ft_strcmp(cmd, "exit") == 0)
		return (TRUE);
	return (FALSE);
}
