/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtangalv <mtangalv@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 20:43:52 by mtangalv          #+#    #+#             */
/*   Updated: 2025/10/05 14:53:19 by mtangalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// * contains
// *	close_all_pipes
// *	get_path
// *	set_path
// *	find_heredoc
// *	check_close

char	*get_path(char *command, char **env)
{
	char	*tmp;
	char	*fullcmd;
	int		i;

	i = 0;
	if (env && command)
	{
		while (env[i])
		{
			tmp = ft_strjoin(env[i++], "/");
			if (!tmp)
				return (NULL);
			fullcmd = ft_strappend(tmp, command);
			if (!fullcmd)
				return (NULL);
			if (access(fullcmd, F_OK | X_OK) == 0)
				return (fullcmd);
			free(fullcmd);
			fullcmd = NULL;
		}
	}
	command = ft_strdup(command);
	if (!command)
		return (NULL);
	return (command);
}

int	set_path(t_envs *envs)
{
	t_env	*path_node;
	char	**temp;

	if (envs->path)
		free_dpt(envs->path);
	path_node = env_search(envs->env, "PATH");
	if (path_node == NULL)
	{
		envs->path = NULL;
		return (TRUE);
	}
	else
		temp = ft_split(path_node->val, ':');
	if (!temp)
		return (FALSE);
	envs->path = temp;
	return (TRUE);
}

int	find_heredoc(t_ast *node)
{
	if (node->value.type == HEREDOC)
		return (TRUE);
	if (node->value.type == WORD)
		return (FALSE);
	return (find_heredoc(node->left));
}

void	check_close(int fd)
{
	if (fd > 2 && fd != -1)
		close(fd);
}