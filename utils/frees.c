/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtangalv <mtangalv@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 20:24:27 by mtangalv          #+#    #+#             */
/*   Updated: 2025/10/05 11:10:31 by mtangalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// * contains:
// *	free_dpt;
// *	free_str;
// *	free_tree;
// *	destroy_shell;
// *	free_null;

void	free_dpt(char **str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return ;
	while (str && str[i])
	{
		free(str[i]);
		str[i++] = NULL;
	}
	free(str);
	str = NULL;
}

void	free_str(char *str)
{
	if (str)
		free(str);
	str = NULL;
}

void	free_tree(t_ast **node)
{
	if (*node == NULL)
		return ;
	free_tree(&(*node)->left);
	free_tree(&(*node)->right);
	free_str((*node)->value.cmd);
	if ((*node)->value.args)
		free_dpt((*node)->value.args);
	free(*node);
	*node = NULL;
}

void	destroy_shell(t_shell *shell)
{
	if (shell->exec)
		free_all_exec(&shell->exec);
	if (shell->ast)
		free_tree(&shell->ast);
	if (shell->envps->envs)
		free_dpt(shell->envps->envs);
	if (shell->envps->path)
		free_dpt(shell->envps->path);
	if (shell->envps->env)
		free_env(shell->envps->env);
	free(shell->envps);
	shell->envps = NULL;
	free(shell);
	shell = NULL;
}

void	free_null(void **ptr)
{
	if (*ptr)
		free(*ptr);
	*ptr = NULL;
}
