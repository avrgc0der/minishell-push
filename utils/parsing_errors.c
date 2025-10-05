/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtangalv <mtangalv@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 13:36:47 by mtangalv          #+#    #+#             */
/*   Updated: 2025/09/28 19:51:40 by mtangalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// * contains:
// *	tree_error
// *	single_env_error
// *	double_env_error
// * 	single_tree_error
// * 	double_tree_error

t_ast	*ast_error(t_ast *node, char *error_message)
{
	if (node)
		free_tree(&node);
	if (error_message)
		ft_putendl_fd(error_message, 2);
	return (NULL);
}

void	*single_env_error(void *ptr, char *error_message)
{
	if (ptr)
		free_null(ptr);
	if (error_message)
		ft_putendl_fd(error_message, 2);
	return (NULL);
}

void	*double_env_error(void *ptr1, void *ptr2, char *error_message)
{
	if (ptr1)
		free_null(ptr1);
	if (ptr2)
		free_null(ptr2);
	if (error_message)
		ft_putendl_fd(error_message, 2);
	return (NULL);
}

int	single_tree_error(void *ptr, char *error_message)
{
	if (ptr)
		free_null(ptr);
	if (error_message)
		ft_putendl_fd(error_message, 2);
	return (FALSE);
}

int	double_tree_error(void *ptr1, void *ptr2, char *error_message)
{
	if (ptr1)
		free_null(ptr1);
	if (ptr2)
		free_null(ptr2);
	if (error_message)
		ft_putendl_fd(error_message, 2);
	return (FALSE);
}
